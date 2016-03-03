//
//  renderableEntity.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderableEntity.h"

#include "renderingEngineSystem.h"

RenderableEntity::RenderableEntity() {
	m_mesh = new Mesh( "cube.obj" );
	m_material = new Material();
	m_shaderType = SHADER_PHONG;
	m_isVisible = false;
}

RenderableEntity::RenderableEntity( Mesh *mesh, Material *material ) {
	m_mesh = mesh;
	m_material = material;
	m_shaderType = SHADER_PHONG;
	m_isVisible = true;
}

RenderableEntity::~RenderableEntity() {
	if ( m_mesh ) delete m_mesh;
	if ( m_material ) delete m_material;
}

void RenderableEntity::Render() {
	if ( IsVisible() ) {
		Shader *shader = RenderingEngineSystem::GetShaders()[ m_shaderType ];
		shader->Bind();
		
		// Update uniforms accordingly
		if ( m_shaderType == SHADER_BASIC ) {
			
		} else if ( m_shaderType == SHADER_PHONG ) {
			
		} else if ( m_shaderType == SHADER_SKYBOX ) {
			
		} else if ( m_shaderType == SHADER_TEXT ) {
			
		}
	}
}