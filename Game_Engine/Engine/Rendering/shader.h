//
//  shader.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#include "material.h"
#include "shadingFramework.h"

class CameraEntity;

class Shader {
    
private:
    ShadingFramework *m_framework;
    
public:
    Shader();
    virtual ~Shader();
    virtual void Init() {}
    
    void AddFragmentShader( const std::string &filename );
    void AddVertexShader( const std::string &filename );
    
    void AttachShader( int shaderID ) const;
    void LinkProgram() const;
	
	virtual void Enable() const {}
	virtual void Disable() const {}
	
	void EnableVertexAttribArray( unsigned int position ) const;
	void DisableVertexAttribArray( unsigned int position ) const;
	
    void Bind() const;
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const CameraEntity &camera, const Material &material );
	virtual void UpdateUniforms( const Matrix4<float> &pMVP, const Material &pMaterial );
	virtual void UpdateUniforms( const Matrix4<float> &pModel, const Matrix4<float> &pView , const Matrix4<float> &pProjection, Texture *pTexture );
    
    void AddUniform( const std::string &name ) const;
    GLuint GetUniform( const std::string &name ) const;
    void AddAttribute( const std::string &name ) const;
    GLuint GetAttribute( const std::string &name ) const;
    
    void SetAttribLocation( const std::string &name, int location ) const;
    
    void Uniform1ui( const std::string &name, unsigned int value ) const;
    void Uniform1i( const std::string &name, int value ) const;
    void Uniform1f( const std::string &name, float value ) const;
    void UniformMatrix4f( const std::string &name, const Matrix4<float> &value ) const;
    void Uniform2f( const std::string &name, float x, float y ) const;
    void UniformVector3f( const std::string &name, const Vector3<float> &value ) const;
};

#endif /* shader_h */
