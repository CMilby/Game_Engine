//
//  entity.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "entity.h"

#include "component.h"

Entity::Entity( EntityType pType ) {
	m_type = pType;
	m_parent = 0;
}

Entity::~Entity() {
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		if ( m_children[ i ] != 0 ) {
			delete m_children[ i ];
		}
	}
	
	std::map<ComponentType, Component*>::iterator it;
	for ( it = m_components.begin(); it != m_components.end(); it++ ) {
		delete it->second;
	}
}


Entity* Entity::AddChild( Entity *pChild ) {
	pChild->SetParent( this );
	m_children.emplace_back( pChild );
	return this;
}

Entity* Entity::AddComponent( Component *pComponent ) {
	pComponent->SetParent( this );
	m_components.insert( std::pair<ComponentType, Component*>( pComponent->GetType(), pComponent ) );
	return this;
}

void Entity::InitAll() {
	Init();
	
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->InitAll();
	}
	
	std::map<ComponentType, Component*>::iterator it;
	for ( it = m_components.begin(); it != m_components.end(); it++ ) {
		it->second->Init();
	}
}

void Entity::UpdateAll( float pDelta ) {
	Update( pDelta );
	
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->UpdateAll( pDelta );
	}
	
	std::map<ComponentType, Component*>::iterator it;
	for ( it = m_components.begin(); it != m_components.end(); it++ ) {
		it->second->Update( pDelta );
	}
}

void Entity::InputAll( float pDelta ) {
	Input( pDelta );
	
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->InputAll( pDelta );
	}
	
	std::map<ComponentType, Component*>::iterator it;
	for ( it = m_components.begin(); it != m_components.end(); it++ ) {
		it->second->Input( pDelta );
	}
}

void Entity::RenderAll() {
	Render();
	
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		m_children[ i ]->RenderAll();
	}
	
	std::map<ComponentType, Component*>::iterator it;
	for ( it = m_components.begin(); it != m_components.end(); it++ ) {
		it->second->Render();
	}
}

Matrix4<float> Entity::GetModelMatrix() const {
	return m_transform.GetModelMatrix();
}

Component* Entity::GetComponent( ComponentType pType ) const {
	return m_components.at( pType );
}

void Entity::RemoveChild( Entity *pChild ) {
	for ( unsigned int i = 0; i < m_children.size(); i++ ) {
		if ( m_children[ i ] == pChild ) {
			delete m_children[ i ];
			m_children.erase( m_children.begin() + i );
		}
	}
}

void Entity::RemoveChild( unsigned int pIndex ) {
	delete m_children[ pIndex ];
	m_children.erase( m_children.begin() + pIndex );
}

void Entity::RemoveComponent( ComponentType pType ) {
	std::map<ComponentType, Component*>::iterator it = m_components.find( pType );
	if ( it != m_components.end() ) {
		delete it->second;
		m_components.erase( it );
	}
}


