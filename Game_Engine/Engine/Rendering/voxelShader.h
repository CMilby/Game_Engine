//
//  voxelShader.h
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __VOXEL_SHADER_H__
#define __VOXEL_SHADER_H__

#include "shader.h"

class VoxelShader : public Shader {
	
public:
	VoxelShader();
	virtual ~VoxelShader();
	virtual void Init();
	
	virtual void Enable() const;
	virtual void Disable() const;
	
	virtual void UpdateUniforms( const Matrix4<float> &pModel, const Matrix4<float> &pView , const Matrix4<float> &pProjection, Texture *pTexture );
};

#endif /* voxelShader_h */
