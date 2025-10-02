#pragma once 

#include <raylib.h>

class Box {
    public:
        Vector2 center;
        float halfDimension;

        Box() = default;
        Box(float x, float y, float halfDimension);
        bool containsPoint(Vector2 point);
        bool intersectsBox(Box other);
};