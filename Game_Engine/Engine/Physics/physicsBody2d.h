//
//  physicsBody2d.h
//  Game_Engine
//
//  Created by Craig Milby on 7/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PHYSICS_BODY_2D__
#define __PHYSICS_BODY_2D__

#include "collider.h"
#include "entity.h"

class PhysicsBody2D {

private:
	Entity *m_parent;
	
	Vector3<float> m_position;
	Vector3<float> m_oldPosition;
	
	Vector2<float> m_velocity;
	Collider *m_collider;
	
public:
	PhysicsBody2D();
	PhysicsBody2D( Collider *pCollider );
	virtual ~PhysicsBody2D();
	
	void Intergrate( float pDelta );
	
	inline const Collider& GetCollider() {
		Vector3<float> myTranslation = m_position - m_oldPosition;
		m_oldPosition = GetPosition();
		m_collider->Transform( myTranslation );
		return *m_collider;
	}
	
	inline Vector3<float> GetPosition() const { return m_position; }
	inline Vector2<float> GetVelocity() const { return m_velocity; }
	
	inline void SetVelocity( const Vector2<float> &pVelocity ) { m_velocity = pVelocity; }
	inline void SetVelocityX( float pX ) { m_velocity.SetX( pX ); }
	inline void SetVelocityY( float pY ) { m_velocity.SetY( pY ); }
	
	inline void SetParent( Entity* pParent ) { m_parent = pParent; }
	inline Entity* GetParent() const { return m_parent; }
};

#endif /* physicsBody2d_h */
