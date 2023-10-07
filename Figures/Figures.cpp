#include "Figures.h"

figure* generate_figures()
{
    constexpr int figures_count = 7;

    figure* figures_list = new figure[figures_count]{};

    // J figure
    {
        auto J_figure = create_array_2d<char>();
        auto J_figure_rows = create_array<Array<char>>(3);

        char J_figure_rows_chars[3][3]
        {
            {'\0', '\0', '*'},
            {'\0', '\0', '*'},
            {'*', '*', '*'}
        };

        for (int i = 0; i < 3; ++i)
        {
            auto row = create_array<char>(3);
            set_data_array(row, J_figure_rows_chars[i], 3);
            append(J_figure_rows, row);
            append_row(J_figure, J_figure_rows.data[i]);
        }
    }

    // L figure
    {
        auto L_figure = create_array_2d<char>();
        auto L_figure_rows = create_array<Array<char>>(3);

        char L_figure_rows_chars[3][3]
        {
            {'*'},
            {'*'},
            {'*', '*', '*'}
        };

        for (int i = 0; i < 3; ++i)
        {
            auto row = create_array<char>(3);
            set_data_array(row, L_figure_rows_chars[i], 3);
            append(L_figure_rows, row);
            append_row(L_figure, L_figure_rows.data[i]);
        }
    }

    // I figure
    {
        auto I_figure = create_array_2d<char>();
        auto I_figure_rows = create_array<Array<char>>(4);

        char I_figure_rows_chars[4][1]
        {
            {'*'},
            {'*'},
            {'*'},
            {'*'}
        };

        for (int i = 0; i < 4; ++i)
        {
            auto row = create_array<char>(1);
            set_data_array(row, I_figure_rows_chars[i], 1);
            append(I_figure_rows, row);
            append_row(I_figure, I_figure_rows.data[i]);
        }
    }

    // O figure
    {
        auto O_figure = create_array_2d<char>();
        auto O_figure_rows = create_array<Array<char>>(2);

        char O_figure_rows_chars[2][2]
        {
            {'*', '*'},
            {'*', '*'}
        };

        for (int i = 0; i < 2; ++i)
        {
            auto row = create_array<char>(2);
            set_data_array(row, O_figure_rows_chars[i], 2);
            append(O_figure_rows, row);
            append_row(O_figure, O_figure_rows.data[i]);
        }
    }

    // S figure
    {
        auto S_figure = create_array_2d<char>();
        auto S_figure_rows = create_array<Array<char>>(3);

        char S_figure_rows_chars[3][2]
        {
            {'*'},
            {'*', '*'},
            {'\0', '*'}
        };

        for (int i = 0; i < 2; ++i)
        {
            auto row = create_array<char>(2);
            set_data_array(row, S_figure_rows_chars[i], 2);
            append(S_figure_rows, row);
            append_row(S_figure, S_figure_rows.data[i]);
        }
    }

    return figures_list;
}
