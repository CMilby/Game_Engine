//
//  pointLightPassTech.hpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __POINT_LIGHT_PASS_TECH_H__
#define __POINT_LIGHT_PASS_TECH_H__

#include "lightPassTech.h"
#include "lighting.h"

class PointLightPassTech : public LightPassTech {
    
public:
    PointLightPassTech();
    virtual void Init();
    
    void SetPointLight( const PointLight &pLight );
};

#endif /* pointLightPassTech_hpp */
