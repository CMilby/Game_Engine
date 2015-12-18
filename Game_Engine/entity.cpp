//
//  entity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "entity.h"

#include "camera.h"
#include "renderingEngine.h"
#include "shader.h"

Entity::Entity() {
    m_transform = new Transform();
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

void Entity::RenderAll( const std::vector<Shader*> &shaders, const Camera &camera ) {
    Render( shaders, camera );
    for ( unsigned int i = 0; i < m_children.size(); i++ ) {
        m_children[ i ]->RenderAll( shaders, camera );
    }
}

Entity* Entity::AddChild( Entity *entity ) {
    m_children.push_back( entity );
    return this;
}

RenderableEntity::RenderableEntity() {
    m_mesh = new Mesh( "cube.obj" );
    SetTransform( new Transform() );
    m_material = new Material( new Texture( "cube.DDS", TextureType::TYPE_DDS ) );
    m_visible = false;
}

RenderableEntity::RenderableEntity( Mesh *mesh, Material *material ) {
    m_mesh = mesh;
    SetTransform( new Transform() );
    m_material = material;
    m_visible = true;
}

RenderableEntity::~RenderableEntity() {
    if ( m_mesh ) delete m_mesh;
    if ( m_material ) delete m_material;
}

void RenderableEntity::Input( float delta ) {
    
}

void RenderableEntity::Update( float delta ) {
    
}

void RenderableEntity::Render( const std::vector<Shader*> &shaders, const Camera &camera ) {
    if ( m_visible ) {
        for ( int i = 0; i < shaders.size(); i++ ) {
            shaders[ i ]->Bind();
    
            shaders[ i ]->UpdateUniforms( GetModelMatrix(), Transform::GetProjection() * camera.GetView() * GetModelMatrix(), camera, *m_material, *m_mesh );
        }
    }
}

Matrix4<float> RenderableEntity::GetModelMatrix() const {
    return Matrix4<float>().Transform( GetTransform()->GetPosition() ) * GetTransform()->GetRotation().ToRotationMatrix() * Matrix4<float>().InitScale( GetTransform()->GetScale() );
}







