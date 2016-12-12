//
//  shader.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include "entity.h"
#include "material.h"
#include "math3d.h"
#include "shader_type.h"

#define INVALID_LOCATION 0xFFFFFFFF

class Shader {
    
private:
    std::unordered_map<std::string, GLuint> m_uniformMap;
    std::unordered_map<std::string, GLuint> m_attributeMap;
    
    GLuint m_program;
    GLuint m_vao;
    ShaderType::ShaderType m_type;
    
public:
    Shader( ShaderType::ShaderType p_type );
    virtual ~Shader();
    
    virtual void Init() {}
    
    void AddFragmentShader( const std::string &p_filename );
    void AddVertexShader( const std::string &p_filename );
    
    void AttachShader( int p_shaderID ) const;
    void LinkProgram() const;
    
    virtual void Enable() const {}
    virtual void Disable() const {}
    
    void EnableVertexAttribArray( unsigned int p_position ) const;
    void DisableVertexAttribArray( unsigned int p_position ) const;
    
    void Bind() const;
    
    virtual void UpdateUniforms( const Matrix4f &p_world, const Matrix4f &p_projected, const Entity &p_camera, const Material &p_material );
    virtual void UpdateUniforms( const Matrix4f &p_MVP, const Material &p_material );
    virtual void UpdateUniforms( const Matrix4f &p_model, const Matrix4f &p_view , const Matrix4f &p_projection, Texture *p_texture );
    
    void AddUniform( const std::string &p_name );
    GLuint GetUniform( const std::string &p_name ) const;
    void AddAttribute( const std::string &p_name );
    GLuint GetAttribute( const std::string &p_name ) const;
    
    void SetAttribLocation( const std::string &p_name, int p_location ) const;
    
    void Uniform1ui( const std::string &p_name, unsigned int p_value ) const;
    void Uniform1i( const std::string &p_name, int p_value ) const;
    void Uniform1f( const std::string &p_name, float p_value ) const;
    void UniformMatrix4f( const std::string &p_name, const Matrix4f &p_value ) const;
    void Uniform2f( const std::string &p_name, float p_x, float p_y ) const;
    void UniformVector3f( const std::string &p_name, const Vector3f &p_value ) const;
    
    inline ShaderType::ShaderType GetType() const {
        return m_type;
    }
    
private:
    void LoadShader( const std::string &p_filename, int p_type );
    void CheckShaderError( int p_shader, int p_flag, bool p_isProgram, const std::string& p_errorMessage ) const;
};

#endif /* shader_h */
