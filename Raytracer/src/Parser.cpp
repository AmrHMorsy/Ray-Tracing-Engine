#include "Parser.h"



Parser::Parser( nlohmann::json _j )
{
    j = _j ;
}

void Parser::parse_data()
{
    extract_output_info() ;
    extract_lights_info() ;
    extract_spheres_info() ;
    extract_rectangles_info() ;
}

void Parser::extract_output_info()
{
    outputs.resize(j["output"].size()) ;
    auto itr = j["output"].begin() ;
    for( int i = 0 ; i < j["output"].size() ; i++ ){
        outputs[i].filename = j["output"][i]["filename"] ;
        outputs[i].fov = j["output"][i]["fov"] ;
        outputs[i].width = j["output"][i]["size"][0] ;
        outputs[i].height = j["output"][i]["size"][1] ;
        outputs[i].dof = false ;
        
        
        for( int m = 0 ; m < 3 ; m++ ){
            outputs[i].lookat.push_back(j["output"][i]["lookat"][m]) ;
            outputs[i].up.push_back(j["output"][i]["up"][m]) ;
            outputs[i].camera.push_back(j["output"][i]["centre"][m]) ;
            outputs[i].ai.push_back(j["output"][i]["ai"][m]) ;
            outputs[i].bkc.push_back(j["output"][i]["bkc"][m]) ;
        }
        if( (itr->contains("antialiasing")) && (j["output"][i]["antialiasing"] == true) ) {
            outputs[i].antialiasing = j["output"][i]["antialiasing"] ;
            outputs[i].raysperpixel = j["output"][i]["raysperpixel"] ;
        }
        if( (itr->contains("globalillum")) && (j["output"][i]["globalillum"] == true) ){
            outputs[i].globalillum = j["output"][i]["globalillum"] ;
            outputs[i].raysperpixel = j["output"][i]["raysperpixel"] ;
            outputs[i].maxbounces = j["output"][i]["maxbounces"] ;
            outputs[i].probterminate = j["output"][i]["probterminate"] ;
        }
        if( (itr->contains("dof")) && (j["output"][i]["dof"] == true) ){
            outputs[i].dof = true ;
            outputs[i].focus_distance = j["output"][i]["focus_distance"] ;
            outputs[i].aperture_radius = j["output"][i]["aperture_radius"] ;
            outputs[i].raysperpixel = j["output"][i]["raysperpixel"] ;
        }
        if( !( (itr->contains("antialiasing")) && (j["output"][i]["antialiasing"] == true) ) && !( (itr->contains("globalillum")) && (j["output"][i]["globalillum"] == true) ) && !((itr->contains("dof")) && (j["output"][i]["dof"] == true)) ){
            outputs[i].focus_distance = 1 ;
            outputs[i].aperture_radius = 0.0 ;
            outputs[i].antialiasing = false ;
            outputs[i].globalillum = false ;
            outputs[i].raysperpixel = 1 ;
        }
        itr++ ;
    }
}

void Parser::extract_lights_info()
{
    lights.resize(j["light"].size()) ;
    auto itr = j["light"].begin() ;
    for ( int i = 0 ; i < j["light"].size() ; i++ ){
        lights[i].type = j["light"][i]["type"] ;
        if( lights[i].type == "area" ){
            for( int k = 0 ; k < 3 ; k++ ){
                lights[i].p1.push_back(j["light"][i]["p1"][k]) ;
                lights[i].p2.push_back(j["light"][i]["p2"][k]) ;
                lights[i].p3.push_back(j["light"][i]["p3"][k]) ;
                lights[i].p4.push_back(j["light"][i]["p4"][k]) ;
                lights[i].Id.push_back(j["light"][i]["id"][k]) ;
                lights[i].is.push_back(j["light"][i]["is"][k]) ;
            }
            if( itr->contains("n") )
                lights[i].n = j["light"][i]["n"] ;
            else
                lights[i].n = 1 ;
            lights[i].min.push_back(std::min(std::min(lights[i].p1[0],lights[i].p2[0]),std::min(lights[i].p3[0],lights[i].p4[0]))) ;
            lights[i].min.push_back(std::min(std::min(lights[i].p1[1],lights[i].p2[1]),std::min(lights[i].p3[1],lights[i].p4[1]))) ;
            lights[i].min.push_back(std::min(std::min(lights[i].p1[2],lights[i].p2[2]),std::min(lights[i].p3[2],lights[i].p4[2]))) ;
            lights[i].max.push_back(std::max(std::max(lights[i].p1[0],lights[i].p2[0]),std::max(lights[i].p3[0],lights[i].p4[0]))) ;
            lights[i].max.push_back(std::max(std::max(lights[i].p1[1],lights[i].p2[1]),std::max(lights[i].p3[1],lights[i].p4[1]))) ;
            lights[i].max.push_back(std::max(std::max(lights[i].p1[2],lights[i].p2[2]),std::max(lights[i].p3[2],lights[i].p4[2]))) ;
            lights[i].centre.push_back( (lights[i].min[0]+lights[i].max[0]) / 2 ) ;
            lights[i].centre.push_back( (lights[i].min[1]+lights[i].max[1]) / 2 ) ;
            lights[i].centre.push_back( (lights[i].min[2]+lights[i].max[2]) / 2 ) ;
        }
        else{
            for( int k = 0 ; k < 3 ; k++ ){
                lights[i].centre.push_back(j["light"][i]["centre"][k]) ;
                lights[i].Id.push_back(j["light"][i]["id"][k]) ;
                lights[i].is.push_back(j["light"][i]["is"][k]) ;
            }
        }
        itr++ ;
    }
}

