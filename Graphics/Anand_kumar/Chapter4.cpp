#include<iostream>
#include<fstream>
#include"ray.h"

using namespace std;

bool hit_sphere(const vec3 &center , float radius , const ray &r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction() , r.direction());
    float b = 2.0*dot( oc , r.direction());
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return ( discriminant > 0);
}

vec3 color(const ray &r){
    if(hit_sphere(vec3(0.0,0.0,-1.0) , 0.5 , r)){
        return vec3(1,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0 , 1.0 , 1.0) + t*vec3(0.5 , 0.7 , 1.0);
}

int main(){
    int x = 200;
    int y = 100;
    ofstream ostream;
    ostream.open("Chapter4.ppm");
    ostream << "P3\n" << x << " " << y << "\n255\n";
    vec3 bottom_left_corner(-2.0 , -1.0 , -1.0);
    vec3 horizonal(4.0 , 0.0 , 0.0);
    vec3 vertical(0.0 , 2.0 , 0.0);
    vec3 origin(0.0 , 0.0 , 0.0);
    for(int j = y-1 ; j >= 0 ; j--){
        for(int i = 0 ; i < x ; i++){
            float u = float(i)/float(x);
            float v = float(j)/float(y);
            ray r(origin , bottom_left_corner + u*horizonal + v*vertical);
            vec3 colors = color(r);
            int ir = int(255.99*colors[0]);
            int ig = int(255.99*colors[1]);
            int ib = int(255.99*colors[2]);

            ostream << ir << " " << ig << " " << ib << "\n";
        }
    }
    ostream.close();
    return 0;
}
