//
//  renderingEngine.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_H__
#define __RENDERING_ENGINE_H__

#include "math3d.h"
#include "shader.h"
#include "texture.h"

class RenderingEngine {
    
private:
    // glm::mat4 m_projection;
    // glm::mat4 m_view;
    // glm::mat4 m_model;
    Matrix4<float> m_projection;
    Matrix4<float> m_view;
    Matrix4<float> m_model;
    
    
    Shader *m_shader;
    Texture *m_texture;
public:
    RenderingEngine();
    virtual ~RenderingEngine();
    
    void Init() const;
    void Render() const;
    
    inline void SetProjection( const Matrix4<float> &projection ) { m_projection = projection; }
    inline void SetView( const Matrix4<float> &view ) { m_view = view; }
    inline void SetModel( const Matrix4<float> &model ) { m_model = model; }
};

#endif /* renderingEngine_h */
