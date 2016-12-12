//
//  component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "component_type.h"
#include "transform.h"

class Entity;

class Component {
    
private:
    Entity *m_parent;
    ComponentType::ComponentType m_type;
    
public:
    Component( ComponentType::ComponentType p_type ) : m_type( p_type ) {}
    virtual ~Component() {}
    
    virtual void Execute() = 0;
    virtual void Execute( float p_delta ) = 0;
    virtual void Execute( Entity *p_entity ) = 0;
    
    inline void SetParent( Entity *p_parent ) { m_parent = p_parent; }
    inline Entity* GetParent() const { return m_parent; }
    
    inline ComponentType::ComponentType GetType() const { return m_type; }
};

#endif /* component_h */
