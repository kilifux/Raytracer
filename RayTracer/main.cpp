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
#include "PointLight.h"
#include <algorithm>
#include <random>


#define M_PI 3.14159265358979323846

Vector Reflect(Vector I, Vector N)
{
    return I - N * 2 * I.dotProduct(N);
}


Vector Refract(Vector I, Vector N, const float& ior)
{

    float cosi = std::fmin(-I.dotProduct(N), 1.0f);

    Vector r_out_perp = (I + N * cosi) * ior;
    Vector r_out_parallel = N * -sqrt(fabs(1.0f - r_out_perp.GetLength() * r_out_perp.GetLength()));
    return r_out_perp + r_out_parallel;

}

void IntersectObjects(std::shared_ptr<Scene> scene, Ray ray, std::shared_ptr<Object>& closestObject, int& nr, int& nr2) {
    
    float closestDistance = 1000;
    bool check = false;
    bool check2 = false;
    Vector intersectionPoint;

    for (int i = 0; i < scene->objects.size(); i++) {

        std::shared_ptr<Object> obj = scene->objects[i];
        Vector distance = obj->Intersect(ray); //distance to nie punkt przeciecia

        if (distance.z != -1000.0f && nr != i && nr2 != i) {

            if (distance.z < closestDistance) {
                closestDistance = distance.z;
                closestObject = obj;
                intersectionPoint = obj->GetIntersectionPoint();
                nr = i;
                check = true;
            }
        }
    }

    if (closestObject == nullptr)
        return;


    if (scene->reflectionNumber > 0) {

        //scene->reflectionNumber = scene->reflectionNumber - 1;
        for (int k = 0; k < scene->reflectionNumber; k++) {
            if (closestObject->material.refractFraction > 0.001f) {
                //std::cout << closestObject->GetIntersectionPoint() << std::endl;
                Ray rr = Ray(closestObject->GetIntersectionPoint(), Refract(ray.Direction.Normalize(), closestObject->GetIntersectionNormal(), closestObject->material.refractFraction));
                nr2 = nr;
                nr = -1;
                IntersectObjects(scene, rr, closestObject, nr, nr2);
            }
        }




        for (int k = 0; k < scene->reflectionNumber; k++) {
            if (closestObject->material.reflectFraction > 0.001f) {
                Ray r = Ray(closestObject->GetIntersectionPoint(), Reflect(ray.Direction, closestObject->GetIntersectionNormal()));
                nr2 = nr;
                nr = -1;
                IntersectObjects(scene, r, closestObject, nr, nr2);

                //closestObject->material = Material(Vector(1.0f, 1.0f, 1.0f), 128, 1, 0, 0);
            }
        }
    }
    


}

Vector getRandomDirectionHemisphere(Vector& normal) {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    // Generowanie losowego kierunku w p�kuli za pomoc� r�wnomiernego rozk�adu punkt�w na sferze
    float u1 = distribution(generator);
    float u2 = distribution(generator);

    float r = sqrt(1.0f - u1 * u1); // promie� ko�a w p�kuli
    float phi = 2 * M_PI * u2; // k�t fi w zakresie [0, 2*PI]

    // Konwersja wsp�rz�dnych sferycznych na kartezja�skie
    float x = r * cos(phi);
    float y = r * sin(phi);
    float z = u1;

    // Obliczenie kierunku na podstawie normalnej powierzchni
    Vector tangent, bitangent;
    if (fabs(normal.x) < fabs(normal.y)) {
        tangent = Vector(1.0f, 0.0f, 0.0f);
    }
    else {
        tangent = Vector(0.0f, 1.0f, 0.0f);
    }
    tangent = (tangent - normal * normal.dotProduct(tangent)).Normalize();
    bitangent = normal.cross(tangent).Normalize();

    // Wygenerowanie losowego wektora w lokalnym uk�adzie wsp�rz�dnych
    return (tangent * x + bitangent * y + normal * z).Normalize();
}

