#pragma once
#define STR_MERGE_IMPL(a, b) a ## b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a,b)
#define STRUCT_PAD(size) unsigned char STR_MERGE(__pad_, __COUNTER__)[size]

#define PAUSE() std::cin.ignore()
#define PAUSE_EXIT() { std::print( "Press any key to exit..." ); PAUSE(); }

#define CLEAR_SCREEN "\033[2J\033[H"