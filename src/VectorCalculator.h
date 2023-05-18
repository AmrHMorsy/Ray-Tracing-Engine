#include "Includes.h"





class VectorCalculator
{
 
public:
    
    VectorCalculator() ;
    std::vector<double> set( double x, double y, double z) ; 
    std::vector<double> initialize( std::vector<double> A, double B ) ; 
    std::vector<double> add( std::vector<double> A, std::vector<double> B ) ;
    double dot( std::vector<double> A, std::vector<double> B ) ;
    std::vector<double> cross( std::vector<double> A, std::vector<double> B ) ;
    std::vector<double> multiply( std::vector<double> A, double B ) ;
    std::vector<double> subtract( std::vector<double> A, std::vector<double> B ) ;
    std::vector<double> normalize( std::vector<double> A ) ; 
    double magnitude( std::vector<double> A ) ;
    std::vector<double> hadamard_product( std::vector<double> A, std::vector<double> B ) ;
    std::vector<double> clamp( std::vector<double> A ) ;
    std::vector<double> add_scalar( std::vector<double> A, double scalar ) ;
    double clamp_value( double a ) ;
    double generate_random_number( double min, double max ) ;
    std::vector<double> Multiply( std::vector<std::vector<double>> M, std::vector<double> p ) ;
    std::vector<double> power( std::vector<double> A, double p ) ;
    ~VectorCalculator() ;
    
} ;
