//
//  item.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "item.h"

Item::Item() {

}

void Item::Update() {
	if ( m_isCoolingDown ) {
		m_cooldown--;
		if ( m_cooldown == 0 ) {
			m_isCoolingDown = false;
		}
	}
} 

void Item::Use() {
	if ( m_isCoolingDown ) {
		return;
	}
	
	m_isCoolingDown = true;
	m_currentCooldown = m_cooldown;
}