Vector getColour(std::shared_ptr<Scene> scene, Ray ray, int depth) {

    if (depth <= 0) {
        return Vector(0, 0, 0);
    }

    Vector color = { 0, 0, 0 };

    std::shared_ptr<Object> closestObject;
    int nr = -1;
    int nr2 = -1;
    scene->reflectionNumber = 2;
    IntersectObjects(scene, ray, closestObject, nr, nr2);

    if (closestObject != nullptr) { 

        Vector colorMaterial = closestObject->GetMaterial().GetColour();
        Vector intersectionPoint = closestObject->GetIntersectionPoint();
        Vector normal = closestObject->GetIntersectionNormal();

        int numRays = 32;
        Vector indirectLighting = Vector(0, 0, 0);

        for (int i = 0; i < numRays; ++i) {
            Vector randomDirection = getRandomDirectionHemisphere(normal);
            Ray indirectRay(intersectionPoint, randomDirection);
            indirectLighting = indirectLighting + getColour(scene, indirectRay, depth - 1); 
        }

        indirectLighting = indirectLighting / numRays;

        color = color + scene->Light(closestObject->GetIntersectionPoint(), closestObject, ray.Direction.Normalize(), nr);
       
        color.x = color.x * colorMaterial.x;
        color.y = color.y * colorMaterial.y;
        color.z = color.z * colorMaterial.z;

        Vector finalColor = (indirectLighting + color);

        return finalColor;

    }
    else {
        return Vector(0.2, 0.4, 0.85);
    }
}

