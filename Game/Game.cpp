#include "Game.h"
#include "../Array/Array2D.h"
#include "../Console_App/Console_app.h"
#include <Windows.h>
#include <random>
#include <conio.h>

void start_game(area_size game_area_width, area_size game_area_height)
{
    // while (true)
    {
        const int area_width = static_cast<int>(game_area_width);
        const int area_height = static_cast<int>(game_area_height);

        auto game_area = create_area(area_width, area_height);
        auto figures_list = generate_figures();

        std::default_random_engine engine(time(nullptr));
        std::uniform_int_distribution<> range(0, figures_list.size - 1);

        print_introduction();

        print_area(game_area);

        // main loop
        while (true)
        {
            auto figure_object = figures_list.data[range(engine)];
            // auto figure_object = figures_list.data[2];
            auto current_figure = copy_figure(figure_object);
            int iteration{};
            while (true)
            {
                if (_kbhit())
                {
                    int key = _getch();
                    if (key == 75)
                    {
                        delete_figure_from_area(game_area, current_figure);
                        move_figure(game_area, current_figure, direction::left);
                        draw_figure_in_area(game_area, current_figure);
                    }
                    else if (key == 77)
                    {
                        delete_figure_from_area(game_area, current_figure);
                        move_figure(game_area, current_figure, direction::right);
                        draw_figure_in_area(game_area, current_figure);
                    }
                }
                if (iteration % 20 == 0)
                {
                    draw_figure_in_area(game_area, current_figure);
                }
                ++iteration;

                Sleep(20);
                ++iteration;
                if (current_figure.y + current_figure.height == area_height)
                {
                    break;
                }
                if (check_figure_stop(game_area, current_figure))
                {
                    break;
                }
                if (iteration % 20 == 0)
                {
                    delete_figure_from_area(game_area, current_figure);
                    ++current_figure.y;
                }
            }

            delete_array_2d(current_figure.figure_array);
            break_line(game_area);
        }


        finish_game(game_area, figures_list);
    }
    system("pause");
}

void finish_game(area& game_area, Array<figure>& figures_list)
{
    delete_array_2d(game_area.area_array);
    destroy_figures(figures_list);
}
