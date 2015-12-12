//
//  nullTech.hpp
//  Game_Engine
//
//  Created by Craig Milby on 12/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __NULL_TECH_H__
#define __NULL_TECH_H__

#include "math3d.h"
#include "shader.h"

class NullTech : public Shader {
    
private:
    
public:
    NullTech();
    virtual ~NullTech();
    
    virtual void Init();
    
    void SetWVP( const Matrix4<float> &WVP );
};

#endif /* nullTech_hpp */
