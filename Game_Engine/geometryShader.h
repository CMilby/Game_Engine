//
//  geometryShader.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GEOMETRY_SHADER_H__
#define __GEOMETRY_SHADER_H__

#include "shader.h" 

class GeometryShader : public Shader {
    
private:
    
public:
    GeometryShader();
    virtual ~GeometryShader();
    
    virtual void Init();
};

#endif /* geometryShader_h */
