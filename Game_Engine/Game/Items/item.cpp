//
//  item.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "item.h"

Item::Item() : Entity( EntityType::ENTITY_GAME_ITEM ) {
	m_item = "BaseItem";
	
	m_useTime = 30;
	m_timeSinceUse = 0;
	
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

Item::Item( const std::string &pItem, eHand pHand ) : Entity( EntityType::ENTITY_GAME_ITEM ) {
	m_item = pItem;
	m_hand = pHand;
	
	m_useTime = 30;
	m_timeSinceUse = 0;
	
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

void Item::Update( float pDelta ) {
	if ( m_isCoolingDown ) {
		m_currentCooldown--;
		if ( m_currentCooldown == 0 ) {
			m_isCoolingDown = false;
		}
	}
}

bool Item::Use() {
	if ( m_isCoolingDown ) {
		return false;
	}
	
	Logger::LogInfo( "Item - Use", m_item );
	
	m_isCoolingDown = true;
	m_currentCooldown = m_cooldown;
	return true;
}

void Item::Collided( Entity *pOther ) {
	// Logger::LogDebug( "Item - Collided", "Collided" );
}

void Item::SetPosition() {
	if ( m_hand == eHand::HAND_LEFT ) {
		Entity::SetPosition( Vector3<float>( m_handLeftOffset.GetXY(), ITEM_HEIGHT ) );
	} else if ( m_hand == eHand::HAND_RIGHT ) {
		Entity::SetPosition( Vector3<float>( m_handRightOffset.GetXY(), ITEM_HEIGHT ) );
	}
}

void Item::SetPosition( const Vector3<float> &pPosition ) {
	Entity::SetPosition( Vector3<float>( pPosition.GetXY(), ITEM_HEIGHT ) );
}

RenderableComponent* Item::GetRenderer() const {
	return ( RenderableComponent* ) GetComponent( ComponentType::RENDERABLE_COMPONENT );
}






