//
//  entity.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

#include "entityType.h"
#include "transform.h"

class PhysicsBody2D;

class Entity {
	
private:
	std::vector<Entity*> m_children;
	
	Entity *m_parent;
	
	EntityType m_entityType;
	Transform m_transform;
	PhysicsBody2D *m_physicsBody;
	
protected:
	virtual void Init() {}
	virtual void Input( float pDelta ) {}
	virtual void Update( float pDelta );
	virtual void Render() {}
	
public:
	Entity( EntityType pType );
	Entity( const Transform &transform );
	Entity( const Vector3<float> &position );
	virtual ~Entity();
	
	Entity* AddChild( Entity *pChild );
	
	void InitAll();
	void InputAll( float pDelta );
	void UpdateAll( float pDelta );
	void RenderAll();
	
	inline PhysicsBody2D* GetPhysicsBody() const { return m_physicsBody; }
	void SetPhysicsBody( PhysicsBody2D *pPhysicsBody );
	
	void RemoveChild( Entity* pEntity );
	void RemoveChild( int pIndex );
	
	inline void SetPosition( const Vector3<float> &position ) { m_transform.SetPosition( position ); }
	inline void SetScale( const Vector3<float> &scale ) { m_transform.SetScale( scale ); }
	inline void SetRotation( const Quaternion &rotation ) { m_transform.SetRotation( rotation ); }
	
	inline Vector3<float> GetPosition() const { return m_transform.GetPosition(); }
	inline Vector3<float> GetScale() const { return m_transform.GetScale(); }
	inline Quaternion GetRotation() const { return m_transform.GetRotation(); }
	
	inline void Move( const Vector3<float> &direction, float amount ) { m_transform.Move( direction, amount ); }
	inline void Rotate( const Quaternion &quat ) { m_transform.Rotate( quat ); }
	inline void Rotate( const Vector3<float> &axis, float angle ) { m_transform.Rotate( axis, angle ); }
	
	void SetVelocity( const Vector2<float> &pVelocity );
	void SetVelocityX( float pX );
	void SetVelocityY( float pY );
	
	Vector2<float> GetVelocity() const;
	
	inline void ClearChildren() { m_children.clear(); }
	inline std::vector<Entity*> GetChildren() const { return m_children; }
	
	inline Entity* GetParent() const { return m_parent; }
	inline void SetParent( Entity* pParent ) { m_parent = pParent; }
	
	inline EntityType GetEntityType() const { return m_entityType; }
	inline void SetEntityType( EntityType pEntityType ) { m_entityType = pEntityType; }
	
	virtual void Collided( Entity* pOther ) {}
	// virtual Vector3<float> GetWorldCoordinates() const { return GetPosition(); }
	
	Matrix4<float> GetModelMatrix() const;
};

#endif /* entity_h */
