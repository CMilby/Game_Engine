//
//  entity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "entity.h"

RenderableEntity::RenderableEntity( const std::string &meshFile, const std::string &textureFile ) {
    m_mesh = new Mesh( meshFile );
    m_transform = new Transform();
    m_texture = new Texture( textureFile );
}

RenderableEntity::~RenderableEntity() {
    if ( m_mesh ) delete m_mesh;
    if ( m_transform ) delete m_transform;
    if ( m_texture ) delete m_texture;
}

void RenderableEntity::Render( const Shader &shader ) const {
    m_texture->Bind();
    shader.Uniform1i( "myTextureSampler", 0 );
    
    shader.UniformMatrix4f( "M", GetModelMatrix() );
    m_mesh->Render();
}

Matrix4<float> RenderableEntity::GetModelMatrix() const {
    return Matrix4<float>().Model( m_transform->GetPosition(), m_transform->GetScale() );
}