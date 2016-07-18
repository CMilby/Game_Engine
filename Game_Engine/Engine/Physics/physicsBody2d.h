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

class Entity;

class PhysicsBody2D {

private:
	Entity *m_parent;
	
	Vector3<float> m_position;
	Vector3<float> m_oldPosition;
	Collider *m_collider;
	
public:
	PhysicsBody2D();
	PhysicsBody2D( Collider *pCollider );
	virtual ~PhysicsBody2D();
	
	inline const Collider& GetCollider() {
		Vector3<float> myTranslation = m_position - m_oldPosition;
		m_oldPosition = GetPosition();
		m_collider->Transform( myTranslation );
		return *m_collider;
	}
	
	inline Vector3<float> GetPosition() const { return m_position; }
	
	inline void SetParent( Entity* pParent ) { m_parent = pParent; }
	inline Entity* GetParent() const { return m_parent; }
};

#endif /* physicsBody2d_h */
