#include "VectorCalculator.h"




class Parser
{
    
private:
    
    nlohmann::json j ;
    std::vector<Output> outputs ;
    std::vector<Light> lights ;
    std::vector<Sphere> spheres ;
    std::vector<Rectangle> rectangles ;

public:
    
    Parser( nlohmann::json _j ) ;
    void parse_data() ;
    void extract_info() ;
    void extract_spheres_info() ;
    void extract_lights_info() ;
    void extract_rectangles_info() ;
    void extract_output_info() ;
    std::vector<Light> get_lights() ;
    std::vector<Sphere> get_spheres() ;
    std::vector<Rectangle> get_rectangles() ;
    std::vector<Output> get_output() ;
    ~Parser() ;

} ;
