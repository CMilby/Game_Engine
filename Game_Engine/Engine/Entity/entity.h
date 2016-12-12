//
//  entity.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <unordered_map>
#include <vector>

#include "component.h"
#include "hash_utility.h"
#include "transform.h"

class Entity {
    
private:
    Entity *m_parent;
    Transform *m_transform;
    
    std::vector<Entity*> m_children;
    std::unordered_map<ComponentType::ComponentType, Component*, EnumHash> m_components;
    
public:
    Entity( const Vector3f &p_position = Vector3f(), const Vector3f &p_scale = Vector3f( 1.0f, 1.0f, 1.0f ), const Quaternion &p_rotation = Quaternion() );
    virtual ~Entity();
    
    virtual void Init();
    
    Entity* AddChild( Entity *p_child );
    Entity* AddComponent( Component *p_component );
    Entity* AddComponent( Component *p_component, ComponentType::ComponentType p_componentType );
    
    Matrix4f GetModelMatrix() const;
    
    inline Component* GetComponent( ComponentType::ComponentType p_type ) const { return m_components.at( p_type ); }
    Component* GetComponent( ComponentType::ComponentType p_class, ComponentType::ComponentType p_sub ) const;
    
    inline void SetParent( Entity* p_parent ) { m_parent = p_parent; }
    inline Entity* GetParent() const { return m_parent; }
    inline Transform& GetTransform() const { return *m_transform; }
    
    inline void SetPosition( const Vector3<float> &pPosition ) { m_transform->SetPosition( pPosition ); }
    inline void SetRotation( const Quaternion &pRotation ) { m_transform->SetRotation( pRotation ); }
    inline void SetScale( const Vector3<float> &pScale ) { m_transform->SetScale( pScale ); }
    
    inline Vector3<float> GetPosition() const { return m_transform->GetPosition(); }
    inline Quaternion GetRotation() const { return m_transform->GetRotation(); }
    inline Vector3<float> GetScale() const { return m_transform->GetScale(); }
    
protected:
    
};

#endif /* entity_h */
