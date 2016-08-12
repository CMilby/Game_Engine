//
//  renderingEngineSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderingSystem.h"

#include "basicShader.h"
#include "phongShader.h"
#include "renderFramework.h"
#include "textShader.h"
#include "tileShader.h"

std::map<ShaderType, Shader*> RenderingSystem::s_shaders = std::map<ShaderType, Shader*>();

RenderingSystem::RenderingSystem() : System( SYSTEM_RENDERING_ENGINE ) {
	
}

void RenderingSystem::Init() {
    System::Init();
    
    RenderFramework::InitRenderer();
	
	AddShader( SHADER_PHONG, new PhongShader() );
	AddShader( SHADER_BASIC, new BasicShader() );
	AddShader( SHADER_TEXT, new TextShader( "Courier_New.png" ) );
	AddShader( SHADER_TILE, new TileShader() );
	
	InitShaders();
}

void RenderingSystem::Render() {
    RenderFramework::ClearScreen();
	
    SendMessage( SYSTEM_ENTITY, Message( SYSTEM_RENDERING_ENGINE, MESSAGE_RENDER ) );
}

void RenderingSystem::AddShader( const ShaderType &type, Shader *shader ) {
	s_shaders[ type ] = shader;
}

void RenderingSystem::InitShaders() {
	for ( auto const &s : s_shaders ) {
		s.second->Init();
	}
}


