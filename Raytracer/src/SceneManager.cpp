#include "SceneManager.h"



SceneManager::SceneManager( Parser * obj )
{
    v = new VectorCalculator() ;
    outputs = obj->get_output() ;
    lights = obj->get_lights() ;
    spheres = obj->get_spheres() ;
    rectangles = obj->get_rectangles() ;
    sac = new SceneAttributesCalculator(outputs) ;
    shader = new Shader(outputs,lights,spheres,rectangles) ;
}

void SceneManager::customize_progress_bar()
{
    bar->set_done_char("█");
    bar->set_opening_bracket_char("{");
    bar->set_closing_bracket_char("}");
}

void SceneManager::construct_scene()
{
    for( k = 0 ; k < outputs.size() ; k++ ){
        scene.resize(3*outputs[k].width*outputs[k].height) ;
        bar = new progressbar(outputs[k].height) ;
        customize_progress_bar() ;
        sac->compute_scene_attributes(k) ;
        shade_scene() ;
        generate_image() ;
        delete bar ;
        bar = NULL ;
    }
}

void SceneManager::shade_scene()
{
    std::vector<double> color, pixel_coordinate, ray, origin, focal_point ;
    
    #pragma omp parallel for schedule(dynamic) private(color, pixel_coordinate, ray, origin, focal_point)
    for ( int h = 0 ; h < outputs[k].height ; h++ ){
        for ( int w = 0 ; w < outputs[k].width ; w++ ){
            pixel_coordinate = sac->compute_pixel_coordinate(w,h,k) ;
            focal_point = sac->compute_focal_point(pixel_coordinate,k) ;
            color = v->initialize(color,0.0) ;
            for( int i = 0 ; i < outputs[k].raysperpixel ; i++ ){
                origin = sac->compute_origin(k) ;
                ray = sac->compute_ray(i, origin, focal_point, pixel_coordinate,k) ;
                color = v->add( color, shader->compute_color(ray, origin, v->generate_random_number(0,1),k) ) ;
            }
            color = v->multiply(color,(1.0/outputs[k].raysperpixel)) ;
            color = v->power(color,(1/GAMMA)) ;
            #pragma omp critical
                shade_pixel(w,h,color) ;
        }
        #pragma omp critical
            bar->update();
    }
    std::cout << std::endl ;
}

void SceneManager::shade_pixel( int w, int h, std::vector<double> color )
{
    scene[(3*outputs[k].width*h)+(3*w)+0] = color[0] ;
    scene[(3*outputs[k].width*h)+(3*w)+1] = color[1] ;
    scene[(3*outputs[k].width*h)+(3*w)+2] = color[2] ;
}

void SceneManager::generate_image()
{
    std::ofstream ofs(outputs[k].filename, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << outputs[k].width << ' ' << outputs[k].height << std::endl << "255" << std::endl;
 
    for (unsigned int j = 0; j < outputs[k].height; ++j)
        for (unsigned int i = 0; i < outputs[k].width; ++i)
            ofs << (char) (255.0 * scene[3*j*outputs[k].width+3*i+0]) <<  (char) (255.0 * scene[3*j*outputs[k].width+3*i+1]) << (char) (255.0 * scene[3*j*outputs[k].width+3*i+2]);
 
    ofs.close();
}

SceneManager::~SceneManager()
{
    delete sac ;
    delete v ;
    v = NULL ;
    sac = NULL ;
}
