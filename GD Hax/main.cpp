#include <iostream>
#include <string>
#include <stdexcept>
#include <print>

#include "memory.hpp"
#include "GDExploits.hpp"

// use the virtual terminal so we can use ansi escape sequences
static void init_console()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
}

inline void print_stat_row(int index, const char* stat)
{
    std::print(" {:2}) {:<25}", index, stat);
}

int read_int(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::print("{}", prompt);
        std::string input;
        std::getline(std::cin, input);

        try
        {
            value = std::stoi(input);
            return value;
        }
        catch (const std::invalid_argument&)
        {
            std::println("Invalid input. Please enter an integer.");
        }
        catch (const std::out_of_range&)
        {
            std::println("Number is out of range. Please enter a valid integer.");
        }
    }
}

stat_edits::StatType try_parse_input()
{
    std::string input;
    while (true)
    {
        std::print("\nInput: ");
        std::getline(std::cin, input);

        if (input.size() == 1 && tolower(input[0]) == 'q')
        {
            return stat_edits::StatType::NONE;
        }

        try
        {
            size_t pos;
            int value = std::stoi(input, &pos);

            // Check if entire string was consumed
            if (pos == input.length())
            {
                stat_edits::StatType result = stat_edits::StatType(value);
                if (stat_edits::StatType::NONE < result && result <= stat_edits::StatType::TOTAL_COUNT)
                    return result;

                std::println(CLEAR_SCREEN "Invalid input. Input a value that corresponds to a stat.");
            }
            else
            {
                std::println(CLEAR_SCREEN "Invalid input. Please enter only an integer.");
            }
        }
        catch (const std::invalid_argument&)
        {
            std::println(CLEAR_SCREEN "Invalid input. Please enter an integer.");
        }
        catch (const std::out_of_range&)
        {
            std::println(CLEAR_SCREEN "Number is out of range. Please enter a valid integer.");
        }

        return stat_edits::StatType::INVALID;
    }
}

int main()
{
    const int total_options = stat_edits::StatType::TOTAL_COUNT;

    auto game = driver(L"GeometryDash.exe");
    if (!game.is_attached())
    {
        std::println("Failed to find game process!");
        PAUSE_EXIT();
        return EXIT_FAILURE;
    }

    while (true)
    {
        stat_edits::StatType input = stat_edits::StatType::INVALID;
        while (input < 0 || total_options < input)
        {
            std::println("Input 'q' to exit\nSelect a stat to modify [1 - {}]:", total_options);

            for (int i = 1; i <= total_options; ++i)
            {
                print_stat_row(i, stat_edits::stat_types[i - 1]);

                if (i % 2 == 0)
                    std::print("\n");
            }

            input = try_parse_input();
            if (input == stat_edits::StatType::NONE)
            {
                std::println("Exiting...");
                return EXIT_SUCCESS;
            }
        }

        std::println("\nInput value to set for stat '{}'!", stat_edits::stat_types[input - 1]);
        int value = read_int(std::format("Value [{} - {}]: ", INT_MIN, INT_MAX));
        std::println("Setting '{}' value to {}!", stat_edits::stat_types[input - 1], value);

        // since those random achievements aren't in the list anymore, adjust to fix gaunlets and list rewards since they come after
        if (input >= 30)
            input = stat_edits::StatType(input + 10);

        auto stats_instance = game.read<uintptr_t>(game.base + 0x6A4E78);

        auto stat_info = reinterpret_cast<stat_edits::StatInfo*>(stats_instance + 0x248);
        auto stat_info_delta = reinterpret_cast<stat_edits::StatInfo*>(stats_instance + 0x288);

        stat_edits::StatLinkedList* stat_info_delta_addr = stat_edits::get_stat_addr(game, stat_info_delta, input);
        if (stat_info_delta_addr == nullptr)
        {
            std::println("Failed to get the delta address for the specified stat type!");
            PAUSE_EXIT();
            return EXIT_FAILURE;
        }

        auto delta = game.read<uint32_t>(&stat_info_delta_addr->value);

        stat_edits::StatLinkedList* stat_info_addr = stat_edits::get_stat_addr(game, stat_info, input);
        if (stat_info_addr == nullptr)
        {
            std::println("Failed to get the stat value address for the specified stat type!");
            PAUSE_EXIT();
            return EXIT_FAILURE;
        }

        game.write<uint32_t>(&stat_info_addr->value, value + delta);

        std::println("Success! Press any key to continue!");
        PAUSE();
        std::print(CLEAR_SCREEN);
    }

    return EXIT_SUCCESS;
}
