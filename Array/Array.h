#pragma once
#include <iostream>

template <typename T>
struct Array
{
    T* data;
    int capacity;
    int size;
};

template <typename T>
Array<T> create_array(int capacity = 16)
{
    Array<T> array;

    array.capacity = capacity;
    array.data = new T[capacity]{};
    array.size = 0;

    return array;
}

template <typename T>
void print_array(Array<T> array)
{
    if (array.size <= 0)
    {
        std::cout << "{ }";
        return;
    }

    std::cout << "{ ";

    for (int i = 0; i < array.size; ++i)
    {
        std::cout << array.data[i];

        if (i != array.size - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << " }";
}

template <typename T>
void reallocate(Array<T>& array)
{
    if (array.capacity == array.size)
    {
        array.capacity *= 2;
        T* new_array = new T[array.capacity];

        for (int i = 0; i < array.size; ++i)
        {
            new_array[i] = array.data[i];
        }

        delete[] array.data;

        array.data = new_array;
    }
}

template <typename T>
void move_array_right(Array<T>& array, int start_index)
{
    for (int i = array.size - 1; i >= start_index; --i)
    {
        array.data[i + 1] = array.data[i];
    }
}

template <typename T>
void move_array_left(Array<T>& array, int start_index)
{
    for (int i = start_index; i < array.size; ++i)
    {
        array.data[i] = array.data[i + 1];
    }
}

template <typename T>
void append(Array<T>& array, T value)
{
    reallocate(array);
    array.data[array.size] = value;
    ++(array.size);
}

template <typename T>
void prepend(Array<T>& array, T value)
{
    reallocate(array);

    move_array_right(array, 0);
    array.data[0] = value;
    ++(array.size);
}

template <typename T>
void insert(Array<T>& array, T value, int index)
{
    if (index >= array.capacity || index < 0)
    {
        return;
    }

    reallocate(array);
    move_array_right(array, index);
    array.data[index] = value;
    ++(array.size);
}

template <typename T>
Array<T> concat(Array<T>& first_array, Array<T>& second_array)
{
    Array<T> concat_array = create_array<T>(first_array.capacity + second_array.capacity);

    for (int i = 0; i < first_array.size; ++i)
    {
        append(concat_array, first_array.data[i]);
    }

    for (int i = 0; i < second_array.size; ++i)
    {
        append(concat_array, second_array.data[i]);
    }

    return concat_array;
}

template <typename T>
void pop(Array<T>& array, int index = -1)
{
    if (index == -1)
    {
        index = array.size - 1;
    }
    array.data[index] = T{};

    move_array_left(array, index);

    --(array.size);
}

template <typename T>
void shift(Array<T>& array)
{
    pop(array, 0);
}

template <typename T>
void clear_array(Array<T>& array)
{
    // changed all values to null in order to prevent access to cleared data 
    for (int i = 0; i < array.size; ++i)
    {
        array.data[i] = T{};
    }

    array.size = 0;
}

template <typename T>
void resize(Array<T>& array, int new_capacity)
{
    // Check for idiots
    if (new_capacity < 0)
    {
        return;
    }

    // Another check for idiots
    if (new_capacity < array.size)
    {
        array.size = new_capacity;
    }

    // Resize
    array.capacity = new_capacity;
}

template <typename T>
Array<T> slice(Array<T>& array, int begin_index, int end_index)
{
    auto sliced_array = create_array<T>(end_index - begin_index + 1);

    for (int i = begin_index; i < end_index; ++i)
    {
        append(sliced_array, array.data[i]);
    }

    return sliced_array;
}

template <typename T>
void swap_values(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void reverse(Array<T>& array)
{
    const int middle_index = array.size / 2,
              last_index = array.size - 1;
    T* data = array.data;
    for (int i = 0; i < middle_index; ++i)
    {
        swap_values(data[i], data[last_index - i]);
    }
}

template <typename T>
void set_data_array(Array<T>& array, T* new_data, int new_data_size)
{
    delete[] array.data;
    array.size = new_data_size;
    array.data = new_data;
}

template <typename T>
void delete_array(Array<T>& array)
{
    delete[] array.data;
}
