#include "Shader.h"



Shader::Shader( std::vector<Output> _outputs, std::vector<Light> _lights, std::vector<Sphere> _spheres, std::vector<Rectangle> _rectangles )
{
    v = new VectorCalculator() ;
    outputs = _outputs ;
    lights = _lights ;
    spheres = _spheres ;
    rectangles = _rectangles ;
}

std::vector<double> Shader::compute_color( std::vector<double> ray, std::vector<double> origin, double time, int k )
{
    IntersectionPoint p ;
    IntersectionChecker * ic = new IntersectionChecker(spheres, rectangles) ;
    std::vector<double> color ;
    if( !ic->check_intersection(ray, origin, time, -1) )
        color = outputs[k].bkc ;
    else if( !outputs[k].globalillum )
        color = perform_local_illumination( ic->get_intersection_point(), time, k, ic ) ;
    else{
        color = perform_global_illumination( ic->get_intersection_point(), time, k, outputs[k].maxbounces, ic ) ;
        if( (color[0]==-1) && (color[1]==-1) && (color[2]==-1) ){
            color[0] = 0 ; color[1] = 0 ; color[2] = 0 ;
        }
        color = v->power(color,(1/GAMMA)) ;
    }
    delete ic ;
    ic = NULL ;
    return color ;
}

std::vector<double> Shader::perform_local_illumination( IntersectionPoint intersection_point, double time, int k, IntersectionChecker * ic )
{
    std::vector<double> light_ray, color ;
        
    color = v->initialize(color,0.0) ;
    for( int i = 0 ; i < lights.size() ; i++ ){
        light_ray = v->normalize(v->subtract(lights[i].centre, intersection_point.point)) ;
        color = v->add(color,v->multiply(v->add(v->multiply(v->hadamard_product(intersection_point.dc,lights[i].Id),std::max(0.0,v->dot(intersection_point.normal,light_ray) )), v->hadamard_product(intersection_point.sc,v->multiply(lights[i].is, pow(v->dot(v->normalize(v->add(v->normalize( v->subtract(outputs[k].camera,intersection_point.point) ),light_ray)),intersection_point.normal), intersection_point.pc))) ), compute_shadow(i,time,intersection_point,ic) )) ;
    }
    return v->clamp(v->add(color,v->multiply(v->hadamard_product(outputs[k].ai, intersection_point.ac),intersection_point.ka) )) ;
}

double Shader::compute_shadow( int i, double time, IntersectionPoint p, IntersectionChecker * ic )
{
    double shadow = 0.0 ;
    std::vector<double> ray ;

    if( lights[i].type == "point" ){
        ray = v->subtract(lights[i].centre,p.point) ;
        if( (ic->ishit_sphere(ray, time, p)) || (ic->ishit_rectangle(ray,p)) )
            return 0.0 ;
        return 1.0 ;
    }
    for( int m = 0 ; m < lights[i].n ; m++ ){
        ray = v->subtract(v->set( (v->generate_random_number(lights[i].min[0],lights[i].max[0] )), (v->generate_random_number(lights[i].min[1],lights[i].max[1])), (v->generate_random_number(lights[i].min[2],lights[i].max[2])) ),p.point) ;
        if( !(ic->ishit_sphere(ray, time, p)) && !(ic->ishit_rectangle(ray,p)) )
            shadow = shadow + 1 ;
    }
    return shadow / lights[i].n ;
}

std::vector<double> Shader::perform_global_illumination( IntersectionPoint intersection_point, double time, int k, int max_depth, IntersectionChecker * ic )
{
    if( max_depth <= 0  || v->generate_random_number(0,1) <= outputs[k].probterminate )
        return perform_local_illumination( intersection_point, time, k, ic ) ;

    std::vector<double> point = generate_random_point() ;
    if( (point[0]==0) && (point[1]==0) && (point[2]==0) )
        return v->set(-1,-1,-1) ;
    
    point = build_frame(intersection_point.point,intersection_point.normal,point) ;
    std::vector<double> ray = v->normalize(v->subtract(point,intersection_point.point)) ;
    
    if( !ic->check_intersection(ray, intersection_point.point, time, intersection_point.ID ) )
        return v->set(-1,-1,-1) ;
    
    std::vector<double> res = perform_global_illumination( ic->get_intersection_point(), time, k, max_depth-1, ic ) ;
    if( (res[0] == -1) && (res[1]==-1) && (res[2]==-1) )
        return v->set(-1,-1,-1) ;
    double cos = v->clamp_value( v->dot(intersection_point.normal,ray) ) ;
    double probability_coefficient  = 1.0 / (1.0 - outputs[k].probterminate) ;

    std::vector<double> color ;
    color.resize(3) ;
    for(int i = 0 ; i < 3 ; i++ )
        color[i] = probability_coefficient * cos * intersection_point.kd * intersection_point.dc[i] * res[i] ;
    
    return color ;
}

std::vector<double> Shader::generate_random_point()
{
    std::vector<double> point = v->set(0,0,0) ;
    point[0] = v->generate_random_number(0,1) * 2.0 - 1.0 ;
    point[2] = v->generate_random_number(0,1) * 2.0 - 1.0 ;

    double tmp = (point[0]*point[0]) + (point[2]*point[2]) ;
    if( tmp <= 1 ){
        point[1] = sqrt(1.0 - tmp) ;
        return point ;
    }
    else
        return v->set(0,0,0) ;
}

std::vector<double> Shader::build_frame( std::vector<double> origin, std::vector<double> normal, std::vector<double> random_point )
{
    std::vector<double> random_direction = v->set(1,0,0) ;
    std::vector<std::vector<double>> matrix ;
    matrix.resize(3) ;
    for( int i = 0 ; i < 3 ; i++ )
        matrix[i].resize(3) ;
    if( fabs(v->dot(random_direction,normal)) > 0.9 )
        random_direction = v->set(0,1,0) ;
    
    std::vector<double> z = v->normalize(v->cross(random_direction,normal)) ;
    std::vector<double> x = v->normalize(v->cross(normal,z)) ;

    for(int i=0;i<3;++i){
        matrix[i][0] = x[i] ;
        matrix[i][1] = normal[i] ;
        matrix[i][2] = z[i] ;
    }
    
    return v->add( origin, v->Multiply(matrix,random_point) ) ;
}

Shader::~Shader()
{
    delete v ;
    v = NULL ;
}
