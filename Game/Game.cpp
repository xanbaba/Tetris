#include "Game.h"
#include <Windows.h>
#include "../Console/Console.h"

void start_game(area_size game_area_width, area_size game_area_height)
{
    // while (true)
    {
        const int area_width = static_cast<int>(game_area_width);
        const int area_height = static_cast<int>(game_area_height);

        auto game_area = create_area(area_width, area_height);
        auto console_size = get_console_size();

        // print_introduction();
        print_area(game_area, console_size);
        auto figures_list = generate_figures();
        finish_game(game_area, console_size, figures_list);
    }
    system("pause");
}

void finish_game(area& game_area, int* console_size, Array<figure>& figures_list)
{
    delete_array_2d(game_area.area_array);
    delete[] console_size;
    destroy_figures(figures_list);
}
