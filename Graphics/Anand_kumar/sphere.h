#include"hitable.h"
#include<iostream>

class sphere : public hitable{
    public:
        sphere() {}
        sphere(vec3 cen , float r , material *material2) : center(cen) , radius(r) , material1(material2){}
        virtual bool hit(const ray &r , float tmin , float tmax , hit_record &rec) const;
        vec3 center;
        float radius;
        material *material1;
};

bool sphere::hit(const ray &r , float t_min , float t_max , hit_record &rec) const{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction() , r.direction());
    float b = dot( oc , r.direction());
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - a*c;
    if(discriminant > 0){
        float temp = ( -b - sqrt(discriminant))/a;
        if ( temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/radius;
            rec.mat_ptr = material1;
            return true;
        }
        temp = ( -b + sqrt(discriminant))/a;
        if ( temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/radius;
            rec.mat_ptr = material1;
            return true;
        }
    }
    return false;
}