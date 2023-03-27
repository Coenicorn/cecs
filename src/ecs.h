/*

Every componentcontainer holds a list of components
Every component holds custom data in the form of a void * and an identifier
Every system holds a list of entities it's associated with, an ID, 

*/

#ifndef ECS_H
#define ECS_H

#include <stdint.h>

#include "dyve.h"

// Initial size of entity array
#define ECS_ENTITYSTARTCOUNT 256

#define ECS_ENTITYMAX UINT32_MAX

// potential memory shortage waiting to happen...?
typedef uint64_t ECS_Entity_t;
typedef uint32_t ECS_ComponentID_t;
typedef uint32_t ECS_SystemID_t;

typedef DYVE_NEWTYPE(ECS_Entity_t) DYVE_ECS_EntityArr_t;



typedef struct ECS_ComponentContainer
{
    ECS_ComponentID_t id;
    /* not typesafe, needs to be allocated very carefully
    should point to dynamic array of components */
    void *components;
    /* function to free component data */
    void (*destroy)(void *components);
} ECS_ComponentContainer;

typedef DYVE_NEWTYPE(ECS_ComponentContainer) DYVE_ECS_ComponentContainer_t;






typedef struct ECS_System
{
    DYVE_ECS_EntityArr_t entities;
    /* Weight: When in the system call stack should this system be called. (i.e. gravity before collision) */
    ECS_SystemID_t id, weight;
    /* Entity handling */
    void (*perEntity)(struct ECS_Container *ECS, ECS_Entity_t entityID);
    /* Data associated with system that persists for all entities */
    void *persistentData;
} ECS_System;

typedef DYVE_NEWTYPE(ECS_System) DYVE_ECS_SystemArr_t;





typedef struct ECS_Container
{
    DYVE_ECS_EntityArr_t entities;

    DYVE_ECS_ComponentContainer_t components;

    DYVE_ECS_SystemArr_t systems;

    ECS_Entity_t nextEntityID;
    
} ECS_Container;





/* Creates a new ECS with 0 entities*/
ECS_Container *ECS_CreateECS(void);
/* Creates a new system. Fails if system already exists. */
void ECS_AddSystemType(ECS_Container *ecs, ECS_SystemID_t id, void (*perEntity)(ECS_Container *ECS, ECS_Entity_t entityID));
/* Frees the ECS from memory */
void ECS_Destroy(ECS_Container *ecs);
/* Adds an entity. */
ECS_Entity_t ECS_NewEntity(ECS_Container *container, uint32_t components);

#endif