Vector Sampling(std::shared_ptr<Scene> scene, int x, int y, int resX, int resY, int maxSteps, float centreX, float centreY, float offset) {

    int depth = 2;
    Vector colour = Vector(0, 0, 0);
    Vector centreColour = Vector(0, 0, 0);
    std::vector<Vector> tempColours;
    tempColours.clear();

    centreColour = getColour(scene, scene->camera->GenerateRay(x + centreX, y + centreY), depth);
    //std::cout << x + centreX << " " << x + (centreX - offset) << " " << x + (centreX + offset) << std::endl;
    tempColours.push_back(getColour(scene, scene->camera->GenerateRay(x + (centreX - offset), y + (centreY - offset)), depth));
    tempColours.push_back(getColour(scene, scene->camera->GenerateRay(x + (centreX + offset), y + (centreY - offset)), depth));
    tempColours.push_back(getColour(scene, scene->camera->GenerateRay(x + (centreX - offset), y + (centreY + offset)), depth));
    tempColours.push_back(getColour(scene, scene->camera->GenerateRay(x + (centreX + offset), y + (centreY + offset)), depth));

    //if (maxSteps > 1) {
    //    if ((tempColours[0] - centreColour).GetLength() > 0.4) {
    //        //std::cout << "0" << std::endl;
    //        tempColours[0] = Sampling(scene, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, -offset * 0.5f, offset * 0.5f);
    //    }
    //    else {
    //        tempColours[0] = (Vector)(tempColours[0] + centreColour) * 0.5;
    //    }
    //    if ((tempColours[1] - centreColour).GetLength() > 0.4) {
    //        //std::cout << "1" << std::endl;
    //        tempColours[1] = Sampling(scene, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, -offset * 0.5f, offset * 0.5f);
    //    }
    //    else {
    //        tempColours[1] = (Vector)(tempColours[1] + centreColour) * 0.5;
    //    }
    //    if ((tempColours[2] - centreColour).GetLength() > 0.4) {
    //        //std::cout << "2" << std::endl;
    //        tempColours[2] = Sampling(scene, x, y, resX, resY, maxSteps - 1, -offset * 0.5f, +offset * 0.5f, offset * 0.5f);
    //    }
    //    else {
    //        tempColours[2] = (Vector)(tempColours[2] + centreColour) * 0.5;
    //    }
    //    if ((tempColours[3] - centreColour).GetLength() > 0.4) {
    //        //std::cout << "3" << std::endl;
    //        tempColours[3] = Sampling(scene, x, y, resX, resY, maxSteps - 1, +offset * 0.5f, +offset * 0.5f, offset * 0.5f);
    //    }
    //    else {
    //        tempColours[3] = (Vector)(tempColours[3] + centreColour) * 0.5;
    //    }
    //}


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
    std::shared_ptr<PerspectiveCamera> perspCam = std::make_shared<PerspectiveCamera>(256,256, 100.0f, 75.0f, Vector(0, 0, 5), Vector(0, 0, -1), Vector(0, 1, 0));
    
    std::shared_ptr<Camera> camera = perspCam;

    scene->camera = camera;


    //make objects
    //dont know why but to move sphere up in orthographic camera you have to put -1 intead of 1
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector(-0.5f, -3.0f, -11.5), 1.0f, Material(Vector(0.8f, 0.8f, 0.8f), 128, 5, 0, 0));
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector(0, 0.75f, -1), 0.3, Material(Vector(1.0f, 1.0f, 1.0f), 128, 1, 0, 0));
    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector(1.5f, -3.0f, -12.5), 1.0, Material(Vector(0.1f, 0.5f, 0.5f), 100, 1, 0, 1.05f));
    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(Vector(1.5f, -3.0f, -8.5), 1.0f, Material(Vector(1.f, 1.f, 1.f), 128, 1, 0, 0.f));
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(Vector(0, -2, 0), Vector(0, 1, 0), Material(Vector(1.f, 1.f, 1.f)));

    std::shared_ptr<Plane> P1 = std::make_shared<Plane>(Vector(4, 0, 0), Vector(-1, 0, 0), Material(Vector(0.0f, 0.0f, 1.0f), 128, 1, 0, 0)); //blue
    std::shared_ptr<Plane> P2 = std::make_shared<Plane>(Vector(-4, 0, 0), Vector(1, 0, 0), Material(Vector(1.0f, 0.0f, 0.0f), 128, 1, 0, 0)); //red
    std::shared_ptr<Plane> P3 = std::make_shared<Plane>(Vector(0, 4, 0), Vector(0, -1, 0), Material(Vector(0.9f, 0.9f, 0.9f), 128, 1, 0, 0)); //black
    std::shared_ptr<Plane> P4 = std::make_shared<Plane>(Vector(0, -4, 0), Vector(0, 1, 0), Material(Vector(0.9, 0.9f, 0.9f), 128, 1, 0, 0)); //turkusowy
    std::shared_ptr<Plane> P5 = std::make_shared<Plane>(Vector(0, 0, 16), Vector(0, 0, -1), Material(Vector(0.9f, 0.9f, 0.9f), 128, 1, 0, 0)); //fiolet
    std::shared_ptr<Plane> P6 = std::make_shared<Plane>(Vector(0, 0, -16), Vector(0, 0, 1), Material(Vector(0.9f, 0.9f, 0.9f), 128, 1, 0, 0)); //zolty


    //std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector(-0.5, -0.75, -20), 0.5, Vector(0.5f, 0.2f, 0.1f));

    //std::shared_ptr<Plane> plane1 = std::make_shared<Plane>(Vector(-1, 0, 0), Vector(0,0,1), Material(Vector(0.1f, 0.1f, 0.1f)));

    scene->objects.push_back(sphere1);
    //scene->objects.push_back(sphere2);
    //scene->objects.push_back(sphere3);
    scene->objects.push_back(sphere4);

    scene->objects.push_back(P1);
    scene->objects.push_back(P2);
    scene->objects.push_back(P3);
    scene->objects.push_back(P4);
    scene->objects.push_back(P5);
    scene->objects.push_back(P6);


    std::shared_ptr<PointLight> spotLight = std::make_shared<PointLight>(
        Vector(0, 3, -8),
        LightIntensity(1.0, 1.0, 1.0),
        0.7f,
        0.05f,
        0.00001f
    );


    //scene->lights.push_back(spotLight);
    scene->lights.push_back(spotLight);
    //scene->objects.push_back(plane1);
    //scene->objects.push_back(sphere3);

    //make buffer
    TGABuffer tgaBuffer(camera->GetResolutionX(), camera->GetResolutionY());
    LightIntensity lightIntensity(0.2, 0.4, 0.85);

    tgaBuffer.ClearColor(lightIntensity);

    //render
    Render(scene, tgaBuffer);
    //Render(scene, tgaBuffer, s2, s1);
    
    tgaBuffer.WriteTGA("outputPoint1.tga");


    return 0;
}




