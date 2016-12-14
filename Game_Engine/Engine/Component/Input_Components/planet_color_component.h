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

class PlanetColorComponent : public InputComponent {
	
private:
	
public:
	PlanetColorComponent();
	virtual ~PlanetColorComponent();
	
	virtual void Execute( float p_delta );
};

#endif /* planet_color_component_h */
