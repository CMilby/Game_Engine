//
//  entity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "entity.h"

RenderableEntity::RenderableEntity() {
    m_mesh = new Mesh( "cube.obj" );
    m_transform = new Transform();
    m_texture = new Texture( "cube.DDS" );
    m_visible = false;
}

RenderableEntity::RenderableEntity( const std::string &meshFile, const std::string &textureFile ) {
    m_mesh = new Mesh( meshFile );
    m_transform = new Transform();
    m_texture = new Texture( textureFile );
    m_visible = true;
}

RenderableEntity::~RenderableEntity() {
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        if ( m_children[ i ] ) delete m_children[ i ];
    }
    
    if ( m_mesh ) delete m_mesh;
    if ( m_transform ) delete m_transform;
    if ( m_texture ) delete m_texture;
}

void RenderableEntity::Input() const {
    
}

void RenderableEntity::InputAll() const {
    Input();
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->InputAll();
    }
}

void RenderableEntity::Update() const {
    
}

void RenderableEntity::UpdateAll() const {
    Update();
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->UpdateAll();
    }
}

void RenderableEntity::Render( const Shader &shader, const Camera &camera ) const {
    m_texture->Bind();
    shader.Uniform1i( "myTextureSampler", 0 );
    
    shader.UniformMatrix4f( "MVP", Transform::GetProjection() * camera.GetView() * GetModelMatrix() );
    shader.UniformMatrix4f( "M", GetModelMatrix() );
    m_mesh->Render();
}

void RenderableEntity::RenderAll( const Shader &shader, const Camera &camera ) const {
    if ( m_visible ) {
        Render( shader, camera );
    }
    
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->RenderAll( shader, camera );
    }
}

Matrix4<float> RenderableEntity::GetModelMatrix() const {
    return Matrix4<float>().Model( m_transform->GetPosition(), m_transform->GetScale() );
}

RenderableEntity* RenderableEntity::AddEntity( RenderableEntity *entity ) {
    m_children.emplace_back( entity );
    return this;
}






