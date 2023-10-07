#include "Area.h"

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
