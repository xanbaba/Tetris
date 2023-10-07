#pragma once
#include "../Array/Array2D.h"

struct figure
{
    Array2D<char> figure_array;
    int x, y;
    int center_x, center_y;
    int width, height;
};
