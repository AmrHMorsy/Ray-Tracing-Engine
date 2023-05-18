#include "SceneAttributesCalculator.h"



SceneAttributesCalculator::SceneAttributesCalculator( std::vector<Output> _outputs )
{
    outputs = _outputs ;
    v = new VectorCalculator() ;
}

void SceneAttributesCalculator::compute_scene_attributes( int k )
{
    horizantle = v->cross(outputs[k].lookat,outputs[k].up) ;
    pixel_length = (tan((outputs[k].fov*(PI/180))/2)*2)/outputs[k].height ;
    scene_topleft = v->subtract(v->add(v->add(outputs[k].camera,v->multiply(outputs[k].lookat,FOCAL_LENGTH)),v->multiply(outputs[k].up,tan((outputs[k].fov*(PI/180))/2))), v->multiply(horizantle,((outputs[k].width/2)*pixel_length)) ) ;
}

std::vector<double> SceneAttributesCalculator::compute_ray( int i, std::vector<double> origin, std::vector<double> focal_point, std::vector<double> pixel_coordinate, int k )
{
    if( outputs[k].dof )
        return v->normalize(v->subtract( focal_point , origin )) ;
    else{
        if( i == 0 )
            return v->normalize(v->subtract( pixel_coordinate , origin )) ;
        else
            return v->normalize(v->subtract( v->add_scalar(pixel_coordinate,v->generate_random_number(-(pixel_length/sqrt(12)),(pixel_length/sqrt(12)))) , origin )) ;
    }
}

std::vector<double> SceneAttributesCalculator::compute_origin( int k )
{
    if( outputs[k].dof )
        return v->set((v->generate_random_number(outputs[k].camera[0]-(outputs[k].aperture_radius/sqrt(3)),outputs[k].camera[0]+(outputs[k].aperture_radius/sqrt(3)))),(v->generate_random_number(outputs[k].camera[1]-(outputs[k].aperture_radius/sqrt(3)),outputs[k].camera[1]+(outputs[k].aperture_radius/sqrt(3)))),outputs[k].camera[2]) ;
    else
        return outputs[k].camera ;
}

std::vector<double> SceneAttributesCalculator::compute_focal_point( std::vector<double> pixel_coordinate, int k )
{
    if( outputs[k].dof )
        return v->add(outputs[k].camera,v->multiply(v->normalize(v->subtract(pixel_coordinate,outputs[k].camera)),outputs[k].focus_distance)) ;
    else
        return v->set(0,0,0) ;
}

std::vector<double> SceneAttributesCalculator::compute_pixel_coordinate( int w, int h, int k )
{
    return v->subtract(v->add(scene_topleft,v->multiply(horizantle,((pixel_length*w)+(pixel_length/2)))),v->multiply(outputs[k].up,((pixel_length*h)+(pixel_length/2)))) ;
}

SceneAttributesCalculator::~SceneAttributesCalculator()
{
    delete v ;
    v = NULL ; 
}
