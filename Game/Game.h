#pragma once
#include "../GameArea/Area.h"

enum class area_size
{
    width = 10,
    height = 20
};

void start_game(area_size game_area_width, area_size game_area_height);
void finish_game(area& game_area, int* console_size);