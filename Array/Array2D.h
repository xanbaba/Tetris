#pragma once
#include "Array.h"

template <typename T>
struct Array2D
{
    Array<T>* data;
    int capacity;
    int rows;
};

template <typename T>
Array2D<T> create_array_2d(int capacity = 16)
{
    Array2D<T> array;

    array.rows = 0;
    array.capacity = capacity;
    array.data = new Array<T>[capacity]{};

    for (int i = 0; i < capacity; ++i)
    {
        array.data[i] = create_array<T>(capacity);
    }

    return array;
}

template <typename T>
void reallocate_array_2d(Array2D<T>& array)
{
    if (array.capacity == array.rows)
    {
        array.capacity *= 2;
        auto new_array = new Array<T>[array.capacity];
        memcpy(new_array, array.data, array.rows * sizeof(Array<T>));
        for (int i = 0; i < array.rows; ++i)
        {
            delete_array(array.data[i]);
        }
        delete[] array.data;

        array.data = new_array;
    }
}

template <typename T>
void print_array_2d(Array2D<T> array)
{
    if (array.rows == 0)
    {
        std::cout << "{}";
        return;
    }

    std::cout << "{\n";

    for (int i = 0; i < array.rows; ++i)
    {
        std::cout << "    ";
        print_array(array.data[i]);
        std::cout << '\n';
    }
    std::cout << "\n}";
}

template <typename T>
void move_array_2d_right(Array2D<T>& array, int start_index)
{
    for (int i = array.rows - 1; i >= start_index; --i)
    {
        array.data[i + 1] = array.data[i];
    }
}

template <typename T>
void move_array_2d_left(Array2D<T>& array, int start_index)
{
    for (int i = start_index; i < array.rows - 1; ++i)
    {
        array.data[i] = array.data[i + 1];
    }
}

template <typename T>
void append_row(Array2D<T>& array, Array<T>& row)
{
    reallocate_array_2d(array);
    array.data[array.rows] = row;
    ++array.rows;
}

template <typename T>
void prepend_row(Array2D<T>& array, Array<T>& row)
{
    reallocate_array_2d(array);
    move_array_2d_right(array, 0);
    array.data[0] = row;
    ++array.rows;
}

template <typename T>
void insert_row(Array2D<T>& array, Array<T>& row, int index)
{
    if (index >= array.capacity || index < 0)
    {
        return;
    }

    reallocate_array_2d(array);
    move_array_2d_right(array, index);
    array.data[index] = row;
    ++(array.rows);
}

template <typename T>
void pop_row(Array2D<T>& array, int index = -1)
{
    if (index == -1)
    {
        index = array.rows - 1;
    }

    delete_array(array.data[index]);
    array.data[index] = Array<T>{};

    move_array_2d_left(array, index);
    --array.rows;
}

template <typename T>
void append_col(Array2D<T>& array, Array<T>& col)
{
    
}

template <typename T>
void delete_array_2d(Array2D<T>& array)
{
    for (int i = 0; i < array.capacity; ++i)
    {
        delete_array(array.data[i]);
    }
    delete[] array.data;
}
