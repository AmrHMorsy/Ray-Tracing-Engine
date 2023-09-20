#include "SceneManager.h"





class Raytracer{

private:
    
    Parser * obj ;
    nlohmann::json j ;
    char * file_name ;
    SceneManager * scene_manager ; 
    
public:
    
    Raytracer( char * name ) ;
    void run() ;
    bool extract_file_data() ;
    void parse_data() ;
    void construct_scene() ;
    ~Raytracer() ;
    
} ;
