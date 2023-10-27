#include "Game.h"
#include "../Array/Array2D.h"
#include "../Array/String.h"
#include "../Console_App/Console_app.h"
#include <Windows.h>
#include <random>
#include <conio.h>
#include "../console_library/console.h"

using namespace app::console;

void start_game(area_size game_area_width, area_size game_area_height)
{
    const int area_width = static_cast<int>(game_area_width);
    const int area_height = static_cast<int>(game_area_height);

    auto game_area = create_area(area_width, area_height);
    auto figures_list = generate_figures();

    std::default_random_engine engine(time(nullptr));
    std::uniform_int_distribution<> range(0, figures_list.size - 1);

    int frame_update = 50;

    print_introduction();

    print_area(game_area);
    // main loop
    while (true)
    {
        auto figure_object = figures_list.data[range(engine)];
        if (!can_spawn_figure(game_area, figure_object))
        {
            break;
        }
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
                else if (key == 80)
                {
                    if (current_figure.y + 1 < game_area.height)
                    {
                        delete_figure_from_area(game_area, current_figure);
                        ++current_figure.y;
                        draw_figure_in_area(game_area, current_figure);
                    }
                }
                else if (key == 72)
                {
                    delete_figure_from_area(game_area, current_figure);
                    rotate_figure(game_area, current_figure);
                    draw_figure_in_area(game_area, current_figure);
                }
                
            }
            if (iteration % frame_update == 0)
            {
                draw_figure_in_area(game_area, current_figure);
            }

            Sleep(5);
            ++iteration;


            if (current_figure.y + current_figure.height == area_height)
            {
                break;
            }
            if (check_figure_stop(game_area, current_figure))
            {
                break;
            }

            if (iteration % frame_update == 0)
            {
                delete_figure_from_area(game_area, current_figure);
                ++current_figure.y;
            }
        }

        delete_array_2d(current_figure.figure_array);
        break_line(game_area);
    }
    finish_game(game_area, figures_list);
    io.readk(key::ENTER);
}

void finish_game(area& game_area, Array<figure>& figures_list)
{
    system("cls");
    auto console_size = get_console_size();

    io.mvxy0();
    io << '*';
    for (int i = 0; i < console_size[1] - 2; ++i)
    {
        io << '-';
    }
    io << '*' << '\n';

    for (int col = 1; col < console_size[0] - 1; ++col)
    {
        io.scpos(0, static_cast<coord>(col));
        io << '|';
        io.scpos(static_cast<coord>(console_size[1] - 1), static_cast<coord>(col));
        io << '|';
    }

    io << '*';
    for (int i = 0; i < console_size[1] - 2; ++i)
    {
        io << '-';
    }
    io << '*';

    auto game_over_label = create_array<String<>>();

    auto row1 = create_string();
    append(row1, R"( ___                                _____       ____               _____     ____)");

    auto row2 = create_string();
    append(row2, R"(/   \      /\        /\    /\      |           /    \   \      /  |         |    \)");

    auto row3 = create_string();
    append(row3, R"(|___      /  \      /  \  /  \     |____      |      |   \    /   |____     |____/)");

    auto row4 = create_string();
    append(row4, R"(|   |    /----\    /    \/    \    |          |      |    \  /    |         |\__)");

    auto row5 = create_string();
    append(row5, R"(\___/   /      \  /            \   |_____      \____/      \/     |_____    |   \_)");

    append(game_over_label, row1);
    append(game_over_label, row2);
    append(game_over_label, row3);
    append(game_over_label, row4);
    append(game_over_label, row5);

    const int y = console_size[0] / 2 - game_over_label.size / 2,
              x = console_size[1] / 2 - game_over_label.data[1].size / 2;

    for (int i = y; i < y + 5; ++i)
    {
        io.at(x, i, game_over_label.data[i - y].data);
    }

    auto exit_label = "Press Enter to exit";
    io.at(console_size[1] / 2 - strlen(exit_label) / 2, y + 6, exit_label);

    destroy_string(row1);
    destroy_string(row2);
    destroy_string(row3);
    destroy_string(row4);
    destroy_string(row5);

    delete_array(game_over_label);

    delete_array_2d(game_area.area_array);
    destroy_figures(figures_list);
}
