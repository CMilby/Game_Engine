//
//  entity.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "entity.h"

#include "messenger.h"

Entity::Entity() {
	m_physicsBody = 0;
}

Entity::Entity( const Transform &transform ) {
	m_transform = transform;
	m_physicsBody = 0;
}

Entity::Entity( const Vector3<float> &position ) {
	m_transform.SetPosition( position );
	m_physicsBody = 0;
}

Entity::~Entity() {
	if ( m_physicsBody ) {
		delete m_physicsBody;
		m_physicsBody = 0;
	}
}

Entity* Entity::AddChild( Entity *child ) {
	m_children.emplace_back( child );
	return this;
}

void Entity::Update() {
	if ( m_physicsBody != NULL ) {
		SetPosition( m_physicsBody->GetPosition() );
	}
}

void Entity::InitAll() {
	Init();
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->InitAll();
	}
}

void Entity::InputAll() {
	Input();
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->InputAll();
	}
}

void Entity::UpdateAll() {
	Update();
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->UpdateAll();
	}
}

void Entity::RenderAll() {
	Render();
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->RenderAll();
	}
}

void Entity::SetPhysicsBody( PhysicsBody *pPhysicsBody ) {
	m_physicsBody = pPhysicsBody;
	std::vector<MessagePayload> myPayload;
	myPayload.emplace_back( MessagePayload( PAYLOAD_PHYSICS_OBJECT, pPhysicsBody ) );
	Messenger::SendMessage( SYSTEM_PHYSICS_ENGINE, Message( SYSTEM_ENTITY, MESSAGE_ADD_PHYSICS_BODY, myPayload ) );
}







