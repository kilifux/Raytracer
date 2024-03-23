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
#include "Camera.h"
#include <vector>


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
                tgaBuffer.SetPixel(x, y, LightIntensity(s1.colour.x,s1.colour.y,s1.colour.z));
            }
        }
    }

}

Vector getColour(PerspectiveCamera camera, Sphere sphere, int x, int y, int resX, int resY) {
    
    Vector color = { 0, 0, 0 };
    Ray nRay = camera.GenerateRay(x,y);

    bool intersect = sphere.Intersect(nRay, 0.1f, 100.0f);

    if (intersect) {

        color = color + sphere.colour;

    }
    else
    {
        color = color + Vector(0.5,0.5,0.5);
    }

    return color;
}

Vector Sampling(PerspectiveCamera camera, Sphere sphere, int x, int y, int resX, int resY, int maxSteps, float centreX, float centreY, float offset) {

    Vector colour = Vector(0, 0, 0);
    Vector centreColour = Vector(0, 0, 0);
    std::vector<Vector> tempColours;
    tempColours.clear();

    centreColour = getColour(camera, sphere, x + centreX, y + centreY, resX, resY);

    tempColours.push_back(getColour(camera, sphere, x + (centreX - offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, x + (centreX + offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, x + (centreX - offset), y + (centreY + offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, x + (centreX + offset), y + (centreY + offset), resX, resY));

    if (maxSteps > 1) {
        if ((tempColours[0] - centreColour).GetLength() > 0.4) {
            std::cout << "0" << std::endl;
            tempColours[0] = Sampling(camera, sphere, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[0] = (Vector)(tempColours[0] + centreColour) * 0.5;
        }
        if ((tempColours[1] - centreColour).GetLength() > 0.4) {
            std::cout << "1" << std::endl;
            tempColours[1] = Sampling(camera, sphere, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[1] = (Vector)(tempColours[1] + centreColour) * 0.5;
        }
        if ((tempColours[2] - centreColour).GetLength() > 0.4) {
            std::cout << "2" << std::endl;
            tempColours[2] = Sampling(camera, sphere, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[2] = (Vector)(tempColours[2] + centreColour) * 0.5;
        }
        if ((tempColours[3] - centreColour).GetLength() > 0.4) {
            std::cout << "3" << std::endl;
            tempColours[3] = Sampling(camera, sphere, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[3] = (Vector)(tempColours[3] + centreColour) * 0.5;
        }
    }


    for (auto c : tempColours) {
        colour = colour + c;
    }

    colour = colour / tempColours.size();

    return colour;

}

void Sampling(OrthographicCamera camera, Sphere sphere, int x, int y, int resX, int resY, int maxSteps, float centreX, float centreY, float offset) {

    Vector colour = sphere.colour;
    std::vector<Vector> tempColours;

}

void Render(PerspectiveCamera camera, TGABuffer& tgaBuffer, Sphere s1)
{
    Ray ray = Ray();
    Vector colour = Vector(0, 0, 0);

    std::cout << "render" << std::endl;
    for (int x = 0; x < camera.GetResX(); x++) {
        for (int y = 0; y < camera.GetResY(); y++) {
            ray = camera.GenerateRay(x, y);
            bool isS1 = s1.Intersect(ray, 0, 100);

            if (isS1 == true) {
                //std::cout << "hit" << std::endl;
                colour = Sampling(camera, s1, x, y, camera.GetResX(), camera.GetResY(), 5, 0.0f, 0.0f, 0.5f);
                tgaBuffer.SetPixel(x, y, LightIntensity(colour.x, colour.y, colour.z));
            }
        }
    }

}

int main(int argv, char** args) {

    OrthographicCamera orthoCam = OrthographicCamera(1024,1024,Vector(0,0,10), Vector(0,0,-1), Vector(0,1,0));
    PerspectiveCamera perspCam = PerspectiveCamera(1024,1024, 0.1f, 100, 45.0f, Vector(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0));

    //dont know why but to move sphere up in orthographic camera you have to put -1 intead of 1
    Sphere s1 = Sphere(Vector(0, 0, -10), 1.5, Vector(0.5f,0.1f,0.3f));
    Sphere s2 = Sphere(Vector(0.5, -1, -20), 1.5, Vector(0.2f,0.7f,0.9f));
    //Triangle t1 = Triangle(Vector(0, 0, 0), Vector(0, 0.5, 0), Vector(0.5, 0, 0));
    //Plane p1;

    TGABuffer tgaBuffer(orthoCam.GetResX(), orthoCam.GetResY());
    LightIntensity lightIntensity(0.2, 0.4, 0.85);

    tgaBuffer.ClearColor(lightIntensity);

    
    //Render(orthoCam, tgaBuffer, s1);
    //Render(orthoCam, tgaBuffer, s2);
    Render(perspCam, tgaBuffer, s1);
    Render(perspCam, tgaBuffer, s2);
    
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
        return sphere.colour;


    if (triangle.Intersect(r, IntersectVector))
        return Vector(1.0f, 1.0f, 0.5f);


    return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.5, 0.7, 1.0f) * t;
}


