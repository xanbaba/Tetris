#include "Figures.h"

#include "../console_library/console.h"
#include "../Game/Game.h"


void create_figure(Array<figure>& figures_list, int& figures_list_index, char**& figure_rows_chars, int rows, int cols)
{
    auto figure_array = create_array_2d<char>();

    for (int i = 0; i < rows; ++i)
    {
        auto row = create_array<char>(cols);
        set_data_array(row, figure_rows_chars[i], cols);
        append_row(figure_array, row);
    }

    delete[] figure_rows_chars;

    figure add_figure{};
    add_figure.figure_array = figure_array;
    add_figure.width = cols;
    add_figure.height = rows;
    add_figure.x = static_cast<int>(area_size::width) / 2 - cols / 2;

    append(figures_list, add_figure);
    ++figures_list_index;
}

Array<figure> generate_figures()
{
    constexpr int figures_count = 7;

    Array<figure> figures_list = create_array<figure>(figures_count);

    int figures_iteration{};

    // J figure
    {
        char** J_figure_rows_chars = new char*[3]
        {
            new char[3]{'\0', '*'},
            new char[3]{'\0', '*'},
            new char[3]{'*', '*'}
        };

        create_figure(figures_list, figures_iteration, J_figure_rows_chars, 3, 2);
    }

    // L figure
    {
        char** L_figure_rows_chars = new char*[3]
        {
            new char[3]{'*'},
            new char[3]{'*'},
            new char[3]{'*', '*'}
        };

        create_figure(figures_list, figures_iteration, L_figure_rows_chars, 3, 2);
    }

    // I figure
    {
        char** I_figure_rows_chars = new char*[4]
        {
            new char[1]{'*'},
            new char[1]{'*'},
            new char[1]{'*'},
            new char[1]{'*'}
        };

        create_figure(figures_list, figures_iteration, I_figure_rows_chars, 4, 1);
    }

    // O figure
    {
        char** O_figure_rows_chars = new char*[2]
        {
            new char[2]{'*', '*'},
            new char[2]{'*', '*'}
        };

        create_figure(figures_list, figures_iteration, O_figure_rows_chars, 2, 2);
    }

    // S figure
    {
        char** S_figure_rows_chars = new char*[3]
        {
            new char[2]{'*'},
            new char[2]{'*', '*'},
            new char[2]{'\0', '*'}
        };

        create_figure(figures_list, figures_iteration, S_figure_rows_chars, 3, 2);
    }
    // T figure
    {
        char** T_figure_rows_chars = new char*[3]
        {
            new char[2]{'*'},
            new char[2]{'*', '*'},
            new char[2]{'*'}
        };

        create_figure(figures_list, figures_iteration, T_figure_rows_chars, 3, 2);
    }

    // Z figure
    {
        char** Z_figure_rows_chars = new char*[3]
        {
            new char[2]{'\0', '*'},
            new char[2]{'*', '*'},
            new char[2]{'*'}
        };

        create_figure(figures_list, figures_iteration, Z_figure_rows_chars, 3, 2);
    }

    return figures_list;
}

void destroy_figures(Array<figure>& figures_list)
{
    for (int i = 0; i < figures_list.capacity; ++i)
    {
        delete_array_2d(figures_list.data[i].figure_array);
    }
    delete_array(figures_list);
}

figure copy_figure(figure figure_object)
{
    figure copied_figure;
    copied_figure.x = figure_object.x;
    copied_figure.y = figure_object.y;
    copied_figure.width = figure_object.width;
    copied_figure.height = figure_object.height;
    copied_figure.figure_array = create_array_2d<char>(figure_object.height);


    for (int i = 0; i < figure_object.figure_array.rows; ++i)
    {
        auto row = create_array<char>(figure_object.width);
        for (int j = 0; j < figure_object.figure_array.data[i].size; ++j)
        {
            append(row, figure_object.figure_array.data[i].data[j]);
        }
        append_row(copied_figure.figure_array, row);
    }

    return copied_figure;
}

bool check_figure_stop(area game_area, figure figure_object)
{
    auto game_area_array = game_area.area_array;
    auto figure_object_array = figure_object.figure_array;

    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        auto figure_y = y - figure_object.y;
        for (int x = figure_object.x; x < figure_object.x + figure_object.width; ++x)
        {
            auto figure_x = x - figure_object.x;

            if (figure_object_array.data[figure_y].data[figure_x] == '*' &&
                game_area_array.data[y + 1].data[x] == '*')
            {
                if (figure_y + 1 < figure_object.height)
                {
                    if (figure_object_array.data[figure_y + 1].data[figure_x] != '*')
                    {
                        return true;
                    }
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void move_figure(area game_area, figure& figure_object, direction dir)
{
    auto result_x = figure_object.x + static_cast<int>(dir);
    if (result_x < 0 || result_x + figure_object.width >= game_area.width + 1)
    {
        return;
    }

    int check_x;
    if (dir == direction::left)
    {
        check_x = 0;
    }
    else
    {
        check_x = figure_object.width - 1;
    }

    for (int i = 0; i < figure_object.height; ++i)
    {
        const auto figure_y_line = game_area.area_array.data[figure_object.y + i];

        if (figure_y_line.data[result_x + check_x] == '*' && figure_object.figure_array.data[i].data[check_x] == '*')
        {
            return;
        }
    }

    figure_object.x = result_x;
}

void rotate_figure(area& game_area, figure& figure_object)
{
    const int old_width = figure_object.width,
              old_height = figure_object.height;

    figure_object.height = old_width;
    figure_object.width = old_height;

    auto new_figure_array = create_array_2d<char>();

    for (int i = 0; i < figure_object.height; ++i)
    {
        auto row = create_array<char>(figure_object.width);
        append_row(new_figure_array, row);
    }

    for (int y = 0; y < old_height; ++y)
    {
        for (int x = 0; x < old_width; ++x)
        {
            if (figure_object.figure_array.data[y].data[x] != '*')
            {
                continue;
            }

            int new_x = figure_object.width - 1 - y,
                new_y = x;

            new_figure_array.data[new_y].data[new_x] = '*';
        }
    }

    const int old_x = figure_object.x;

    for (int y = 0; y < figure_object.height; ++y)
    {
        for (int x = 0; x < figure_object.width; ++x)
        {
            bool broke = true;
            for (int i = 0; i < figure_object.width; ++i)
            {
                if (game_area.area_array.data[figure_object.y + y].data[figure_object.x + x] == '*')
                {
                    move_figure(game_area, figure_object, direction::left);
                    continue;
                }
                broke = false;
                break;
            }

            if (broke)
            {
                figure_object.height = old_height;
                figure_object.width = old_width;
                figure_object.x = old_x;
                delete_array_2d(new_figure_array);
                return;
            }
        }
    }

    delete_array_2d(figure_object.figure_array);
    figure_object.figure_array = new_figure_array;
}
