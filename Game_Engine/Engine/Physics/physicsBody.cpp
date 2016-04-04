//
//  physicsEntity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "physicsBody.h"

Vector3<float> PhysicsBody::s_gravity = Vector3<float>( 0.0f, -9.8f, 0.0f );

PhysicsBody::PhysicsBody( Collider *pCollider, const Vector3<float> &pVelocity ) {
	m_collider = pCollider;
	m_velocity = pVelocity;
	m_position = pCollider->GetCenter();
	m_oldPosition = m_position;
	
	if ( pCollider->GetType() == ColliderType::COLLIDER_PLANE ) {
		m_affectedByGravity = false;
	} else {
		m_affectedByGravity = true;
	}
}

PhysicsBody::~PhysicsBody() {
	
}

void PhysicsBody::Intergrate( float pDelta ) {
	if ( m_affectedByGravity ) {
		m_position += m_velocity * pDelta;
		m_velocity += s_gravity * pDelta;
	}
}





