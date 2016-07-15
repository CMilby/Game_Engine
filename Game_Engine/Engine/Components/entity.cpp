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
	m_parent = 0;
}

Entity::Entity( const Transform &transform ) {
	m_transform = transform;
	m_physicsBody = 0;
	m_parent = 0;
}

Entity::Entity( const Vector3<float> &position ) {
	m_transform.SetPosition( position );
	m_physicsBody = 0;
	m_parent = 0;
}

Entity::~Entity() {
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		if ( m_children[ i ] ) {
			delete m_children[ i ];
		}
	}
	
	if ( m_physicsBody ) {
		delete m_physicsBody;
		m_physicsBody = 0;
	}
	
	if ( m_parent != 0 ) {
		delete m_parent;
		m_parent = 0;
	}
}

Entity* Entity::AddChild( Entity *child ) {
	child->SetParent( this );
	m_children.emplace_back( child );
	return this;
}

void Entity::Update( float pDelta ) {
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

void Entity::InputAll( float pDelta ) {
	Input( pDelta );
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->InputAll( pDelta );
	}
}

void Entity::UpdateAll( float pDelta ) {
	Update( pDelta );
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->UpdateAll( pDelta );
	}
}

void Entity::RenderAll() {
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->RenderAll();
	}
	Render();
}

void Entity::SetPhysicsBody( PhysicsBody *pPhysicsBody ) {
	m_physicsBody = pPhysicsBody;
	std::vector<MessagePayload> myPayload;
	myPayload.emplace_back( MessagePayload( PAYLOAD_PHYSICS_OBJECT, pPhysicsBody ) );
	Messenger::SendMessage( SYSTEM_PHYSICS_ENGINE, Message( SYSTEM_ENTITY, MESSAGE_ADD_PHYSICS_BODY, myPayload ) );
}

void Entity::RemoveChild( Entity *pEntity ) {
	auto myIter = std::find( m_children.begin(), m_children.end(), pEntity );
	if ( myIter != m_children.end() ) {
		m_children.erase( m_children.begin() + std::distance( m_children.begin(), myIter ) );
	}
}

void Entity::RemoveChild( int pIndex ) {
	m_children.erase( m_children.begin() + pIndex );
}

Matrix4<float> Entity::GetModelMatrix() const {
	if ( m_parent != 0 ) {
		return m_parent->GetModelMatrix() * m_transform.GetModelMatrix();
	}
	return m_transform.GetModelMatrix();
}






