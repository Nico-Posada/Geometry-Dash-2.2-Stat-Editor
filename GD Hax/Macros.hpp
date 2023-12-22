#pragma once
#define STR_MERGE_IMPL(a, b) a ## b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a,b)
#define STRUCT_PAD(size) unsigned char STR_MERGE(__pad_, __COUNTER__)[size]

#define PAUSE() system("pause")

#define IS_TRM_CHR(chr) (((chr) == '\0') || ((chr) == '\n'))