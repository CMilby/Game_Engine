//
//  render_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__

#include "component.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"

class RenderComponent : public Component {
    
private:
    Mesh *m_mesh;
    Material *m_material;
    Shader *m_shader;
    
public:
    RenderComponent( const std::string &p_mesh, const std::string &p_texture, ShaderType::ShaderType p_type = ShaderType::SHADER_BASIC );
    RenderComponent( Mesh *p_mesh, Material *p_material = new Material( "test.png" ) );
    RenderComponent( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> &p_uvs, const std::vector<Vector3f> &p_normals );
    virtual ~RenderComponent();
    
    virtual void Execute();
    virtual void Execute( float p_delta );
    virtual void Execute( Entity *p_entity );
    
    void SetShaderType( ShaderType::ShaderType p_type );
};

#endif /* render_component_h */
