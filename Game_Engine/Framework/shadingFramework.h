//
//  shadingFramework.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SHADING_FRAMEWORK_H__
#define __SHADING_FRAMEWORK_H__

#include <map>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "math3d.h"

#define INVALID_LOCATION 0xFFFFFFFF

class ShadingFramework {
    
private:
    std::map<std::string, GLuint> m_uniformMap;
    std::map<std::string, GLuint> m_attributeMap;
    
    GLuint m_program;
    GLuint m_vao;
    
    void LoadShader( const std::string &filename, int type );
    void CheckShaderError( int shader, int flag, bool isProgram, const std::string& errorMessage ) const;
    
public:
    ShadingFramework();
    virtual ~ShadingFramework();
    
    void AddFragmentShader( const std::string &filename );
    void AddVertexShader( const std::string &filename );
    
    void AttachShader( int shaderID ) const;
    void LinkProgram() const;
    
    void Bind() const;
    
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

#endif /* shadingFramework_h */
