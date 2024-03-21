#pragma once
#include "LightIntensity.h"
#include "Ray.h"
#include "OrthographicCamera.h"
#include "Sphere.h"


class TGABuffer {
    unsigned int* colorBuffer;
    unsigned int width;
    unsigned int height;

    float* depth;

public:
    TGABuffer(unsigned int width, unsigned int height);
    ~TGABuffer();

    bool WriteTGA(const char* fileName);
    void ClearColor(unsigned int color);
    void ClearColor(LightIntensity lightIntensity);
    void ClearDepth(float value);

    void SetPixel(int x, int y, LightIntensity lightIntensity);

    unsigned int* GetColorBuffer() { return colorBuffer; }
    float* GetDepth() { return depth; }

    static unsigned int GetColorFromArgb(unsigned int red, unsigned int green, unsigned int blue);
    unsigned int GetWidth() const { return width; }
    unsigned int GetHeight() const { return height; }

};

