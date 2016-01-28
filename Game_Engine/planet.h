//
//  planet.h
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANET_H__
#define __PLANET_H__

#include "terrain.h"

class Planet : public RenderableEntity {
    
private:
    float m_radius;

public:
    Planet();
    virtual ~Planet();
    
    void Render();
};

#endif /* planet_h */
