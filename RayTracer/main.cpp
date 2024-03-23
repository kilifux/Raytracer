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

Vector getColour(std::shared_ptr<Camera> camera, Sphere sphere, Sphere s2, float x, float y, int resX, int resY) {

    Vector color = { 0, 0, 0 };
    Ray nRay = camera->GenerateRay(x, y);

    bool intersect = sphere.Intersect(nRay, 0.1f, 100.0f);

    if (intersect) {

        color = color + sphere.colour;
        //std::cout << color << std::endl;

    }
    else if (s2.Intersect(nRay, 0.1f, 100.0f))
    {
        color = color + s2.colour;
        //std::cout << "hit" << std::endl;
    }
    else {
        color = color + Vector(0.2, 0.2, 0.2);
    }

    return color;
}

Vector Sampling(std::shared_ptr<Camera> camera, Sphere sphere, Sphere s2, int x, int y, int resX, int resY, int maxSteps, float centreX, float centreY, float offset) {

    Vector colour = Vector(0, 0, 0);
    Vector centreColour = Vector(0, 0, 0);
    std::vector<Vector> tempColours;
    tempColours.clear();

    centreColour = getColour(camera, sphere, s2, x + centreX, y + centreY, resX, resY);
    //std::cout << x + centreX << " " << x + (centreX - offset) << " " << x + (centreX + offset) << std::endl;
    tempColours.push_back(getColour(camera, sphere, s2, x + (centreX - offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, s2, x + (centreX + offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, s2, x + (centreX - offset), y + (centreY + offset), resX, resY));
    tempColours.push_back(getColour(camera, sphere, s2, x + (centreX + offset), y + (centreY + offset), resX, resY));

    if (maxSteps > 1) {
        if ((tempColours[0] - centreColour).GetLength() > 0.4) {
            //std::cout << "0" << std::endl;
            tempColours[0] = Sampling(camera, sphere, s2, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[0] = (Vector)(tempColours[0] + centreColour) * 0.5;
        }
        if ((tempColours[1] - centreColour).GetLength() > 0.4) {
            //std::cout << "1" << std::endl;
            tempColours[1] = Sampling(camera, sphere, s2, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[1] = (Vector)(tempColours[1] + centreColour) * 0.5;
        }
        if ((tempColours[2] - centreColour).GetLength() > 0.4) {
            //std::cout << "2" << std::endl;
            tempColours[2] = Sampling(camera, sphere, s2, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[2] = (Vector)(tempColours[2] + centreColour) * 0.5;
        }
        if ((tempColours[3] - centreColour).GetLength() > 0.4) {
            //std::cout << "3" << std::endl;
            tempColours[3] = Sampling(camera, sphere, s2, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, +offset * 0.5f, offset * 0.5f);
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

void Render(std::shared_ptr<Camera> camera, TGABuffer& tgaBuffer, Sphere s1, Sphere s2)
{
    Ray ray = Ray();
    Vector colour = Vector(0, 0, 0);

    std::cout << "render" << std::endl;
    for (int x = 0; x < camera->GetResolutionX(); x++) {
        for (int y = 0; y < camera->GetResolutionY(); y++) {
            ray = camera->GenerateRay(x, y);
            bool isS1 = s1.Intersect(ray, 0, 100);
            //std::cout << "here" << std::endl;
            if (isS1 == true) {
                //std::cout << "hit" << std::endl;
                colour = Sampling(camera, s1, s2, x, y, camera->GetResolutionX(), camera->GetResolutionY(), 5, 0.0f, 0.0f, 0.5f);
                tgaBuffer.SetPixel(x, y, LightIntensity(colour.x, colour.y, colour.z));
            }
        }
    }

}


int main(int argv, char** args) {

    std::shared_ptr<OrthographicCamera> orthoCam = std::make_shared<OrthographicCamera>(1024,1024,Vector(0,0,10), Vector(0,0,-1), Vector(0,1,0));
    std::shared_ptr<PerspectiveCamera> perspCam = std::make_shared<PerspectiveCamera>(1024,1024, 100.0f, 90.0f, Vector(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0));

    std::shared_ptr<Camera> camera = perspCam;

    //dont know why but to move sphere up in orthographic camera you have to put -1 intead of 1
    Sphere s1 = Sphere(Vector(0, 0, -10), 1.5, Vector(0.5f,0.1f,0.3f));
    Sphere s2 = Sphere(Vector(0.5, 0, -20), 1.5, Vector(0.2f,0.7f,0.9f));
    //Triangle t1 = Triangle(Vector(0, 0, 0), Vector(0, 0.5, 0), Vector(0.5, 0, 0));
    //Plane p1;

    TGABuffer tgaBuffer(camera->GetResolutionX(), camera->GetResolutionY());
    LightIntensity lightIntensity(0.2, 0.2, 0.2);

    tgaBuffer.ClearColor(lightIntensity);

    
    Render(camera, tgaBuffer, s1, s2);
    Render(camera, tgaBuffer, s2, s1);
    
    tgaBuffer.WriteTGA("output.tga");


    return 0;
}




