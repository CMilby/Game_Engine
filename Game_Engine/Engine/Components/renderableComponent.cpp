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

RenderableComponent::RenderableComponent() : Component( ComponentType::RENDERABLE_COMPONENT ) {
	m_mesh = 0;
	m_material = 0;
	m_shaderType = ShaderType::SHADER_BASIC;
	m_isVisible = false;
}

RenderableComponent::RenderableComponent( Mesh *pMesh ) : Component( ComponentType::RENDERABLE_COMPONENT ) {
	m_mesh = pMesh;
	m_material = 0;
	m_shaderType = SHADER_VOXEL;
	m_isVisible = true;
}

RenderableComponent::RenderableComponent( Mesh *p_mesh, const std::string &p_texture ) : Component( ComponentType::RENDERABLE_COMPONENT ) {
	m_mesh = p_mesh;
	m_material = new Material( p_texture );;
	m_shaderType = SHADER_BASIC;
	m_isVisible = true;
}

RenderableComponent::RenderableComponent( const std::string &pMesh, const std::string &pTexture ) : Component( ComponentType::RENDERABLE_COMPONENT ) {
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
		
		Matrix4<float> model = GetParent()->GetModelMatrix();
		CameraEntity *camera = CameraSystem::GetMainCamera();
		
		shader->Enable();
		
		if ( m_shaderType == SHADER_BASIC ) {
			shader->UpdateUniforms( Transform::GetProjection() * camera->GetView() * model, *m_material );
		} else if ( m_shaderType == SHADER_PHONG ) {
			shader->UpdateUniforms( model, Transform::GetProjection() * camera->GetView() * model, *camera, *m_material );
		} else if ( m_shaderType == SHADER_SKYBOX ) {
			
		} else if ( m_shaderType == SHADER_TEXT ) {
			
		} else if ( m_shaderType == SHADER_TILE ) {
			shader->UpdateUniforms( Transform::GetProjection() * camera->GetView() * model, *m_material );
		} else if ( m_shaderType == SHADER_VOXEL ) {
			shader->UpdateUniforms( model, camera->GetView(), Transform::GetProjection(), m_material->m_texture );
		}
		
		shader->Disable();
		
		m_mesh->Render();
	}
}
