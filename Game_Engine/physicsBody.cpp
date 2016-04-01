//
//  physicsEntity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "physicsBody.h"

PhysicsBody::PhysicsBody( Collider *pCollider, const Vector3<float> &pVelocity ) {
	m_collider = pCollider;
	m_velocity = pVelocity;
	m_position = pCollider->GetCenter();
	m_oldPosition = m_position;
}

PhysicsBody::~PhysicsBody() {
	
}

void PhysicsBody::Intergrate( float pDelta ) {
	m_position += m_velocity * pDelta;
}