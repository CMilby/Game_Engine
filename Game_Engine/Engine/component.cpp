//
//  component.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "component.h"

Component::Component( ComponentType pType ) {
	m_type = pType;
	m_parent = 0;
}

Component::~Component() {
	
}
