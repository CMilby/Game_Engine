//
//  item.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "item.h"

#include "logger.h"

Item::Item() {
	m_item = "BaseItem";
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

Item::Item( const std::string &pItem, eHand pHand ) {
	m_item = pItem;
	m_hand = pHand;
	
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

Item::Item( const Vector3<float> &pPosition, const std::string &pItem ) {
	SetPosition( pPosition );
	
	m_item = pItem;
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

Item::Item( const Vector3<float> &pPosition, const std::string &pItem, eHand pHand ) {
	if ( pHand == HAND_LEFT ) {
		SetPosition( pPosition + m_handLeftOffset );
	} else if ( pHand == HAND_RIGHT ) {
		SetPosition( pPosition + m_handRightOffset );
	}
	
	m_item = pItem;
	m_hand = pHand;
	
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
	
	Logger::LogDebug( "Item - Use", m_item );
	
	m_isCoolingDown = true;
	m_currentCooldown = m_cooldown;
	return true;
}

void Item::SetPosition( const Vector3<float> &pPosition ) {
	if ( m_hand == eHand::HAND_LEFT ) {
		RenderableEntity::SetPosition( pPosition + m_handLeftOffset );
	} else if ( m_hand == eHand::HAND_RIGHT ) {
		RenderableEntity::SetPosition( pPosition + m_handRightOffset );
	}
}




