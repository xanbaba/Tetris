#include "Console.h"
#include <Windows.h>
#include <conio.h>

void print_area(area game_area, int* console_size)
{
    int width = game_area.width;
    int height = game_area.height;

    for (int i = 0; i < (console_size[0] / 2) - (height / 2); ++i)
    {
        std::cout << '\n';
    }

    for (int j = 0; j < (console_size[1] / 2 + 1) - width; ++j)
    {
        std::cout << ' ';
    }
    for (int i = 0; i < width * 2 + 1; ++i)
    {
        std::cout << '_';
    }
    std::cout << '\n';
    for (int i = 0; i < height; ++i)
    {
        auto row = game_area.area_array.data[i];

        for (int j = 0; j < (console_size[1] / 2) - width; ++j)
        {
            std::cout << ' ';
        }

        std::cout << '|';
        for (int j = 0; j < width; ++j)
        {
            std::cout << ' ';
            if (!row.data[j])
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << row.data[j];
            }
        }
        std::cout << " |\n";
    }

    for (int j = 0; j < (console_size[1] / 2 + 1) - width; ++j)
    {
        std::cout << ' ';
    }
    for (int i = 0; i < width * 2 + 1; ++i)
    {
        std::cout << '-';
    }
    std::cout << '\n';
}

void print_introduction()
{
    std::cout << "Hi, this is Tetris game made by Xanbaba.\n  next >>";
    _getch();
    std::cout <<
        "\n!!!THE GAME IS ONLY AVAILABLE ON WINDOWS AND USE EXTERNAL CONSOLE(default console of windows)\n  next >>";
    _getch();
    system("cls");
}

int* get_console_size()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    auto size = new int[2]{rows, columns};

    return size;
}
