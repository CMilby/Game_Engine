//
//  physicsEngineSystem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "physicsEngineSystem.h"

PhysicsEngineSystem::PhysicsEngineSystem() : System( SYSTEM_PHYSICS_ENGINE ) {
	
}

PhysicsEngineSystem::~PhysicsEngineSystem() {
	
}

void PhysicsEngineSystem::Init() {
	System::Init();
	
	m_callbacks[ MESSAGE_HANDLE_COLLISIONS ] = std::bind( &PhysicsEngineSystem::HandleHandleCollisions, this, std::placeholders::_1 );
	m_callbacks[ MESSAGE_SIMULATE_PHYSICS ] = std::bind( &PhysicsEngineSystem::HandleSimulatePhysics, this, std::placeholders::_1 );
	m_callbacks[ MESSAGE_ADD_PHYSICS_BODY ] = std::bind( &PhysicsEngineSystem::HandleAddPhysicsBody, this, std::placeholders::_1 );
}

void PhysicsEngineSystem::AddObject( PhysicsBody *pEntity ) {
	m_objects.emplace_back( pEntity );
}

void PhysicsEngineSystem::HandleSimulatePhysics( const std::vector<MessagePayload> &pPayload ) {
	float myDelta = pPayload[ 0 ].GetPayloadFloat();
	
	for ( unsigned int i = 0; i < m_objects.size(); i++ ) {
		m_objects[ i ]->Intergrate( myDelta );
	}
}

void PhysicsEngineSystem::HandleHandleCollisions( const std::vector<MessagePayload> &pPayload ) {
	for ( unsigned int i = 0; i < m_objects.size(); i++ ) {
		for ( unsigned int j = i + 1; j < m_objects.size(); j++ ) {
			IntersectData myIntersect = m_objects[ i ]->GetCollider().Intersect( m_objects[ j ]->GetCollider() );
			if ( myIntersect.DoesIntersect() ) {
				m_objects[ i ]->SetVelocity( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
				m_objects[ j ]->SetVelocity( Vector3<float>( 0.0f, 0.0f, 0.0f ) );
			}
		}
	}
}

void PhysicsEngineSystem::HandleAddPhysicsBody( const std::vector<MessagePayload> &pPayload ) {
	AddObject( pPayload[ 0 ].GetPayloadPhysicsBody() );
}











