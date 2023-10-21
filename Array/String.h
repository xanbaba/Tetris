#pragma once
#include <iostream>
#include "Array.h"

template <typename T = char>
struct String
{
    T* data;
    int capacity;
    int size;
};



template <typename T = char>
struct Array_of_Strings
{
    String<T>* data;
    int capacity;
    int size;
};

enum class sentence_end
{
    dot = '.',
    exclamatory = '!',
    question = '?',
};

template <typename T = char>
void destroy_array_of_strings(Array_of_Strings<T>& string);

template <typename T = char>
void destroy_string(String<T>& string);

template <typename T = char>
String<T> create_string()
{
    String<T> string;
    string.capacity = 16;
    string.size = 0;
    string.data = new T[string.capacity];
    return string;
}

template <typename T = char>
int str_len(String<T> string)
{
    return string.size;
}

template <typename T = char>
int str_len(const T* string)
{
    int len{};
    int i{};
    while (string[i] != T{})
    {
        ++len;
        ++i;
    }

    return len;
}

template <typename T = char>
void reallocate(String<T>& string, int new_capacity)
{
    string.capacity = new_capacity;
    T* new_string = new T[string.capacity];

    for (int i = 0; i < string.size; ++i)
    {
        new_string[i] = string.data[i];
    }

    delete[] string.data;

    string.data = new_string;
}

template <typename T = char>
void reallocate_if_needed(String<T>& string)
{
    if (string.capacity == string.size + 1)
    {
        reallocate(string, string.capacity * 2);
    }
}

template <typename T = char>
void move_array_right(String<T>& string, const int start_index)
{
    for (int i = string.size - 1; i >= start_index; --i)
    {
        string.data[i + 1] = string.data[i];
    }
}

template <typename T = char>
void move_array_left(String<T>& string, const int start_index)
{
    for (int i = start_index; i < string.size; ++i)
    {
        string.data[i] = string.data[i + 1];
    }
}

template <typename T = char>
void append_string(String<T>& string, const T* appended_string, int appended_string_len)
{
    if (string.size + appended_string_len >= string.capacity)
    {
        reallocate(string, string.capacity + appended_string_len);
    }

    for (int i = 0; i < appended_string_len; ++i)
    {
        string.data[string.size] = appended_string[i];
        ++(string.size);
    }

    string.data[string.size] = T{};
}

template <typename T = char>
void append(String<T>& string, const T* appended_string)
{
    const int appended_string_len = str_len(appended_string);

    append_string(string, appended_string, appended_string_len);
}

template <typename T = char>
void append(String<T>& string, String<T> appended_string)
{
    append_string(string, appended_string.data, appended_string.size);
}

template <typename T = char>
void print_string(String<T> string)
{
    std::cout << '\"';
    if (string.size != 0)
    {
        std::cout << string.data;
    }
    std::cout << '\"';
}

template <typename T = char>
void print_array_of_strings(Array_of_Strings<T>& string)
{
    if (string.size == 0)
    {
        std::cout << "{}";
    }
    std::cout << "{ ";
    for (int i = 0; i < string.size; ++i)
    {
        print_string(string.data[i]);
        if (i != string.size - 1)
        {
            std::cout << ", ";
            continue;
        }
        std::cout << " ";
    }
    std::cout << "}";
}

template <typename T = char>
void remove(String<T>& string, int index = -1)
{
    if (index == -1)
    {
        index = string.size - 1;
    }
    string.data[index] = T{};

    move_array_left(string, index);

    --(string.size);
}

template <typename T = char>
void remove(String<T>& string, T delete_character, int delete_count = -1)
{
    if (delete_count <= -1 || delete_count > string.size)
    {
        delete_count = string.size;
    }

    for (int i = 0; i < string.size && delete_count > 0; ++i)
    {
        if (string.data[i] == delete_character)
        {
            reallocate_if_needed(string);
            remove(string, i);
            --delete_count;
        }
    }
}

template <typename T = char>
void insert(String<T>& string, T value, int index)
{
    if (index >= string.capacity || index < 0)
    {
        return;
    }

    reallocate_if_needed(string);
    move_array_right(string, index);
    string.data[index] = value;
    ++(string.size);
    string.data[string.size] = T{};
}

template <typename T = char>
int find(String<T> string, T character)
{
    // This is my own search algorithm based on double search but unlike double search,
    // this search return the first found index while normal double search may return the last found index
    // if it is located closer to the end of string
    const int last_index = string.size - 1;
    int last_find_index{};
    for (int i = 0; i < string.size / 2 + 1; ++i)
    {
        if (string.data[i] == character)
        {
            return i;
        }
        if (string.data[last_index - i] == character)
        {
            last_find_index = last_index - i;
        }
    }

    if (last_find_index != 0)
    {
        return last_find_index;
    }

    return -1;
}

template <typename T = char>
void clear(String<T>& string)
{
    for (int i = 0; i < string.size; ++i)
    {
        string.data[i] = T{};
    }

    string.size = 0;
}