void Parser::extract_spheres_info()
{
    int s = 0 ;
    for ( int i = 0 ; i < j["geometry"].size() ; i++ ){
        if( j["geometry"][i]["type"] == "sphere")
            s++ ;
    }
    spheres.resize(s) ;
    s = 0 ;
    auto itr = j["geometry"].begin() ;
    for ( int i = 0 ; i < j["geometry"].size() ; i++ ){
        if( j["geometry"][i]["type"] == "sphere"){
            if( itr->contains("mirror") )
                spheres[s].mirror = j["geometry"][i]["mirror"] ;
            else{
                spheres[s].mirror = false ;
                spheres[s].ka = j["geometry"][i]["ka"] ;
                spheres[s].kd = j["geometry"][i]["kd"] ;
                spheres[s].ks = j["geometry"][i]["ks"] ;
                spheres[s].pc = j["geometry"][i]["pc"] ;
                for( int k = 0 ; k < 3 ; k++ ){
                    spheres[s].ac.push_back(j["geometry"][i]["ac"][k]) ;
                    spheres[s].dc.push_back(j["geometry"][i]["dc"][k]) ;
                    spheres[s].sc.push_back(j["geometry"][i]["sc"][k]) ;
                }
            }
            spheres[s].radius = j["geometry"][i]["radius"] ;
            if( itr->contains("motionblur") )
                spheres[s].motionblur = j["geometry"][i]["motionblur"] ;
            else
                spheres[s].motionblur = false ;
            for( int k = 0 ; k < 3 ; k++ ){
                spheres[s].centre.push_back(j["geometry"][i]["centre"][k]) ;
                spheres[s].r.push_back(spheres[s].radius) ;
            }
            if( spheres[s].motionblur ){
                for( int k = 0 ; k < 3 ; k++ )
                    spheres[s].centre2.push_back(j["geometry"][i]["centre2"][k]) ;
            }
            spheres[s].ID = rand()%1000 ;
            s++ ;
        }
        itr++ ;
    }
}

void Parser::extract_rectangles_info()
{
    int r = 0 ;
    for ( int i = 0 ; i < j["geometry"].size() ; i++ ){
        if( j["geometry"][i]["type"] == "rectangle")
            r++ ;
    }
    rectangles.resize(r) ;
    r = 0 ;
    auto itr = j["geometry"].begin() ;
    for ( int i = 0 ; i < j["geometry"].size() ; i++ ){
        if( j["geometry"][i]["type"] == "rectangle"){
            for ( int k = 0 ; k < 3 ; k++ ){
                rectangles[r].p1.push_back(j["geometry"][i]["p1"][k]) ;
                rectangles[r].p2.push_back(j["geometry"][i]["p2"][k]) ;
                rectangles[r].p3.push_back(j["geometry"][i]["p3"][k]) ;
                rectangles[r].p4.push_back(j["geometry"][i]["p4"][k]) ;
            }
            if( itr->contains("mirror") )
                rectangles[r].mirror = j["geometry"][i]["mirror"] ;
            else{
                rectangles[r].mirror = false ;
                rectangles[r].ka = j["geometry"][i]["ka"] ;
                rectangles[r].kd = j["geometry"][i]["kd"] ;
                rectangles[r].ks = j["geometry"][i]["ks"] ;
                rectangles[r].pc = j["geometry"][i]["pc"] ;
                for ( int k = 0 ; k < 3 ; k++ ){
                    rectangles[r].ac.push_back(j["geometry"][i]["ac"][k]) ;
                    rectangles[r].dc.push_back(j["geometry"][i]["dc"][k]) ;
                    rectangles[r].sc.push_back(j["geometry"][i]["sc"][k]) ;
                }
            }
            rectangles[r].x.push_back(rectangles[r].p1[0]) ;
            rectangles[r].x.push_back(rectangles[r].p2[0]) ;
            rectangles[r].x.push_back(rectangles[r].p3[0]) ;
            rectangles[r].x.push_back(rectangles[r].p4[0]) ;
            rectangles[r].y.push_back(rectangles[r].p1[1]) ;
            rectangles[r].y.push_back(rectangles[r].p2[1]) ;
            rectangles[r].y.push_back(rectangles[r].p3[1]) ;
            rectangles[r].y.push_back(rectangles[r].p4[1]) ;
            rectangles[r].z.push_back(rectangles[r].p1[2]) ;
            rectangles[r].z.push_back(rectangles[r].p2[2]) ;
            rectangles[r].z.push_back(rectangles[r].p3[2]) ;
            rectangles[r].z.push_back(rectangles[r].p4[2]) ;
            rectangles[r].ID = rand()%1000 ;
            r++ ;
        }
        itr++ ;
    }
}

std::vector<Output> Parser::get_output()
{
    return outputs ;
}

std::vector<Light> Parser::get_lights()
{
    return lights ;
}

std::vector<Sphere> Parser::get_spheres()
{
    return spheres ;
}

std::vector<Rectangle> Parser::get_rectangles()
{
    return rectangles ;
}

Parser::~Parser(){}
