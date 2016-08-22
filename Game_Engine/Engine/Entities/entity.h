//
//  entity.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <map>
#include <vector>

#include "component.h"
#include "componentTypes.h"
#include "entityTypes.h"
#include "transform.h"

class Entity {
	
private:
	Entity *m_parent;
	EntityType m_type;
	
	Transform m_transform;
	
	std::vector<Entity*> m_children;
	std::map<ComponentType, Component*> m_components;

protected:
	virtual void Init() {}
	virtual void Input( float pDelta ) {}
	virtual void Update( float pDelta ) {}
	virtual void Render() {}
	
public:
	Entity( EntityType pType );
	virtual ~Entity();
	
	void InitAll();
	void InputAll( float pDelta );
	void UpdateAll( float pDelta );
	void RenderAll();
	
	Entity* AddChild( Entity *pChild );
	Entity* AddComponent( Component* pComponent );
	
	Component* GetComponent( ComponentType pType ) const;
	
	inline Entity* GetParent() const { return m_parent; }
	inline void SetParent( Entity* pParent ) { m_parent = pParent; }
	
	inline EntityType GetType() const { return m_type; }
	
	inline void SetPosition( const Vector3<float> &pPosition ) { m_transform.SetPosition( pPosition ); }
	inline void SetRotation( const Quaternion &pRotation ) { m_transform.SetRotation( pRotation ); }
	inline void SetScale( const Vector3<float> &pScale ) { m_transform.SetScale( pScale ); }
	
	inline Vector3<float> GetPosition() const { return m_transform.GetPosition(); }
	inline Quaternion GetRotation() const { return m_transform.GetRotation(); }
	inline Vector3<float> GetScale() const { return m_transform.GetScale(); }
	
	Matrix4<float> GetModelMatrix() const;
	
	void RemoveChild( Entity* pChild );
	void RemoveChild( unsigned int pIndex );
	void RemoveComponent( ComponentType pType );
	
	inline std::vector<Entity*> GetChildren() const { return m_children; }
};

#endif /* entity_h */
