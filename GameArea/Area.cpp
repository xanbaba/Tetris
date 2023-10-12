#include "Area.h"
#include "../Console/Console.h"


area create_area(int width, int height)
{
    area game_area;
    game_area.width = width;
    game_area.height = height;
    game_area.area_array = create_array_2d<char>(height);

    for (int i = 0; i < height; ++i)
    {
        auto row = create_array<char>(width);
        row.size = width;
        append_row(game_area.area_array, row);
        
    }

    return game_area;
}

void print_area(area game_area)
{
    auto console_size = get_console_size();
    int width = game_area.width;
    int height = game_area.height;

    for (int i = 0; i < (console_size[0] / 2) - (height / 2); ++i)
    {
        std::cout << '\n';
    }

    for (int j = 0; j < (console_size[1] / 2 + 1) - width; ++j)
    {
        std::cout << ' ';
    }
    for (int i = 0; i < width * 2 + 1; ++i)
    {
        std::cout << '_';
    }
    std::cout << '\n';
    for (int i = 0; i < height; ++i)
    {
        auto row = game_area.area_array.data[i];

        for (int j = 0; j < (console_size[1] / 2) - width; ++j)
        {
            std::cout << ' ';
        }

        std::cout << '|';
        for (int j = 0; j < width; ++j)
        {
            std::cout << ' ';
            if (!row.data[j])
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << row.data[j];
            }
        }
        std::cout << " |\n";
    }

    for (int j = 0; j < (console_size[1] / 2 + 1) - width; ++j)
    {
        std::cout << ' ';
    }
    for (int i = 0; i < width * 2 + 1; ++i)
    {
        std::cout << '-';
    }
    std::cout << '\n';
    
    delete[] console_size;
}

void delete_figure_from_area(area& game_area, figure figure_object)
{
    auto game_area_array = game_area.area_array;
    auto figure_object_array = figure_object.figure_array;
    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        for (int x = figure_object.x; x < figure_object.x + figure_object.width;++x)
        {
            game_area_array.data[y].data[x] = '\0';
        }
    }
}

void draw_figure_in_area(area& game_area, figure figure_object)
{
    auto game_area_array = game_area.area_array;
    auto figure_object_array = figure_object.figure_array;
    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        for (int x = figure_object.x; x < figure_object.x + figure_object.width;++x)
        {
            if (game_area_array.data[y].data[x] == '*')
            {
                continue;
            }
            game_area_array.data[y].data[x] = figure_object_array.data[y - figure_object.y].
            data[x - figure_object.x];
        }
    }
}
