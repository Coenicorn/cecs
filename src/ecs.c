#include <stdlib.h>
#include <stdio.h>

#include "ecs.h"
#include "log.h"
#include "dyve.h"

ECS_Container *ECS_CreateECS(void)
{
    ECS_Container *outContainer = malloc(sizeof(ECS_Container));

    DYVE_ECS_ComponentContainer_init(&outContainer->components, 8);
    DYVE_ECS_Entity_t_init(&outContainer->entities, ECS_ENTITYSTARTCOUNT);
    DYVE_ECS_System_init(&outContainer->systems, 4);

    outContainer->nextEntityID = 0;
}

void ECS_Destroy(ECS_Container *ecs)
{
    // free all systems
    for (uint32_t i = 0; i < ecs->systems.length; i++)
    {
        DYVE_ECS_(&ecs->systems.data[i].entities);
    }
    
    // free all components
    for (uint32_t i = 0; i < ecs->components.length; i++)
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