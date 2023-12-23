#include <iostream>
#include "memory.hpp"
#include "GDExploits.hpp"

void print_stat_row(int index, const char* stat)
{
    printf(" %2i) %-25s", index, stat);
}

stat_edits::StatType try_parse_input(const char* buffer)
{
    if (IS_TRM_CHR(buffer[0]))
        return stat_edits::StatType::INVALID;

    if ((buffer[0] | 0x20) == 'q' && IS_TRM_CHR(buffer[1]))
        return stat_edits::StatType::NONE;
        
    for (int i = 0; !IS_TRM_CHR(buffer[i]); ++i) {
        if (!isdigit(buffer[i]))
            return stat_edits::StatType::INVALID;
    }

    auto result = stat_edits::StatType(atoi(buffer));
    if (stat_edits::StatType::NONE < result && result <= stat_edits::StatType::TOTAL_COUNT)
        return result;

    return stat_edits::StatType::INVALID;
}

int main()
{
    const int totalOptions = stat_edits::StatType::TOTAL_COUNT;
    char input_buffer[0x10];

    auto game = driver(L"GeometryDash.exe");
    if (!game.is_attached())
    {
        printf("Failed to find game process!\n");
        PAUSE();
        return EXIT_FAILURE;
    }

    while (true)
    {
        stat_edits::StatType input = stat_edits::StatType::INVALID;
        while (input < 0 || totalOptions < input)
        {
            system("cls");
            printf("Input 'q' to exit\nSelect a stat to modify [1 - %d]:\n", totalOptions);

            for (int i = 1; i <= totalOptions; ++i)
            {
                print_stat_row(i, stat_edits::stat_types[i - 1]);

                if (i % 2 == 0)
                    printf("\n");
            }

            printf("\nInput: ");
            fgets(input_buffer, sizeof(input_buffer), stdin);
            input = try_parse_input(input_buffer);

            if (input == stat_edits::StatType::NONE) {
                printf("Exiting...\n");
                return EXIT_SUCCESS;
            }
        }

        int value;
        printf("\nInput value to set for stat '%s'!\nValue: ", stat_edits::stat_types[input - 1]);
        scanf_s("%d", &value);
        printf("\nSetting '%s' value to %d!\n", stat_edits::stat_types[input - 1], value);

        // since those random achievements aren't in the list anymore, adjust to fix gaunlets and list rewards since they come after
        if (input >= 30)
            input = stat_edits::StatType(input + 10);

        auto stats_instance = game.read<DWORD>(game.base + 0x4E82F0);

        auto stat_info = game.read<stat_edits::StatInfo*>(stats_instance + 0x164);
        auto stat_info_delta = game.read<stat_edits::StatInfo*>(stats_instance + 0x16C);

        int* stat_info_delta_addr = stat_edits::get_stat_addr(game, stat_info_delta, input);
        if (!stat_info_delta_addr)
        {
            printf("Failed to get the delta address for the specified stat type!\n");
            PAUSE();
            return EXIT_FAILURE;
        }

        int delta = game.read<int>(stat_info_delta_addr);

        int* stat_info_addr = stat_edits::get_stat_addr(game, stat_info, input);
        if (!stat_info_addr)
        {
            printf("Failed to get the stat value address for the specified stat type!\n");
            PAUSE();
            return EXIT_FAILURE;
        }

        game.write<int>(stat_info_addr, value + delta);

        printf("Finished!\n\n");
        PAUSE();
    }

    return EXIT_SUCCESS;
}
