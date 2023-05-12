#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include <stdlib.h>
#include <stdio.h>

#include "vec3.h"
#include "dyve.h"
#include "ecs.h"
#include "log.h"

typedef struct Transform
{
    Vec3 position, rotation, scale;
} Transform;


typedef struct DYVE_transform_t { Transform *data; uint32_t length, buffSize;} DYVE_transform_t;void DYVE_Transform_init(DYVE_transform_t *arr, uint32_t len){ arr->buffSize = len; arr->data = (Transform*)malloc(sizeof(Transform) * len); arr->length = 0;}void DYVE_Transform_push(DYVE_transform_t *arr, Transform val){ if (arr->length >= arr->buffSize) { uint32_t newLen = arr->buffSize + 16; Transform *newData = (Transform*)realloc(arr->data, sizeof(Transform) * newLen); if (newData == __null) { printf("DVVE: Failed to allocate memory\n"); exit(1); } arr->buffSize = newLen; arr->data = newData; } arr->data[arr->length++] = val;};Transform DYVE_Transform_pop(DYVE_transform_t *arr, uint32_t index){ if (index >= arr->length || index < 0) { printf("DYVE: Index out of range"); exit(1); } for (uint32_t i = index; i < arr->length-2; i++) { arr->data[i] = arr->data[i+1]; } arr->length--; if ((arr->buffSize - arr->length) > 16) { uint32_t newLen = arr->buffSize - 16; Transform *newData = (Transform*)realloc(arr->data, sizeof(Transform) * newLen); if (newData == __null) { printf("DVVE: Failed to allocate memory\n"); exit(1); } arr->data = newData; arr->buffSize = newLen; }}void DYVE_Transform_free(DYVE_transform_t *arr){ free(arr->data);}

#endif