/*
 * Single translation unit that compiles Nuklear's implementation.
 * Every other Granada .c includes nuklear.h *without* NK_IMPLEMENTATION.
 */
#include "granada_config.h"
#define NK_IMPLEMENTATION
#include "nuklear.h"
