//
//  item.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "item.h"

Item::Item() {
	m_cooldown = 50;
	m_currentCooldown = 0;
	m_isCoolingDown = false;
}

void Item::Update() {
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
	
	m_isCoolingDown = true;
	m_currentCooldown = m_cooldown;
	return true;
}