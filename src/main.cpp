#include "Raytracer.h"

    

int main(int argc, char* argv[])
{
    if( argc != 2 ){
        std::cout<< "\n\033[1;31mInvalid number of arguments\033[0m" << std::endl;
        std::cout<< "\033[1;31mAt least one model JSON file path must be provided !\033[0m\n" << std::endl;
        return 1 ;
    }
    
    Raytracer rt(argv[1]) ;
    rt.run() ;
    
    return 0;
}
