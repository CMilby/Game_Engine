//
//  entity.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "entity.h"

#include "system_resource.h"

Entity::Entity( const Vector3f &p_position, const Vector3f &p_scale, const Quaternion &p_rotation ) {
    m_transform = new Transform( p_position, p_scale, p_rotation );
    m_parent = 0;
}

Entity::~Entity() {
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        if ( m_children[ i ] != 0 ) {
            delete m_children[ i ];
            m_children[ i ] = 0;
        }
    }
    
    std::unordered_map<ComponentType::ComponentType, Component*, EnumHash>::iterator it;
    for ( it = m_components.begin(); it != m_components.end(); it++ ) {
        if ( it->second != 0 ) {
            SystemResource::RemoveEntity( it->first, this );
            delete it->second;
            it->second = 0;
        }
    }
    
    if ( m_transform != 0 ) {
        delete m_transform;
        m_transform = 0;
    }
}

void Entity::Init() {
    std::unordered_map<ComponentType::ComponentType, Component*, EnumHash>::iterator it;
    for ( it = m_components.begin(); it != m_components.end(); it++ ) {
        SystemResource::AddEntity( it->first, this );
    }
}

Entity* Entity::AddChild( Entity *p_child ) {
    p_child->SetParent( this );
    m_children.push_back( p_child );
    
    return this;
}

Entity* Entity::AddComponent( Component *p_component ) {
    p_component->SetParent( this );
    m_components.insert( std::pair<ComponentType::ComponentType, Component*>( p_component->GetType(), p_component ) );
    
    SystemResource::AddEntity( p_component->GetType(), this );
    return this;
}

Entity* Entity::AddComponent( Component *p_component, ComponentType::ComponentType p_componentType ) {
    p_component->SetParent( this );
    m_components.insert( std::pair<ComponentType::ComponentType, Component*>( p_componentType, p_component ) );
    
    SystemResource::AddEntity( p_componentType, this );
    return this;
}

Matrix4f Entity::GetModelMatrix() const {
    return m_transform->GetModelMatrix();
}

Component* Entity::GetComponent( ComponentType::ComponentType p_class, ComponentType::ComponentType p_sub ) const {
    return 0;
}



