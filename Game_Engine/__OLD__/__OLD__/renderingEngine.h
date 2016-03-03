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
#include "skyboxShader.h"
#include "textShader.h"

class RenderingEngine {
    
private:
    static Camera s_mainCamera;
    
    std::vector<Shader*> m_shaders;
    
    Shader *m_standardShader;
    Skybox *m_skybox;
    TextShader *m_textShader;
    
public:
    RenderingEngine();
    virtual ~RenderingEngine();
    
    inline static void SetMainCamera( const Camera &camera ) { s_mainCamera = camera; }
    
    void Init();
    void Render( Entity &root );
};

#endif /* renderingEngine_h */
