#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include <stdlib.h>
#include <stdio.h>

#include "vec3.h"
#include "dyve.h"
#include "ecs.h"
#include "log.h"

#define CONC_(A, B) A##B
#define CONC(A, B) CONC_(A, B)

#define ECS_COMPONENT_INITIALIZE(_STRUCTNAME, _ID) \
typedef DYVE_NEWTYPE(_STRUCTNAME) CONC(CONC(DYVE_, _STRUCTNAME), _t);\
void CONC(CONC(ECS_COMPONENT_, _STRUCTNAME), _Destroy)(CONC(CONC(DYVE_, _STRUCTNAME), _t) *component)\
{\
    DYVE_Free(*(component));\
}\
void CONC(CONC(ECS_COMPONENT_, _STRUCTNAME), _Add)(ECS_Container *ECS_COMPONENT_LOCAL_ecs)\
{\
    int ECS_COMPONENT_LOCAL_exists = 0;\
    for (uint32_t i = 0; i < ECS_COMPONENT_LOCAL_ecs->components.size; i++)\
    {\
        if (ECS_COMPONENT_LOCAL_ecs->components.data[i].id == _ID)\
            ECS_COMPONENT_LOCAL_exists = 1;\
    }\
\
    if (ECS_COMPONENT_LOCAL_exists == 0)\
    {\
        CONC(CONC(DYVE_, _STRUCTNAME), _t) *ECS_COMPONENT_LOCAL_arr = (CONC(CONC(DYVE_, _STRUCTNAME), _t)*)malloc(sizeof(CONC(CONC(DYVE_, _STRUCTNAME), _t)));\
        DYVE_Init(*ECS_COMPONENT_LOCAL_arr, ECS_ENTITYSTARTCOUNT);\
        \
        ECS_ComponentContainer container;\
\
        container.components = ECS_COMPONENT_LOCAL_arr;\
        container.destroy = &CONC(CONC(ECS_COMPONENT_, _STRUCTNAME), _Destroy);\
        container.id = _ID;\
\
        DYVE_Push(ECS_COMPONENT_LOCAL_ecs->components, container);\
    }\
    else\
    {\
        ECS_Log("Double component definition\n");\
    }\
}\








// Every component needs to be given an ID
// in this struct, which systems will use
// to identify components
typedef enum
{
    Metaproperties_id               = 1,
    Transform_id                    = 2
} ECS_COMPONENT_IDS;

typedef struct Metaproperties
{
    const char *name;
} Metaproperties;

typedef struct Transform
{
    Vec3 position, rotation, scale;
} Transform;

ECS_COMPONENT_INITIALIZE(Metaproperties, Metaproperties_id)
ECS_COMPONENT_INITIALIZE(Transform, Transform_id)

#endif