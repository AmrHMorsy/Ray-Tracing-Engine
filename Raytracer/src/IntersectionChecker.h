#include "Parser.h"




class IntersectionChecker{
    
private:
    
    VectorCalculator * v ;
    IntersectionPoint point ;
    std::vector<Sphere> spheres ;
    std::vector<Rectangle> rectangles ;
    
public:
    
    IntersectionChecker( std::vector<Sphere> sph, std::vector<Rectangle> rect ) ;
    bool check_intersection( std::vector<double> ray, std::vector<double> origin, double time, int ID ) ;
    IntersectionPoint locate_spheres( std::vector<double> ray, double time, std::vector<double> origin, int ID ) ;
    IntersectionPoint locate_rectangles( std::vector<double> ray, std::vector<double> origin, double time, int ID) ;
    bool ishit_sphere( std::vector<double> ray, double time, IntersectionPoint p ) ;
    bool ishit_rectangle( std::vector<double> ray, IntersectionPoint ip ) ;
    IntersectionPoint get_intersection_point() ;
    ~IntersectionChecker() ;
    
} ;
