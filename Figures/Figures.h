#pragma once
#include "../Array/Array2D.h"
#include "../Array/Array.h"

struct figure
{
    Array2D<char> figure_array;
    int x, y;
    int center_x, center_y;
    int width, height;
};

void create_figure(Array<figure>& figures_list, int& figures_list_index, char**& figure_rows_chars, int rows, int cols);
Array<figure> generate_figures();
void destroy_figures(Array<figure>& figures_list);
