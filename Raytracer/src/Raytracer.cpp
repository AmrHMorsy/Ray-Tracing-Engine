#include "Raytracer.h"

    

Raytracer::Raytracer( char * name )
{
    file_name = name ;
}

void Raytracer::run()
{
    if( !extract_file_data() )
        return ;
    time_t t = time(0) ;
    parse_data() ;
    construct_scene() ;
    t = time(0) - t ;
    std::cout << "Time: \033[1;32m"<< t <<"\033[0m second(s)"<< std::endl ;
}

bool Raytracer::extract_file_data()
{
    std::stringstream buffer;
    std::ifstream f(file_name);
    std::cout << "Scene: \033[1;32m" << file_name << "\033[0m" << std::endl ;
    if(!f){
        std::cout<< "\033[1;31mFile " << file_name << " does not exist!\033[0m" << std::endl ;
        return false ;
    }
    buffer << f.rdbuf();
    j = nlohmann::json::parse(buffer.str());
    return true ;
}

void Raytracer::parse_data()
{
    obj = new Parser(j) ;
    obj->parse_data() ; 
}

void Raytracer::construct_scene()
{
    scene_manager = new SceneManager(obj) ;
    scene_manager->construct_scene() ;
}

Raytracer::~Raytracer()
{
    delete obj ;
    obj = NULL ;
    delete scene_manager ;
    scene_manager = NULL ;
}
