//
//  nullShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/24/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __NULL_SHADER_H__
#define __NULL_SHADER_H__

#include "shader.h"

class NullShader : public Shader {
    
private:
    
public:
    NullShader();
    virtual ~NullShader();
    
    virtual void Init();
    virtual void Enable();
    virtual void Disable();
};

#endif /* nullShader_h */
