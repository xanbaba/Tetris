#include "Area.h"
#include "../Console_App/Console_app.h"
#include "../console_library/console.h"

using namespace app::console;

area create_area(int width, int height)
{
    auto console_size = get_console_size();

    area game_area{};
    game_area.width = width;
    game_area.height = height;
    game_area.area_array = create_array_2d<char>(height);

    for (int i = 0; i < (console_size[0] / 2) - (height / 2); ++i)
    {
        ++game_area.y;
    }

    for (int j = 0; j < (console_size[1] / 2 + 1) - width; ++j)
    {
        ++game_area.x;
    }

    for (int i = 0; i < height; ++i)
    {
        auto row = create_array<char>(width);
        row.size = width;
        append_row(game_area.area_array, row);
    }

    delete[] console_size;
    return game_area;
}

void print_area(area game_area)
{
    int width = game_area.width;
    int height = game_area.height;

    auto x = static_cast<short>(game_area.x),
         y = static_cast<short>(game_area.y);

    io.scpos(x, y);
    io << ' ';
    for (int i = 0; i < width * 2 - 1; ++i)
    {
        io << '_';
    }
    io.scpos(x, ++y);
    for (int i = 0; i < height; ++i)
    {
        io << "| ";
        for (int j = 0; j < width - 1; ++j)
        {
            io << "  ";
        }
        io << "| ";
        io.scpos(x, ++y);
    }
    io << ' ';
    for (int i = 0; i < width * 2 - 1; ++i)
    {
        io << '-';
    }
}

void delete_figure_from_area(area& game_area, figure figure_object)
{
    auto game_area_array = game_area.area_array;
    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        for (int x = figure_object.x; x < figure_object.x + figure_object.width; ++x)
        {
            if (game_area_array.data[y].data[x] == '*' &&
                figure_object.figure_array.data[y - figure_object.y].data[x - figure_object.x] != '*')
            {
                continue;
            }
            game_area_array.data[y].data[x] = '\0';
            io.at(static_cast<coord>(x * 2 + game_area.x + 1),
                  static_cast<coord>(y + game_area.y + 1),
                  " ");
        }
    }
}

void draw_figure_in_area(area& game_area, figure figure_object)
{
    auto game_area_array = game_area.area_array;
    auto figure_object_array = figure_object.figure_array;
    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        for (int x = figure_object.x; x < figure_object.x + figure_object.width; ++x)
        {
            if (game_area_array.data[y].data[x] == '*')
            {
                continue;
            }
            game_area_array.data[y].data[x] = figure_object_array.data[y - figure_object.y].
                data[x - figure_object.x];
            if (game_area_array.data[y].data[x] == '*')
            {
                io.at(static_cast<coord>(x * 2 + game_area.x + 1),
                      static_cast<coord>(y + game_area.y + 1),
                      "*");
            }
        }
    }
}

Array<int> which_line_break(area& game_area)
{
    auto line_indexes = create_array<int>();
    for (int y = 0; y < game_area.height; ++y)
    {
        int return_line = y;
        for (int x = 0; x < game_area.width; ++x)
        {
            if (game_area.area_array.data[y].data[x] != '*')
            {
                return_line = -1;
                break;
            }
        }

        if (return_line != -1)
        {
            append(line_indexes, return_line);
        }
    }

    return line_indexes;
}

void break_line(area& game_area)
{
    auto line_indexes = which_line_break(game_area);
    for (int line_index_i = 0; line_index_i < line_indexes.size; ++line_index_i)
    {
        auto line_index = line_indexes.data[line_index_i];
        for (int y = line_index - 1; y >= 0; --y)
        {
            auto& row = game_area.area_array.data[y];
            for (int x = 0; x < row.size; ++x)
            {
                game_area.area_array.data[y + 1].data[x] = row.data[x];

                io.erase(x * 2 + (game_area.x + 1),
                         y + (game_area.y + 2));
                io.scpos(x * 2 + (game_area.x + 1),
                         y + (game_area.y + 2));
                io << row.data[x];

                row.data[x] = '\0';

                io.scpos(x * 2 + (game_area.x + 1),
                         y + (game_area.y + 1));
                io.erase(x * 2 + (game_area.x + 1),
                         y + (game_area.y + 1));

                io << '\0';
            }
        }
    }
}

bool can_spawn_figure(area& game_area, figure& figure_object)
{
    auto game_area_array = game_area.area_array;
    auto figure_object_array = figure_object.figure_array;
    for (int y = figure_object.y; y < figure_object.y + figure_object.height; ++y)
    {
        for (int x = figure_object.x; x < figure_object.x + figure_object.width; ++x)
        {
            if (figure_object_array.data[y - figure_object.y].data[x - figure_object.x] == '*' &&
                game_area_array.data[y].data[x] == '*')
            {
                io.at(0, 1, "false");
                return false;
            }
        }
    }
    return true;
}
