#include <iostream>
#include "memory.hpp"
#include "GDExploits.hpp"

int main()
{
	auto game = driver(L"GeometryDash.exe");
	if (!game.is_attached())
	{
		printf("FAILED TO FIND GAME PROCESS!");
		PAUSE();
		return EXIT_FAILURE;
	}

	stat_edits::StatType input = stat_edits::StatType::NONE;
	while (input <= 0 || stat_edits::StatType::TOTAL_COUNT < input)
	{
		system("cls");
		printf("Select a stat to modify [1 - %d]:\n", stat_edits::StatType::TOTAL_COUNT);
		for (int i = 0; i < stat_edits::StatType::TOTAL_COUNT; ++i)
			printf("  %i) %s\n", i + 1, stat_edits::stat_types[i]);

		printf("\nInput: ");
		scanf_s("%d", &input);
	}

	int value;
	printf("\nInput value to set for stat '%s'!\nValue: ", stat_edits::stat_types[input - 1]);
	scanf_s("%d", &value);
	printf("\nSetting '%s' value to %d!\n", stat_edits::stat_types[input - 1], value);

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
	return EXIT_SUCCESS;
}