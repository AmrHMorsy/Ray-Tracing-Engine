#include "Shader.h"




class SceneAttributesCalculator
{
    
private:
    
    VectorCalculator * v ;
    double pixel_length ;
    std::vector<Output> outputs ;
    std::vector<double> horizantle, scene_topleft ;
    
public:
    
    SceneAttributesCalculator( std::vector<Output> _outputs ) ;
    void compute_scene_attributes( int k ) ;
    std::vector<double> compute_ray( int i, std::vector<double> origin, std::vector<double> focal_point, std::vector<double> pixel_coordinate, int k ) ;
    std::vector<double> compute_origin( int k ) ;
    std::vector<double> compute_focal_point( std::vector<double> pixel_coordinate, int k ) ;
    std::vector<double> compute_pixel_coordinate( int w, int h, int k ) ;
    ~SceneAttributesCalculator() ; 
    
} ;
