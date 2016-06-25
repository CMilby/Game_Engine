//
//  tileShader.h
//  Game_Engine
//
//  Created by Craig Milby on 6/22/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TILE_SHADER_H__
#define __TILE_SHADER_H__

#include "shader.h"

class TileShader : public Shader {
	
private:
	
public:
	TileShader();
	virtual ~TileShader();
	
	virtual void Init();
	
	virtual void Enable() const;
	virtual void Disable() const;
	
	virtual void UpdateUniforms( const Matrix4<float> &pMVP, const Material &pMaterial );
};

#endif /* tileShader_h */
