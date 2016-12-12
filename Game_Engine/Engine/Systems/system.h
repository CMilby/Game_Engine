//
//  system.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "entity.h"

class System {
    
protected:
    std::vector<Entity*> m_entities;
    ComponentType::ComponentType m_type;
    
public:
    System( ComponentType::ComponentType p_type ) : m_type( p_type ) {}
    
    virtual void Init() {}
    
    virtual void Execute();
    virtual void Execute( float p_delta );
    virtual void Execute( Entity *p_entity );
    
    void AddEntity( Entity* p_entity );
    void RemoveEntity( Entity *p_entity );
    
    bool ContainsEntity( Entity *p_entity );
    Entity* GetEntity( Entity *p_entity );
};

#endif /* system_h */
