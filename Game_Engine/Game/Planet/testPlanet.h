//
//  testPlanet.h
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TEST_PLANET_H__
#define __TEST_PLANET_H__

#include "renderableEntity.h"

class TestPlanet : public RenderableEntity {
	
private:
	float m_radius;
	unsigned int m_LoD;
	
protected:
	virtual void Init();
	
public:
	TestPlanet( float pRadius, unsigned int pLoD );
};

#endif /* testPlanet_h */
