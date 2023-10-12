#pragma once
#include "../Array/Array.h"
#include "../Figures/Figures.h"

enum class area_size
{
    width = 10,
    height = 20
};

void start_game(area_size game_area_width, area_size game_area_height);
void finish_game(area& game_area, Array<figure>& figures_list);