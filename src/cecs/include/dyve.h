/*
    Dyve is a DYnamic VEctor implementation in C/C++

    Copyright (C) 2023 Coenicorn

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied w(arr)anty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
    Usage


    #include "dyve.h"

    DYVE_NEWTYPE(int);

    // initialization
    DYVE_int_t (arr);
    DYVE_Init((arr), 3);

    // push value to (arr)ay
    DYVE_Push((arr), 5);
    DYVE_Push((arr), 9);
    DYVE_Push((arr), 27);

    // pop at index
    int out = DYVE_Pop(2);

    printf("%DYVE_LOCAL_i\n", out)             // 27

    out = DYVE_Pop(0);

    printf("%i\n", out);            // 5

    printf("%i\n", (arr).data[0])     // 9
    printf("%u\n", (arr).size)        // 1


    Some variables can be adjusted to fit bigger (arr)ay entries:

    DYVE_MAXSIZEDIFFERENCE -> The allowed size difference beween the buffer size and the used size of the (arr)ay.
    When low, more memory allocation will happen (depending on the activity), but memory will be saved. When large,
    more memory will go unused, but future allocations will be faster until the buffer end is reached.

    DYVE already comes with some (arr)ay types for basic types, but these don't need to be used if not needed.

*/

#ifndef DYVE_H
#define DYVE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define DYVE_MAXSIZE __UINT32_MAX__

#ifndef DYVE_MAXSIZEDIFFERENCE
#define DYVE_MAXSIZEDIFFERENCE 16
#endif

#define DYVE_NEWTYPE(_TYPE, _NAME)\
\
typedef struct _NAME {\
    _TYPE *data;\
    uint32_t length, buffSize;\
} _NAME;\
\
static inline void DYVE_##_TYPE##_init(_NAME *arr, uint32_t len)\
{\
    arr->buffSize = len;\
    arr->data = (_TYPE*)malloc(sizeof(_TYPE) * len);\
    arr->length = 0;\
}\
\
static inline void DYVE_##_TYPE##_push(_NAME *arr, _TYPE val)\
{\
    if (arr->length >= arr->buffSize)\
    {\
        uint32_t newLen = arr->buffSize + DYVE_MAXSIZEDIFFERENCE;\
\
        _TYPE *newData = (_TYPE*)realloc(arr->data, sizeof(_TYPE) * newLen);\
\
        if (newData == NULL)\
        {\
            printf("DVVE: Failed to allocate memory\n");\
        \
            exit(1);\
        }\
\
        arr->buffSize = newLen;\
        arr->data = newData;\
    }\
\
    arr->data[arr->length++] = val;\
}\
\
static inline _TYPE DYVE_##_TYPE##_pop(_NAME *arr, uint32_t index)\
{\
    if (index >= arr->length || index < 0)\
    {\
        printf("DYVE: Index out of range");\
\
        exit(1);\
    }\
\
    for (uint32_t i = index; i < arr->length-2; i++)\
    {\
        arr->data[i] = arr->data[i+1];\
    }\
\
    arr->length--;\
\
    if ((arr->buffSize - arr->length) > DYVE_MAXSIZEDIFFERENCE)\
    {\
        uint32_t newLen = arr->buffSize - DYVE_MAXSIZEDIFFERENCE;\
\
        _TYPE *newData = (_TYPE*)realloc(arr->data, sizeof(_TYPE) * newLen);\
\
        if (newData == NULL)\
        {\
            printf("DVVE: Failed to allocate memory\n");\
        \
            exit(1);\
        }\
\
        arr->data = newData;\
        arr->buffSize = newLen;\
    }\
}\
\
static inline void DYVE_##_TYPE##_free(_NAME *arr)\
{\
    free(arr->data);\
}\

#define DYVE_HASBASICS
#ifdef DYVE_HASBASICS

DYVE_NEWTYPE(int, DYVE_int_t)
DYVE_NEWTYPE(char, DYVE_char_t)
DYVE_NEWTYPE(float, DYVE_float_t)
DYVE_NEWTYPE(double, DYVE_double_t)
DYVE_NEWTYPE(long, DYVE_long_t)
DYVE_NEWTYPE(short, DYVE_short_t)

#endif

#endif