//
//  entity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "entity.h"

#include "camera.h"

Entity::Entity() {
    
}

Entity::~Entity() {
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        if ( m_children[ i ] ) delete m_children[ i ];
    }
}

void Entity::InitAll() {
    Init();
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->InitAll();
    }
}

void Entity::InputAll( float delta ) {
    Input( delta );
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->InputAll( delta );
    }
}

void Entity::UpdateAll( float delta ) {
    Update( delta );
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->UpdateAll( delta );
    }
}

void Entity::RenderAll( const Shader &shader, const Camera &camera ) {
    Render( shader, camera );
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->RenderAll( shader, camera );
    }
}

Entity* Entity::AddChild( Entity *entity ) {
    m_children.push_back( entity );
    return this;
}

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
    if ( m_mesh ) delete m_mesh;
    if ( m_transform ) delete m_transform;
    if ( m_texture ) delete m_texture;
}

void RenderableEntity::Input( float delta ) {
    
}

void RenderableEntity::Update( float delta ) {
    
}

void RenderableEntity::Render( const Shader &shader, const Camera &camera ) {
    if ( m_visible ) {
        m_texture->Bind();
        shader.Uniform1i( "myTextureSampler", 0 );
    
        shader.UniformMatrix4f( "MVP", Transform::GetProjection() * camera.GetView() * GetModelMatrix() );
        shader.UniformMatrix4f( "M", GetModelMatrix() );
        m_mesh->Render();
    }
}

Matrix4<float> RenderableEntity::GetModelMatrix() const {
    return Matrix4<float>().Model( m_transform->GetPosition(), m_transform->GetScale() );
}







