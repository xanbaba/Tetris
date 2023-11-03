#pragma once
#include "../Array/Array2D.h"
#include "../GameArea/Area.h"

struct figure
{
    Array2D<char> figure_array;
    int x, y;
    int width, height;
};

struct area;

enum class direction
{
    left = -1,
    right = 1
};


void create_figure(Array<figure>& figures_list, int& figures_list_index, char**& figure_rows_chars, int rows, int cols);
Array<figure> generate_figures();
void destroy_figures(Array<figure>& figures_list);
figure copy_figure(figure figure_object);
bool check_figure_stop(area game_area, figure figure_object);
void move_figure(area game_area, figure& figure_object, direction dir);
void rotate_figure(area& game_area, figure& figure_object);
void print_next_figure(figure figure_object, area game_area);