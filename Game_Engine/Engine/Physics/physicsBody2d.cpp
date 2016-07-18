//
//  physicsBody2d.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "physicsBody2d.h"

PhysicsBody2D::PhysicsBody2D() {
	m_collider = 0;
}

PhysicsBody2D::PhysicsBody2D( Collider *pCollider ) {
	m_collider = pCollider;
}

PhysicsBody2D::~PhysicsBody2D() {
	if ( m_collider != 0 ) {
		delete m_collider;
		m_collider = 0;
	}
}