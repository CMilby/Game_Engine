//
//  entity.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "entity.h"

Entity::Entity() {
	
}

Entity::Entity( const Transform &transform ) {
	m_transform = transform;
}

Entity::Entity( const Vector3<float> &position ) {
	m_transform.SetPosition( position );
}

Entity::~Entity() {
	
}

Entity* Entity::AddChild( Entity *child ) {
	m_children.emplace_back( child );
	return this;
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







