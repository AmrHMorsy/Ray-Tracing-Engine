#include "IntersectionChecker.h"




class Shader{
    
private:
    
    VectorCalculator * v ;
    std::vector<Output> outputs ;
    std::vector<Light> lights ;
    std::vector<Sphere> spheres ;
    std::vector<Rectangle> rectangles ;
    
public:
    
    Shader( std::vector<Output> _outputs, std::vector<Light> _lights, std::vector<Sphere> _spheres, std::vector<Rectangle> _rectangles ) ;
    std::vector<double> compute_color( std::vector<double> ray, std::vector<double> origin, double time, int k ) ;
    std::vector<double> perform_local_illumination( IntersectionPoint intersection_point, double time, int k, IntersectionChecker * ic ) ;
    std::vector<double> perform_global_illumination( IntersectionPoint intersection_point, double time, int k, int max_depth, IntersectionChecker * ic ) ;
    std::vector<double> generate_random_point() ;
    std::vector<double> build_frame( std::vector<double> origin, std::vector<double> normal, std::vector<double> random_point ) ;
    double compute_shadow( int i, double time, IntersectionPoint p, IntersectionChecker * ic ) ;
    ~Shader() ;
    
} ;
