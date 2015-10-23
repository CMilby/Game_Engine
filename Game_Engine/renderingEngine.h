//
//  renderingEngine.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_H__
#define __RENDERING_ENGINE_H__

#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

class RenderingEngine {
    
private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_model;
    
    Shader *m_shader;
    Texture *m_texture;
public:
    RenderingEngine();
    virtual ~RenderingEngine();
    
    void Init() const;
    void Render() const;
    
    inline void SetProjection( glm::mat4 projection ) { m_projection = projection; }
    inline void SetView( glm::mat4 view ) { m_view = view; }
    inline void SetModel( glm::mat4 model ) { m_model = model; }
};

#endif /* renderingEngine_h */
