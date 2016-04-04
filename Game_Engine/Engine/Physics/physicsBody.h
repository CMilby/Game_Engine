//
//  physicsEntity.h
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PHYSICS_ENTITY_H__
#define __PHYSICS_ENTITY_H__

#include "collider.h"

class PhysicsBody {
	
private:
	static Vector3<float> s_gravity;
	
	Vector3<float> m_position;
	Vector3<float> m_oldPosition;
	Vector3<float> m_velocity;
	Collider *m_collider;
	
	bool m_affectedByGravity;
	
public:
	PhysicsBody( Collider *pCollider, const Vector3<float> &pVelocity );
	virtual ~PhysicsBody();
	
	void Intergrate( float pDelta );
	
	inline const Collider& GetCollider() {
		Vector3<float> myTranslation = m_position - m_oldPosition;
		m_oldPosition = GetPosition();
		m_collider->Transform( myTranslation );
		return *m_collider;
	}
	
	inline Vector3<float> GetPosition() const { return m_position; }
	inline Vector3<float> GetVelocity() const { return m_velocity; }
	
	inline void SetVelocity( const Vector3<float> &pVelocity ) { m_velocity = pVelocity; }
	
	inline void SetIsAffectedByGravity( bool pAffectedByGravity ) { m_affectedByGravity = pAffectedByGravity; }
	inline bool IsAffectedByGravity() const { return m_affectedByGravity; }
};

#endif /* physicsEntity_h */
