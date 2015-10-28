//
//  renderingEngine.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_H__
#define __RENDERING_ENGINE_H__

#include "camera.h"
#include "entity.h"
#include "math3d.h"
#include "shader.h"
#include "texture.h"

class RenderingEngine {
    
private:
    RenderableEntity *m_monkey;
    RenderableEntity *m_cube;
    
    Camera *m_camera;
    Shader *m_shader;
public:
    RenderingEngine();
    virtual ~RenderingEngine();
    
    void Init() const;
    void Render( const Entity &root ) const;
};

#endif /* renderingEngine_h */
