//
//  renderableComponent.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderableComponent.h"

#include "cameraSystem.h"
#include "renderingSystem.h"

RenderableComponent::RenderableComponent() : TransformComponent( ComponentType::RENDERABLE_COMPONENT ) {
	m_mesh = 0;
	m_material = 0;
	m_shaderType = ShaderType::SHADER_BASIC;
	m_isVisible = false;
}

RenderableComponent::RenderableComponent( const std::string &pMesh, const std::string &pTexture ) : TransformComponent( ComponentType::RENDERABLE_COMPONENT ) {
	m_mesh = new Mesh( pMesh );
	m_material = new Material( pTexture );
	m_shaderType = ShaderType::SHADER_BASIC;
	m_isVisible = true;
}

RenderableComponent::~RenderableComponent() {
	if ( m_mesh != 0 ) {
		delete m_mesh;
		m_mesh = 0;
	}
	
	if ( m_material != 0 ) {
		delete m_material;
		m_material = 0;
	}
}

void RenderableComponent::Render() {
	if ( m_isVisible ) {
		Shader *shader = RenderingSystem::GetShaders()[ m_shaderType ];
		shader->Bind();
		
		Matrix4<float> model = GetModelMatrix();
		CameraEntity *camera = CameraSystem::GetMainCamera();
		
		shader->Enable();
		
		if ( m_shaderType == SHADER_BASIC ) {
			shader->UpdateUniforms( Transform::GetProjection() * CameraSystem::GetMainCamera()->GetView() * model, *m_material );
		} else if ( m_shaderType == SHADER_PHONG ) {
			shader->UpdateUniforms( model, Transform::GetProjection() * CameraSystem::GetMainCamera()->GetView() * model, *camera, *m_material );
		} else if ( m_shaderType == SHADER_SKYBOX ) {
			
		} else if ( m_shaderType == SHADER_TEXT ) {
			
		} else if ( m_shaderType == SHADER_TILE ) {
			shader->UpdateUniforms( Transform::GetProjection() * camera->GetView() * model, *m_material );
		}
		
		shader->Disable();
		
		m_mesh->Render();
	}
}