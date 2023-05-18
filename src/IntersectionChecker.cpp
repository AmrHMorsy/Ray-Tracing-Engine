#include "IntersectionChecker.h"




IntersectionChecker::IntersectionChecker( std::vector<Sphere> sph, std::vector<Rectangle> rect )
{
    spheres = sph ;
    rectangles = rect ;
    v = new VectorCalculator() ;
}

bool IntersectionChecker::check_intersection( std::vector<double> ray, std::vector<double> origin, double time, int ID )
{
    IntersectionPoint sphere_intersection_point = locate_spheres(ray, time, origin, ID) ;
    IntersectionPoint rect_intersection_point = locate_rectangles(ray,origin, time, ID) ;
    
    if( sphere_intersection_point.dist < rect_intersection_point.dist ){
        point = sphere_intersection_point ;
        return true ;
    }
    else if( rect_intersection_point.dist < sphere_intersection_point.dist ){
        point = rect_intersection_point ;
        return true ;
    }
    else
        return false ;
}

IntersectionPoint IntersectionChecker::locate_spheres( std::vector<double> ray, double time, std::vector<double> origin, int ID )
{
    double dist, a, b, c, det, t ;
    std::vector<double> centre, tmp, p ;
    IntersectionPoint sphere_intersection_point ;
    
    sphere_intersection_point.dist = std::numeric_limits<double>::max() ;
    a = v->dot(ray, ray) ;
    for( int i = 0 ; i < spheres.size() ; i++ ){
        if( ID == spheres[i].ID )
            continue ; 
        if( spheres[i].motionblur )
            centre = v->add(spheres[i].centre,v->multiply(v->subtract(spheres[i].centre2,spheres[i].centre), time)) ;
        else
            centre = spheres[i].centre ;
        tmp = v->subtract(origin,centre) ;
        c = ((v->dot(tmp,tmp))-(spheres[i].radius*spheres[i].radius)) ;
        b = v->dot(v->multiply(tmp,2.0),ray) ;
        det = (b*b)-(4*a*c) ;
        if( det > 0 ){
            t = std::min((((-1*b)+(sqrt(det)))/(2*a)),(((-1*b)-(sqrt(det)))/(2*a))) ;
            if( t > 0 ){
                p = v->add(origin, v->multiply(ray,t)) ;
                dist = v->magnitude(v->subtract(p,ray)) ;
                if( dist < sphere_intersection_point.dist )
                    sphere_intersection_point.fill(dist,p,spheres[i].dc,spheres[i].ac,spheres[i].sc,spheres[i].ka,spheres[i].kd,spheres[i].ks,spheres[i].pc,spheres[i].ID,spheres[i].mirror,v->normalize(v->subtract(p,centre))) ;
            }
        }
    }
    return sphere_intersection_point ;
}

IntersectionPoint IntersectionChecker::locate_rectangles( std::vector<double> ray, std::vector<double> origin, double time, int ID)
{
    double dist, t ;
    std::vector<double> normal, p ;
    IntersectionPoint rect_intersection_point ;

    rect_intersection_point.dist = std::numeric_limits<double>::max() ;
    for( int i = 0 ; i < rectangles.size() ; i++ ){
        if( ID == rectangles[i].ID )
            continue ;
        normal = v->normalize(v->cross(v->subtract(rectangles[i].p2,rectangles[i].p1),v->subtract(rectangles[i].p3,rectangles[i].p2))) ;
        t = v->dot(normal,ray) ;
        if( t!= 0 ){
            t = ((v->dot(normal,rectangles[i].p1))-(v->dot(normal,origin))) / t ;
            p = v->add(origin, v->multiply(ray,t)) ;
            if( (v->dot(normal,v->cross(v->subtract(rectangles[i].p3,rectangles[i].p2),v->subtract(p,rectangles[i].p2)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p4,rectangles[i].p3),v->subtract(p,rectangles[i].p3)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p2,rectangles[i].p1),v->subtract(p,rectangles[i].p1)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p1,rectangles[i].p4),v->subtract(p,rectangles[i].p4)))>0) ){
                dist = v->magnitude(v->subtract(p,origin)) ;
                if( dist < rect_intersection_point.dist )
                    rect_intersection_point.fill(dist, p, rectangles[i].dc, rectangles[i].ac, rectangles[i].sc, rectangles[i].ka, rectangles[i].kd, rectangles[i].ks, rectangles[i].pc, rectangles[i].ID, rectangles[i].mirror, normal) ;
            }
        }
    }

    return rect_intersection_point ;
}

bool IntersectionChecker::ishit_sphere( std::vector<double> ray, double time, IntersectionPoint p )
{
    double a, b, c, det, t ;
    std::vector<double> tmp, centre ;
    
    a = v->dot(ray, ray) ;
    for( int i = 0 ; i < spheres.size() ; i++ ){
        if( spheres[i].motionblur )
            centre = v->add(spheres[i].centre,v->multiply(v->subtract(spheres[i].centre2,spheres[i].centre), time)) ;
        else
            centre = spheres[i].centre ;
        if( p.ID == spheres[i].ID )
            continue ;
        tmp = v->subtract(p.point,centre) ;
        c = (v->dot(tmp,tmp)) - (spheres[i].radius*spheres[i].radius) ;
        b = v->dot(v->multiply(tmp,2.0),ray) ;
        det = (b*b)-(4*a*c) ;
        t = std::min((((-1*b)+(sqrt(det)))/(2*a)),(((-1*b)-(sqrt(det)))/(2*a))) ;
        if( (det>0) && (t > 0 ) )
            return true ;
    }
    return false ;
}

bool IntersectionChecker::ishit_rectangle( std::vector<double> ray, IntersectionPoint ip )
{
    double t ;
    std::vector<double> normal, p ;
    
    for( int i = 0 ; i < rectangles.size() ; i++ ){
        if( ip.ID == rectangles[i].ID )
            continue ;
        normal = v->normalize(v->cross(v->subtract(rectangles[i].p2,rectangles[i].p1),v->subtract(rectangles[i].p3,rectangles[i].p2))) ;
        t = v->dot(normal,ray) ;
        if( t < 0 )
            continue ;
        if( t != 0 ){
            t = ((v->dot(normal,rectangles[i].p1))-(v->dot(normal,ip.point))) / t ;
            if( t > 0 ){
                p = v->add(ip.point, v->multiply(ray,t)) ;
                if( (v->dot(normal,v->cross(v->subtract(rectangles[i].p3,rectangles[i].p2),v->subtract(p,rectangles[i].p2)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p4,rectangles[i].p3),v->subtract(p,rectangles[i].p3)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p2,rectangles[i].p1),v->subtract(p,rectangles[i].p1)))>0) && (v->dot(normal,v->cross(v->subtract(rectangles[i].p1,rectangles[i].p4),v->subtract(p,rectangles[i].p4)))>0) )
                return true ;
            }
        }
    }
    return false ;
}

IntersectionPoint IntersectionChecker::get_intersection_point()
{
    return point ;
}

IntersectionChecker::~IntersectionChecker()
{
    delete v ;
    v = NULL ; 
}
