#include <system/stdint.h>

#define array_size 1000

uint8_t random_number[array_size] = {
    77,  56, 64,  63,  72, 51, 15, 94,  24,  88, 18,  52, 60, 43, 45,  60, 92,
    100, 40, 34,  65,  96, 92, 0,  80,  23,  0,  37,  87, 20, 71, 60,  56, 48,
    11,  59, 82,  84,  9,  41, 18, 67,  7,   97, 27,  95, 49, 25, 33,  66, 28,
    65,  75, 4,   86,  34, 73, 18, 56,  16,  34, 97,  1,  19, 26, 33,  6,  87,
    81,  47, 82,  95,  30, 93, 81, 14,  89,  27, 65,  66, 49, 26, 79,  97, 65,
    56,  11, 79,  80,  61, 21, 59, 70,  62,  66, 9,   44, 46, 16, 72,  11, 11,
    27,  74, 17,  11,  97, 48, 75, 21,  75,  28, 100, 55, 76, 39, 17,  88, 65,
    53,  79, 88,  46,  16, 4,  20, 87,  94,  62, 76,  24, 92, 53, 76,  11, 32,
    44,  80, 94,  23,  43, 52, 71, 68,  77,  76, 82,  27, 23, 83, 49,  31, 55,
    76,  21, 71,  36,  76, 32, 98, 91,  83,  63, 69,  97, 33, 80, 54,  43, 89,
    10,  69, 17,  5,   27, 83, 58, 82,  96,  69, 61,  27, 10, 50, 17,  47, 67,
    27,  31, 66,  43,  18, 61, 64, 21,  59,  74, 16,  61, 86, 69, 67,  34, 46,
    95,  38, 90,  100, 39, 27, 78, 65,  66,  37, 45,  72, 9,  19, 94,  93, 13,
    95,  56, 0,   2,   93, 82, 72, 78,  54,  58, 95,  59, 2,  82, 65,  95, 55,
    6,   23, 54,  72,  83, 37, 4,  93,  72,  76, 83,  98, 27, 67, 68,  92, 98,
    17,  65, 62,  10,  52, 91, 7,  96,  28,  38, 23,  27, 61, 45, 72,  53, 82,
    72,  43, 59,  57,  78, 7,  58, 61,  31,  57, 37,  84, 41, 9,  5,   68, 84,
    1,   15, 77,  91,  53, 5,  41, 95,  90,  81, 79,  2,  11, 3,  42,  43, 73,
    0,   30, 27,  22,  11, 16, 5,  57,  56,  55, 43,  86, 18, 66, 80,  30, 93,
    55,  49, 21,  63,  55, 83, 86, 81,  36,  95, 83,  0,  93, 63, 35,  56, 26,
    43,  38, 37,  10,  30, 11, 33, 19,  36,  41, 78,  93, 44, 8,  40,  44, 77,
    78,  69, 46,  54,  96, 33, 76, 90,  30,  26, 98,  85, 96, 28, 82,  79, 97,
    37,  29, 100, 82,  76, 92, 8,  81,  25,  47, 80,  20, 73, 5,  96,  97, 79,
    86,  36, 37,  26,  7,  9,  71, 77,  85,  46, 14,  4,  8,  48, 95,  84, 87,
    69,  44, 8,   74,  55, 7,  9,  32,  14,  73, 99,  29, 64, 85, 77,  79, 26,
    22,  14, 61,  67,  31, 28, 54, 33,  95,  33, 100, 34, 86, 91, 25,  56, 67,
    72,  44, 2,   2,   17, 61, 47, 79,  60,  13, 83,  47, 22, 20, 75,  21, 14,
    6,   67, 83,  46,  47, 47, 65, 15,  5,   67, 66,  5,  94, 83, 9,   79, 68,
    15,  0,  93,  9,   30, 73, 55, 3,   95,  45, 14,  36, 98, 55, 52,  69, 32,
    64,  25, 13,  84,  75, 22, 35, 6,   34,  8,  25,  8,  89, 17, 45,  42, 41,
    39,  46, 54,  26,  17, 0,  40, 86,  83,  11, 51,  90, 99, 59, 98,  89, 30,
    23,  98, 19,  82,  87, 21, 66, 35,  84,  64, 81,  64, 55, 3,  68,  32, 23,
    87,  84, 58,  98,  40, 95, 52, 30,  68,  31, 35,  63, 71, 81, 16,  35, 67,
    60,  55, 43,  29,  53, 17, 46, 90,  21,  95, 82,  44, 41, 75, 11,  88, 33,
    28,  18, 52,  15,  72, 35, 19, 15,  33,  45, 93,  19, 68, 14, 1,   76, 18,
    45,  37, 47,  57,  99, 14, 31, 15,  24,  32, 52,  61, 35, 8,  97,  16, 28,
    79,  14, 22,  92,  84, 3,  59, 77,  39,  77, 47,  92, 12, 15, 91,  37, 78,
    100, 5,  32,  50,  83, 96, 46, 26,  40,  41, 15,  35, 84, 61, 7,   55, 87,
    33,  10, 48,  52,  47, 23, 25, 60,  8,   41, 31,  66, 84, 54, 85,  32, 10,
    24,  43, 99,  75,  11, 79, 68, 31,  56,  66, 9,   5,  52, 97, 2,   44, 52,
    15,  53, 64,  8,   45, 67, 71, 81,  28,  41, 82,  3,  76, 28, 100, 43, 100,
    90,  77, 93,  72,  23, 32, 74, 27,  77,  11, 64,  19, 35, 77, 6,   69, 48,
    78,  74, 62,  94,  76, 68, 51, 71,  94,  20, 20,  26, 72, 26, 65,  61, 45,
    39,  20, 36,  67,  60, 35, 52, 66,  53,  0,  43,  81, 50, 54, 87,  67, 29,
    52,  15, 79,  36,  33, 9,  51, 47,  2,   31, 67,  40, 46, 49, 34,  76, 68,
    34,  55, 34,  70,  13, 8,  41, 53,  49,  27, 10,  78, 64, 25, 75,  71, 24,
    79,  95, 82,  19,  12, 26, 53, 13,  22,  66, 81,  92, 92, 5,  3,   82, 67,
    1,   33, 67,  78,  66, 63, 28, 10,  8,   53, 32,  48, 78, 64, 8,   93, 36,
    57,  9,  11,  16,  68, 10, 61, 46,  43,  60, 26,  54, 73, 40, 9,   27, 92,
    24,  50, 95,  82,  97, 24, 29, 12,  65,  29, 36,  11, 61, 94, 24,  22, 6,
    22,  53, 7,   6,   97, 60, 54, 42,  14,  59, 72,  59, 78, 18, 20,  96, 90,
    61,  76, 16,  34,  26, 52, 13, 63,  80,  3,  65,  26, 97, 39, 49,  54, 66,
    30,  96, 79,  5,   20, 26, 88, 73,  55,  46, 11,  18, 64, 51, 30,  35, 2,
    30,  38, 7,   9,   60, 93, 71, 29,  7,   67, 24,  22, 4,  82, 41,  77, 95,
    97,  57, 58,  94,  86, 90, 76, 94,  72,  91, 82,  91, 68, 57, 71,  6,  70,
    30,  66, 31,  26,  57, 12, 59, 49,  100, 12, 54,  26, 56, 16, 28,  90, 14,
    38,  14, 86,  20,  87, 87, 65, 2,   45,  8,  15,  43, 8,  4,  42,  52, 12,
    2,   34, 16,  55,  95, 97, 13, 100, 61,  77, 53,  69, 3,  94, 61,  53, 27,
    3,   86, 93,  10,  65, 0,  92, 91,  7,   59, 31,  34, 31, 6};