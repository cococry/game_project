#pragma once

typedef signed long long i64;
typedef signed int i32;
typedef signed short i16;
typedef signed char i8;

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef float f32;
typedef double f64;

typedef char b8;

#define COLOR_RGB(x) x / 255.0f.0f
#define COLOR_RGB_4(v1, v2, v3, v4) v1 / 255.0f, v2 / 255.0f, v3 / 255.0f, v4 / 255.0f
#define COLOR_RGB_3(v1, v2, v3) v1 / 255.0f, v2 / 255.0f, v3 / 255.0f

using KeyCode = i32;
using MouseCode = i32;
using gl_id = u32;