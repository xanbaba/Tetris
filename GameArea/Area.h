#pragma once
#include "../Figures/Figures.h"
#include "../Array/Array2D.h"

struct area
{
    Array2D<char> area_array;
    int width;
    int height;
};

struct figure;

area create_area(int width, int height);
void delete_figure_from_area(area& game_area, figure figure_object);
void draw_figure_in_area(area& game_area, figure figure_object);
void print_area(area game_area);
