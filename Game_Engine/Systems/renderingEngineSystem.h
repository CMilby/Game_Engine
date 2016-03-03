//
//  renderingEngineSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_SYSTEM_H__
#define __RENDERING_ENGINE_SYSTEM_H__

#include <map>

#include "shader.h"
#include "shaderType.h"
#include "system.h"

class RenderingEngineSystem : public System {
    
private:
	static std::map<ShaderType, Shader*> s_shaders;
	
public:
    RenderingEngineSystem();
    
    virtual void Init();
    virtual void Render();
	
	void AddShader( const ShaderType &type, Shader *shader );
	
	static std::map<ShaderType, Shader*> GetShaders() { return s_shaders; }
};

#endif /* renderingEngineSystem_h */
