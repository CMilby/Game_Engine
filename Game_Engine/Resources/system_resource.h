//
//  system_resource.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_RESOURCE_H__
#define __SYSTEM_RESOURCE_H__

#include <initializer_list>
#include <unordered_map>

#include "component_type.h"
#include "hash_utility.h"
#include "system.h"

class SystemResource {
    
private:
    static std::unordered_map<ComponentType::ComponentType, System*, EnumHash> s_systems;
    
public:
    static void Init() {
        std::unordered_map<ComponentType::ComponentType, System*, EnumHash>::iterator it;
        for ( it = s_systems.begin(); it != s_systems.end(); it++ ) {
            it->second->Init();
        }
    }
    
    static System* GetSystem( ComponentType::ComponentType p_type ) {
        return s_systems[ p_type ];
    }
    
    static void AddSystem( ComponentType::ComponentType p_type, System *p_system ) {
        s_systems.insert( std::pair<ComponentType::ComponentType, System*>( p_type, p_system ) );
    }
    
    static void AddEntity( ComponentType::ComponentType p_type, Entity *p_entity ) {
        s_systems[ p_type ]->AddEntity( p_entity );
    }
    
    static void AddEntity( ComponentType::ComponentType p_type, std::initializer_list<Entity*> p_entities ) {
        
    }
    
    static void RemoveEntity( ComponentType::ComponentType p_type, Entity *p_entity ) {
        s_systems[ p_type ]->RemoveEntity( p_entity );
    }
    
    static bool IsSystem( ComponentType::ComponentType p_type ) {
       return s_systems.count( p_type ) == 1;
    }
};

#endif /* system_resource_h */
