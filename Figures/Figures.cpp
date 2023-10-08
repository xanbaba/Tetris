#include "Figures.h"

void create_figure(Array<figure>& figures_list, int& figures_list_index, char**& figure_rows_chars, int rows, int cols)
{
    auto figure_array = create_array_2d<char>();

    for (int i = 0; i < rows; ++i)
    {
        auto row = create_array<char>(cols);
        set_data_array(row, figure_rows_chars[i], cols);
        append_row(figure_array, row);
        // delete[] figure_rows_chars[i];
    }

    delete[] figure_rows_chars;

    figure add_figure{};
    add_figure.figure_array = figure_array;
    add_figure.width = cols;
    add_figure.height = rows;
    
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
            new char[3]{'\0', '\0', '*'},
            new char[3]{'\0', '\0', '*'},
            new char[3]{'*', '*', '*'}
        };

        create_figure(figures_list, figures_iteration, J_figure_rows_chars, 3, 3);
    }

    // L figure
    {
        char** L_figure_rows_chars = new char*[3]
        {
            new char[3]{'*'},
            new char[3]{'*'},
            new char[3]{'*', '*', '*'}
        };

        create_figure(figures_list, figures_iteration, L_figure_rows_chars, 3, 3);
        
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

    // S figure
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
        // figures_list.data->figure_array.data->data
        delete_array_2d(figures_list.data[i].figure_array);
        
    }
    delete_array(figures_list);
    // std::cout << figures_list.data[0].figure_array.data[0].data[0];
    // print_array(figures_list.data[0].figure_array.data[0]);
    // print_array_2d(figures_list.data[0].figure_array);
}
