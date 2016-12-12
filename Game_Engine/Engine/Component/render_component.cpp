//
//  render_component.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "render_component.h"

#include "shader_resource.h"

RenderComponent::RenderComponent( const std::string &p_mesh, const std::string &p_texture, ShaderType::ShaderType p_type ) : Component( ComponentType::RENDER_COMPONENT ) {
    m_mesh = new Mesh( p_mesh );
    m_material = new Material( p_texture );
    m_shader = ShaderResource::GetShader( p_type );
}

RenderComponent::RenderComponent( Mesh *p_mesh, Material *p_material ) : Component( ComponentType::RENDER_COMPONENT ) {
    m_mesh = p_mesh;
    m_material = p_material;
    m_shader = ShaderResource::GetShader( ShaderType::SHADER_BASIC );
}

RenderComponent::RenderComponent( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> &p_uvs, const std::vector<Vector3f> &p_normals ) : Component( ComponentType::RENDER_COMPONENT ) {
    m_mesh = new Mesh( p_indices, p_vertices, p_uvs, p_normals );
    m_material = new Material( "test.png" );
    m_shader = ShaderResource::GetShader( ShaderType::SHADER_BASIC );
}

RenderComponent::~RenderComponent() {
    if ( m_material != 0 ) {
        delete m_material;
        m_material = 0;
    }
    
    if ( m_mesh != 0 ) {
        delete m_mesh;
        m_mesh = 0;
    }
}

void RenderComponent::Execute() {
    // Shouldn't be called
}

void RenderComponent::Execute( float p_delta ) {
    // Shouldn't be called
}

void RenderComponent::Execute( Entity *p_entity ) {
    m_shader->Bind();
    
    Matrix4f model = GetParent()->GetModelMatrix();
    Matrix4f view = p_entity->GetRotation().ToRotationMatrix() * Matrix4f().Transform( p_entity->GetPosition() * -1 );
    Matrix4f projection = Transform::GetProjection();
    
    m_shader->UpdateUniforms( model, view, projection, m_material->m_texture );
    m_mesh->Render();
}

void RenderComponent::SetShaderType( ShaderType::ShaderType p_type ) {
    m_shader = ShaderResource::GetShader( p_type );
}
