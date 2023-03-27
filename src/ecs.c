#include <stdlib.h>
#include <stdio.h>

#include "ecs.h"
#include "log.h"
#include "dyve.h"

ECS_Container *ECS_CreateECS(void)
{
    ECS_Container *outContainer = malloc(sizeof(ECS_Container));

    DYVE_Init(outContainer->components, 8);
    DYVE_Init(outContainer->entities, ECS_ENTITYSTARTCOUNT);
    DYVE_Init(outContainer->systems, 4);

    outContainer->nextEntityID = 0;
}


void ECS_Destroy(ECS_Container *ecs)
{
    // free all systems
    for (uint32_t i = 0; i < ecs->systems.size; i++)
    {
        DYVE_Free(ecs->systems.data[i].entities);
    }
    
    // free all components
    for (uint32_t i = 0; i < ecs->components.size; i++)
    {
        ecs->components.data[i].destroy(ecs->components.data[i].components);
        free(ecs->components.data[i].components);
    }

    DYVE_Free(ecs->components);
    DYVE_Free(ecs->entities);
    DYVE_Free(ecs->systems);
}

ECS_Entity_t ECS_NewEntity(ECS_Container *container, uint32_t components)
{
    return container->nextEntityID++;
}