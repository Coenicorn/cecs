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

#define DYVE_NEWTYPE(_TYPE) struct { uint32_t size, bufSize; _TYPE *data; }

/* Initializes (arr). Needs be called for every DYVE */
#define DYVE_Init(arr, _SIZE)\
{\
    (arr).size = 0;\
    (arr).bufSize = _SIZE;\
    (arr).data = malloc(sizeof((*(arr).data)) * _SIZE);\
}\

/* Pushes val to head of (arr) */
#define DYVE_Push(arr, val)\
{\
    if ((arr).size < (arr).bufSize)\
    {\
        (arr).data[(arr).size++] = val;\
    }\
    else\
    {\
\
        uint32_t DYVE_LOCAL_newLen = (arr).bufSize + DYVE_MAXSIZEDIFFERENCE;\
\
        void *DYVE_LOCAL_newData = realloc((arr).data, sizeof(*((arr).data)) * DYVE_LOCAL_newLen);\
\
        if (DYVE_LOCAL_newData == NULL)\
        {\
            printf("DYVE: Failed to allocate memory");\
        }\
\
        (arr).bufSize = DYVE_LOCAL_newLen;\
        (arr).data = DYVE_LOCAL_newData;\
\
        (arr).data[(arr).size++] = val;\
\
    }\
}

/* Removes (arr)[index] from (arr) */
#define DYVE_Remove(arr, index)\
{\
    if (index > (arr).size || index < 0)\
    {\
        printf("DYVE: Index outside (arr)ay bounds\n");\
    }\
    else\
    {\
\
        for (uint32_t DYVE_LOCAL_i = index; DYVE_LOCAL_i < (arr).size-1; DYVE_LOCAL_i++)\
        {\
            (arr).data[DYVE_LOCAL_i] = (arr).data[DYVE_LOCAL_i+1];\
        }\
\
        (arr).size--;\
\
        if (((arr).bufSize - (arr).size) > DYVE_MAXSIZEDIFFERENCE)\
        {\
            uint32_t DYVE_LOCAL_newSize = (arr).bufSize - DYVE_MAXSIZEDIFFERENCE;\
\
            void *DYVE_LOCAL_newData = realloc((arr).data, sizeof(*((arr).data)) * DYVE_LOCAL_newSize);\
\
            if (DYVE_LOCAL_newData == NULL)\
            {\
                printf("DYVE: Failed to allocate memory");\
            }\
            else\
            {\
                (arr).data = DYVE_LOCAL_newData;\
                (arr).bufSize = DYVE_LOCAL_newSize;\
            }\
        }\
    }\
}\

#define DYVE_Free(arr)\
{\
    free((arr).data);\
}\

#define DYVE_HASBASICS
#ifdef DYVE_HASBASICS
typedef DYVE_NEWTYPE(int) DYVE_int_t;
typedef DYVE_NEWTYPE(float) DYVE_float_t;
typedef DYVE_NEWTYPE(char) DYVE_char_t;
typedef DYVE_NEWTYPE(double) DYVE_double_t;
#endif

#endif