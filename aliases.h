#ifndef ALIASES_H
#define ALIASES_H

#include <stdint.h>
#include <stddef.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define TERM_COLOR_RED     "\x1b[31m"
#define TERM_COLOR_GREEN   "\x1b[32m"
#define TERM_COLOR_YELLOW  "\x1b[33m"
#define TERM_COLOR_BLUE    "\x1b[34m"
#define TERM_COLOR_MAGENTA "\x1b[35m"
#define TERM_COLOR_CYAN    "\x1b[36m"
#define TERM_COLOR_RESET   "\x1b[0m"

#endif /* end of include guard: ALIASES_H */
