//
//  entitySystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "entitySystem.h"

EntitySystem::EntitySystem() : System( SYSTEM_ENTITY ) {
	m_root = new Entity( EntityType::ENTITY_ROOT );
}

EntitySystem::EntitySystem( Entity *root ) : System( SYSTEM_ENTITY ) {
	m_root = root;
}

EntitySystem::~EntitySystem() {
	if ( m_root ) delete m_root;
}

void EntitySystem::Init() {
	System::Init();
	
	m_callbacks[ MESSAGE_ADD_ENTITY ] = std::bind( &EntitySystem::HandleAddEntity, this, std::placeholders::_1 );
	m_callbacks[ MESSAGE_INIT ] = std::bind( &EntitySystem::HandleInit, this, std::placeholders::_1 );
}

void EntitySystem::Input( float pDelta ) {
	m_root->InputAll( pDelta );
}

void EntitySystem::Update( float pDelta ) {
	m_root->UpdateAll( pDelta );
}

void EntitySystem::Render() {
	m_root->RenderAll();
}

void EntitySystem::HandleAddEntity( const std::vector<MessagePayload> &payload ) {
	m_root->AddChild( payload[ 0 ].GetPayloadEntity() );
}

void EntitySystem::HandleInit( const std::vector<MessagePayload> &pPayload ) {
	m_root->InitAll();
}