template <typename T = char>
void replace(String<T>& string, const char* what, const char* to)
{
    if (!strcmp(what, to))
    {
        return;
    }
    while (true)
    {
        const char* found = strstr(string.data, what);
        if (found == nullptr)
        {
            break;
        }
        const int found_start_index = static_cast<int>(found - string.data); // this was in netacad
        const size_t what_len = strlen(what);
        const size_t to_len = strlen(to);

        for (size_t i = 0; i < what_len; ++i)
        {
            remove(string, found_start_index);
        }

        for (size_t i = found_start_index; i < to_len + found_start_index; ++i)
        {
            insert(string, to[i - found_start_index], static_cast<int>(i));
        }
    }
}

template <typename T = char>
void replace(String<T>& string, String<T> what, String<T> to)
{
    replace(string, what.data, to.data);
}

template <typename T = char>
Array_of_Strings<T> split(String<T>& string, const char* delimiter)
{
    Array_of_Strings<T> splitted_array;
    splitted_array.data = new String<T>[string.size];
    splitted_array.size = 0;
    splitted_array.capacity = string.size;

    size_t start_index{};
    const size_t delimiter_len = strlen(delimiter);

    if (delimiter_len == 0)
    {
        for (int i = 0; i < string.size; ++i)
        {
            splitted_array.data[i] = create_string<T>();
            ++splitted_array.size;
            insert(splitted_array.data[i], string.data[i], 0);
        }
        return splitted_array;
    }

    size_t iteration{};

    bool is_splittable = true;

    while (is_splittable)
    {
        const char* found_delimiter = strstr(&string.data[start_index], delimiter);
        size_t end_index;
        if (found_delimiter == nullptr)
        {
            is_splittable = false;
            end_index = string.size;
        }
        else
        {
            end_index = found_delimiter - string.data;
        }

        splitted_array.data[iteration] = create_string<T>();
        ++splitted_array.size;

        for (size_t i = start_index; i < end_index; ++i)
        {
            insert(splitted_array.data[iteration], string.data[i], splitted_array.data[iteration].size);
        }

        start_index = end_index + delimiter_len;

        ++iteration;
    }

    return splitted_array;
}

template <typename T = char>
Array_of_Strings<T> split(String<T>& string, String<T> delimiter)
{
    return split(string, delimiter.data);
}

template <typename T = char>
String<T> join(Array_of_Strings<T>& str, const T* joiner)
{
    auto joined_string = create_string<T>();

    for (int i = 0; i < str.size; ++i)
    {
        append(joined_string, str.data[i]);
        if (i != str.size - 1)
        {
            append(joined_string, joiner);
        }
    }

    return joined_string;
}

template <typename T = char>
String<T> join(Array_of_Strings<T>& str, String<T>& joiner)
{
    return join(str, joiner.data);
}

template<typename T>
void capitalize(String<T>& str)
{
    auto splited_string = split(str, " ");
    for (int i = 0; i < splited_string.size; ++i)
    {
        auto i_string = splited_string.data[i];
        if (i_string.size)
        {
            i_string.data[0] = static_cast<char>(toupper(i_string.data[0]));
        }
    }

    auto new_string = join(splited_string, " ");
    str = new_string;
}

template<typename T>
Array<int> count_each(String<T>& str, char range_1, char range_2)
{
    auto count_array = create_array<int>(range_2 - range_1 + 1);
    
    for (int i = 0; i < str.size; ++i)
    {
        str.data[i] = static_cast<char>(tolower(str.data[i]));
        if (str.data[i] >= range_1 && str.data[i] <= range_2)
        {
            count_array.data[str.data[i] - range_1] += 1;
        }
    }
    return count_array;
}

template<typename T>
Array<int> count_letters(String<T>& str)
{
    return count_each(str, 'a', 'z');
}

template<typename T>
Array<int> count_each_number(String<T>& str)
{
    return count_each(str, '0', '9');
}

template<typename T>
int count_sentences(String<T> string)
{
    if (string.size == 0)
    {
        return 0;
    }
    int sentences{};

    for (int i = 0; i < string.size; ++i)
    {
        sentence_end symbol = static_cast<sentence_end>(string.data[i]);

        switch (symbol) {
        case sentence_end::dot:
            if (i + 2 >= string.size)
            {
                ++sentences;
                continue;
            }
            if (static_cast<sentence_end>(string.data[i + 1]) == sentence_end::dot &&
                static_cast<sentence_end>(string.data[i + 2]) == sentence_end::dot)
            {
                ++sentences;
                i += 2;
            }
            break;
        case sentence_end::exclamatory:
        case sentence_end::question:
            ++sentences;
            break;
        }
    }
    
    return sentences;
}

template<typename T>
int str_to_int(String<T> string)
{
    int result_number{};
    for (int i = 0; i < string.size; ++i)
    {
        int current_index = string.size - i - 1;
        char current_symbol = string.data[current_index];

        if (current_symbol >= '0' && current_symbol <= '9')
        {
            int number = current_symbol - 48;
            result_number += static_cast<int>(pow(10, i) * number);
        }
    }

    if (string.data[0] == '-')
    {
        result_number *= -1;
    }

    return result_number;
}

template <typename T = char>
void destroy_string(String<T>& string)
{
    delete[] string.data;
}

template <typename T = char>
void destroy_array_of_strings(Array_of_Strings<T>& string)
{
    for (int i = 0; i < string.size; ++i)
    {
        destroy_string(string.data[i]);
    }

    delete[] string.data;
}
