#include "../external/json.hpp"
#include <iostream>
#include "../external/progressbar.h"
#include <vector>
#include <math.h> 
#include <limits>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include "/usr/local/opt/libomp/include/omp.h"


#define FOCAL_LENGTH 1
#define PI 3.14159265359
#define MAX_REFLECTION_DEPTH 1
#define GAMMA 2.2


struct BoundingBox{
    std::vector<double> min, max ;
} ;

struct Output{
    int raysperpixel ;
    bool antialiasing, globalillum, dof ;
    std::string filename ;
    double fov, width, height, maxbounces, probterminate, aperture_radius, focus_distance ;
    std::vector<double> lookat, up, camera, ai, bkc ;
} ;

struct Light{
    double n ;
    std::string type ;
    std::vector<double> centre, Id, is, p1, p2, p3, p4, min, max ; 
} ;

struct Sphere{
    bool mirror ;
    int ID ;
    bool motionblur ;
    double radius, ka, kd, ks, pc ;
    std::vector<double> centre, ac, dc, sc, r, centre2 ;
} ;

struct Rectangle{
    int ID ;
    bool mirror ; 
    double ka, kd, ks, pc ;
    std::vector<double> p1, p2, p3, p4, ac, dc, sc, x, y, z ; 
} ;
 
struct IntersectionPoint{
    bool mirror ; 
    int ID ;
    double dist, ka, kd, ks, pc ; 
    std::vector<double> point, normal, ac, dc, sc, view ; 
    void fill( double dist, std::vector<double> p, std::vector<double> dc, std::vector<double> ac, std::vector<double> sc, double ka, double kd, double ks, double pc, int ID, bool mirror, std::vector<double> normal){
        this->dist = dist ; point = p ;
        this->dc = dc ; this->ac = ac ;
        this->sc = sc ; this->ka = ka ;
        this->kd = kd ; this->ks = ks ;
        this->pc = pc ; this->ID = ID ;
        this->mirror = mirror ; this->normal = normal ;
    }
} ;
