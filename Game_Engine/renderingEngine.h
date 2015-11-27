//
//  renderingEngine.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_H__
#define __RENDERING_ENGINE_H__

#include <vector>

#include "camera.h"
#include "entity.h"
#include "math3d.h"
#include "shader.h"
#include "texture.h"
#include "text2d.h"

class RenderingEngine {
    
private:
    static Camera s_mainCamera;
    
    Shader *m_shader;
    Text2D *m_text2d;
    
public:
    RenderingEngine();
    virtual ~RenderingEngine();
    
    inline static void SetMainCamera( const Camera &camera ) { s_mainCamera = camera; }
    
    void Init() const;
    void Render( Entity &root );
};

#endif /* renderingEngine_h */
