#include "Console.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

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
