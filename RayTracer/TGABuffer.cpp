#include "TGABuffer.h"
#include <cstdio>
#include <iostream>


TGABuffer::TGABuffer(unsigned int width, unsigned int height) : width(width), height(height) {
    colorBuffer = new unsigned int[width * height];
    depth = new float[width * height];
}

TGABuffer::~TGABuffer() {
    delete[] colorBuffer;
}

void TGABuffer::ClearColor(unsigned int color) {
    for (unsigned int i = 0; i < width * height; ++i) {
        colorBuffer[i] = color;
    }
}

void TGABuffer::ClearColor(LightIntensity lightIntensity)
{
    for (unsigned int i = 0; i < width * height; ++i) {

        colorBuffer[i] = GetColorFromArgb(lightIntensity.gRed() * 255, lightIntensity.gGreen() * 255, lightIntensity.gBlue() * 255);
    }
}

void TGABuffer::ClearDepth(float value) {
    for (unsigned int i = 0; i < width * height; ++i) {
        depth[i] = value;
    }
}

void TGABuffer::SetPixel(int x, int y, LightIntensity lightIntensity)
{
    colorBuffer[y * width + x] = GetColorFromArgb(lightIntensity.gRed() * 255, lightIntensity.gGreen() * 255, lightIntensity.gBlue() * 255);
}

unsigned int TGABuffer::GetColorFromArgb(unsigned int red, unsigned int green, unsigned int blue)
{
    return ( (255 & 0xff) << 24 | (red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff);
}

bool TGABuffer::WriteTGA(const char* fileName) {
    unsigned short header[9] = {
            0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
            0x0100, 0x0100, 0x0820
    };

    FILE* file;
    fopen_s(&file, fileName,  "wb+");

    if (!file)
        return false;

    header[6] = width;
    header[7] = height;

    fwrite(header, 2, 9, file);
    fwrite(colorBuffer, sizeof(unsigned int), width * height, file);


    fclose(file);

    return true;
}


void TGABuffer::Render(OrthographicCamera camera, Sphere s1) {

    Ray ray = Ray();


    for (int x = 0; x < camera.GetResX(); x++) {
        for (int y = 0; y < camera.GetResY(); y++) {
            ray = camera.GenerateRay(x, y);
            bool isS1 = s1.Intersect(ray, 0, 100);

            if (isS1 ==  true) {
                //std::cout << "hit" << std::endl;
                this->SetPixel(x, y, LightIntensity(0.5, 0.5, 0.5));
            }
        }
    }

}
