#include "SceneAttributesCalculator.h"




class SceneManager
{
    
private:
    
    int k ; 
    VectorCalculator * v ;
    Shader * shader ;
    progressbar * bar ;
    std::vector<Output> outputs ;
    std::vector<Light> lights ;
    std::vector<Sphere> spheres ;
    std::vector<Rectangle> rectangles ;
    SceneAttributesCalculator * sac ;
    std::vector<double> scene ;
    
public:
        
    SceneManager( Parser * obj ) ;
    void customize_progress_bar() ;
    void construct_scene() ;
    void shade_scene() ;
    void shade_pixel( int w, int h, std::vector<double> color ) ;
    void generate_image() ;
    ~SceneManager() ;

} ;
