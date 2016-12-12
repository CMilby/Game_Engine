//
//  render_system.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "render_system.h"

#include "basic_shader.h"
#include "colorized_shader.h"

#include "render_framework.h"
#include "shader_resource.h"

RenderSystem* RenderSystem::s_instance = 0;

void RenderSystem::Init() {
    RenderFramework::InitRenderer();
    
    ShaderResource::AddShader( new BasicShader() );
    ShaderResource::AddShader( new ColorizedShader() );
    ShaderResource::InitShaders();
}

void RenderSystem::Execute( Entity *p_entity ) {
    RenderFramework::ClearScreen();
    System::Execute( p_entity );
}
