#ifndef GRANADA_CONFIG_H
#define GRANADA_CONFIG_H

/*
 * Nuklear compile flags. Must be identical in every translation unit that
 * includes nuklear.h (header *and* NK_IMPLEMENTATION). Changing these
 * independently corrupts ABI / stack.
 *
 * See Nuklear "OPTIONAL DEFINES" and docs/architecture.md.
 */

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_BOOL
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define GRANADA_VERSION         "0.1.0"
#define GRANADA_NUKLEAR_VERSION "4.13.3"

#endif /* GRANADA_CONFIG_H */
