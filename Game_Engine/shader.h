//
//  shader.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __SHADER_H__
#define __SHADER_H__

#include <map>
#include <string>

#include <GL/glew.h>

#include "camera.h"
#include "mesh.h"
#include "material.h"
#include "math3d.h"

#define INVALID_LOCATION 0xFFFFFFFF

class Shader {
    
private:
    std::map<std::string, GLuint> m_uniformMap;
    std::map<std::string, GLuint> m_attributeMap;
    
    GLuint m_program;
    GLuint m_vao;
    
    void LoadShader( const std::string &filename, int type );
    
public:
    Shader();
    virtual ~Shader();
    virtual void Init() {}
    
    void AddFragmentShader( const std::string &filename );
    void AddVertexShader( const std::string &filename );
    
    void AttachShader( int shaderID ) const;
    void LinkProgram() const;
    
    void Bind() const;
    
    virtual void Enable() const {}
    virtual void Disable() const {}
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected,  const Camera &camera, const Material &material, const Mesh &mesh );
    
    void AddUniform( const std::string &name );
    inline GLuint GetUniform( const std::string &name ) const { return m_uniformMap.at( name ); }
    void AddAttribute( const std::string &name );
    inline GLuint GetAttribute( const std::string &name ) const { return m_attributeMap.at( name ); };

    void SetAttribLocation( const std::string &name, int location ) const;
    
    void Uniform1ui( const std::string &name, unsigned int value ) const;
    void Uniform1i( const std::string &name, int value ) const;
    void Uniform1f( const std::string &name, float value ) const;
    void UniformMatrix4f( const std::string &name, const Matrix4<float> &value ) const;
    void Uniform2f( const std::string &name, float x, float y ) const;
    void UniformVector3f( const std::string &name, const Vector3<float> &value ) const;
};

#endif /* shader_h */
