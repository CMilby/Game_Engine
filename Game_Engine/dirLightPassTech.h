//
//  dirLightPassTech.h
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __DIRECTION_LIGHT_PASS_TECH_H__
#define __DIRECTION_LIGHT_PASS_TECH_H__

#include "lightPassTech.h"
#include "lighting.h"

class DirLightPassTech : public LightPassTech {
    
public:
    DirLightPassTech();
    virtual void Init();
    
    void SetDirectionalLight( const DirectionalLight &light );
};

#endif /* dirLightPassTech_h */
