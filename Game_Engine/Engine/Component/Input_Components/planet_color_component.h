//
//  planet_color_component.h
//  Game_Engine
//
//  Created by Craig Milby on 12/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANET_COLOR_COMPONENT_H__
#define __PLANET_COLOR_COMPONENT_H__

#include "input_component.h"
#include "planet.h"

class PlanetColorComponent : public InputComponent {
	
private:
	Planet* m_planet;
	int m_lastPressed;
	
public:
	PlanetColorComponent( Planet *p_planet );
	virtual ~PlanetColorComponent();
	
	virtual void Execute( float p_delta );
};

#endif /* planet_color_component_h */
