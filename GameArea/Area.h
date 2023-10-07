#pragma once
#include "../Array/Array2D.h"

struct area
{
    Array2D<char> area_array;
    int width;
    int height;
};

area create_area(int width, int height);
