//
//  renderingEngineSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "renderingEngineSystem.h"

#include "basicShader.h"
#include "phongShader.h"
#include "renderFramework.h"
#include "textShader.h"
#include "tileShader.h"

std::map<ShaderType, Shader*> RenderingEngineSystem::s_shaders = std::map<ShaderType, Shader*>();

RenderingEngineSystem::RenderingEngineSystem() : System( SYSTEM_RENDERING_ENGINE ) {
	
}

void RenderingEngineSystem::Init() {
    System::Init();
    
    RenderFramework::InitRenderer();
	
	AddShader( SHADER_PHONG, new PhongShader() );
	AddShader( SHADER_BASIC, new BasicShader() );
	AddShader( SHADER_TEXT, new TextShader( "Courier_New.png" ) );
	AddShader( SHADER_TILE, new TileShader() );
	
	InitShaders();
}

void RenderingEngineSystem::Render() {
    RenderFramework::ClearScreen();
	
    SendMessage( SYSTEM_ENTITY, Message( SYSTEM_RENDERING_ENGINE, MESSAGE_RENDER ) );
}

void RenderingEngineSystem::AddShader( const ShaderType &type, Shader *shader ) {
	s_shaders[ type ] = shader;
}

void RenderingEngineSystem::InitShaders() {
	for ( auto const &s : s_shaders ) {
		s.second->Init();
	}
}


