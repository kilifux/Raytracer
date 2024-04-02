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
#include "Scene.h"
#include <vector>


Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane) {
    r.Direction.Normalize();
    Vector unitDir = r.Direction;
    Vector IntersectVector(0.0f, 0.0f, 0.0f);
    float t = 0.5f * (unitDir.y + 1.0f);

    if (plane.Intersect(r))
        return Vector(0, 0, 1);

    //if (sphere.Intersect(r))
        //return sphere.colour;


    if (triangle.Intersect(r, IntersectVector))
        return Vector(1.0f, 1.0f, 0.5f);


    return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.5, 0.7, 1.0f) * t;
}

Vector IntersectObjects(std::shared_ptr<Scene> scene, Ray ray) {
    //std::cout << ray.Direction << std::endl;

    float closestDistance = -1000;
    bool check = false;
    std::shared_ptr<Object> closestObject;

    for (int i = 0; i < scene->objects.size(); i++) {
        std::shared_ptr<Object> obj = scene->objects[i];
        Vector dist = obj->Intersect(ray);
        //std::cout << "dist " << dist << std::endl;

        if (dist.z > -999) {
            //std::cout << dist << " < " << closestDistance << std::endl;
            if (dist.GetLength() > closestDistance) {
                //std::cout << "change closest " << std::endl;
                closestDistance = dist.GetLength();
                closestObject = obj;
                check = true;
            }
        }
    }

    if (check) {
        return closestObject->GetMaterial().GetColour();
    }
    else {
        return Vector(0.2, 0.4, 0.85);
    }
}

Vector getColour(std::shared_ptr<Scene> scene, float x, float y, int resX, int resY) {

    Vector color = { 0, 0, 0 };
    Ray ray = scene->camera->GenerateRay(x, y);

    Vector colour = IntersectObjects(scene, ray);

    color = colour;

    return color;
}

Vector Sampling(std::shared_ptr<Scene> scene, int x, int y, int resX, int resY, int maxSteps, float centreX, float centreY, float offset) {

    Vector colour = Vector(0, 0, 0);
    Vector centreColour = Vector(0, 0, 0);
    std::vector<Vector> tempColours;
    tempColours.clear();

    centreColour = getColour(scene, x + centreX, y + centreY, resX, resY);
    //std::cout << x + centreX << " " << x + (centreX - offset) << " " << x + (centreX + offset) << std::endl;
    tempColours.push_back(getColour(scene, x + (centreX - offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(scene, x + (centreX + offset), y + (centreY - offset), resX, resY));
    tempColours.push_back(getColour(scene, x + (centreX - offset), y + (centreY + offset), resX, resY));
    tempColours.push_back(getColour(scene, x + (centreX + offset), y + (centreY + offset), resX, resY));

    if (maxSteps > 1) {
        if ((tempColours[0] - centreColour).GetLength() > 0.4) {
            //std::cout << "0" << std::endl;
            tempColours[0] = Sampling(scene, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[0] = (Vector)(tempColours[0] + centreColour) * 0.5;
        }
        if ((tempColours[1] - centreColour).GetLength() > 0.4) {
            //std::cout << "1" << std::endl;
            tempColours[1] = Sampling(scene, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[1] = (Vector)(tempColours[1] + centreColour) * 0.5;
        }
        if ((tempColours[2] - centreColour).GetLength() > 0.4) {
            //std::cout << "2" << std::endl;
            tempColours[2] = Sampling(scene, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColours[2] = (Vector)(tempColours[2] + centreColour) * 0.5;
        }
        if ((tempColours[3] - centreColour).GetLength() > 0.4) {
            //std::cout << "3" << std::endl;
            tempColours[3] = Sampling(scene, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, +offset * 0.5f, offset * 0.5f);
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

void Render(std::shared_ptr<Scene> scene, TGABuffer& tgaBuffer)
{
    Ray ray = Ray();
    Vector colour = Vector(0, 0, 0);

    std::cout << "render" << std::endl;
    for (int x = 0; x < scene->camera->GetResolutionX(); x++) {
        for (int y = 0; y < scene->camera->GetResolutionY(); y++) {

            colour = Sampling(scene, x, y, scene->camera->GetResolutionX(), scene->camera->GetResolutionY(), 5, 0.0f, 0.0f, 0.5f);
            tgaBuffer.SetPixel(x, y, LightIntensity(colour.x, colour.y, colour.z));

        }
    }

}




int main(int argv, char** args) {

    //make scene
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();


    //make cameras
    std::shared_ptr<OrthographicCamera> orthoCam = std::make_shared<OrthographicCamera>(512, 512, Vector(0,0,5), Vector(0,0,-1), Vector(0,1,0));
    std::shared_ptr<PerspectiveCamera> perspCam = std::make_shared<PerspectiveCamera>(512,512, 50.0f, 90.0f, Vector(0, 0, 5), Vector(0, 0, -1), Vector(0, 1, 0));

    std::shared_ptr<Camera> camera = perspCam;

    scene->camera = camera;


    //make objects
    //dont know why but to move sphere up in orthographic camera you have to put -1 intead of 1
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector(-0.25, -0.25, 0), 0.5, Material(Vector(0.9f, 0.9f, 0.9f)));
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector(0.25, 0, 0), 0.5, Material(Vector(0.2f, 0.7f, 0.9f)));
    //std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector(-0.5, -0.75, -20), 0.5, Vector(0.5f, 0.2f, 0.1f));

    scene->objects.push_back(sphere1);
    scene->objects.push_back(sphere2);
    //scene->objects.push_back(sphere3);

    //make buffer
    TGABuffer tgaBuffer(camera->GetResolutionX(), camera->GetResolutionY());
    LightIntensity lightIntensity(0.2, 0.4, 0.85);

    tgaBuffer.ClearColor(lightIntensity);

    //render
    Render(scene, tgaBuffer);
    //Render(scene, tgaBuffer, s2, s1);
    
    tgaBuffer.WriteTGA("output.tga");


    return 0;
}




