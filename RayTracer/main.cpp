#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "TGABuffer.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"


Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane);

void Render(OrthographicCamera camera, TGABuffer& tgaBuffer, Sphere s1)
{
    Ray ray = Ray();


    for (int x = 0; x < camera.GetResX(); x++) {
        for (int y = 0; y < camera.GetResY(); y++) {
            ray = camera.GenerateRay(x, y);
            bool isS1 = s1.Intersect(ray, 0, 100);

            if (isS1 == true) {
                //std::cout << "hit" << std::endl;
                tgaBuffer.SetPixel(x, y, LightIntensity(0.5, 0.5, 0.5));
            }
        }
    }

}

int main(int argv, char** args) {

    OrthographicCamera orthoCam = OrthographicCamera(1024,1024,Vector(0,0,10), Vector(0,0,-1), Vector(0,1,0));

    Sphere s1 = Sphere(Vector(0, 1, 0), 3);
    //Triangle t1 = Triangle(Vector(0, 0, 0), Vector(0, 0.5, 0), Vector(0.5, 0, 0));
    //Plane p1;

    TGABuffer tgaBuffer(orthoCam.GetResX(), orthoCam.GetResY());
    LightIntensity lightIntensity(0.2, 0.4, 0.85);

    tgaBuffer.ClearColor(lightIntensity);
    
    Render(orthoCam, tgaBuffer, s1);

    
    tgaBuffer.WriteTGA("output.tga");


    return 0;
}




Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane) {
    r.Direction.Normalize();
    Vector unitDir = r.Direction;
    Vector IntersectVector(0.0f, 0.0f, 0.0f);
    float t = 0.5f * (unitDir.y + 1.0f);

    if (plane.Intersect(r, 10))
        return Vector(0, 0, 1);

    if (sphere.Intersect(r, 0, 10))
        return Vector(1.0, 0.5, 1.0);


    if (triangle.Intersect(r, IntersectVector))
        return Vector(1.0f, 1.0f, 0.5f);


    return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.5, 0.7, 1.0f) * t;
}


