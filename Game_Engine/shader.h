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

class Shader {
    
private:
    static std::map<std::string, GLuint> s_uniformMap;
    static std::map<std::string, GLuint> s_attributeMap;
    
    GLuint m_program;
    
    void LoadShader( const std::string &filename, int type );
    
public:
    Shader();
    virtual ~Shader();
    
    void AddFragmentShader( const std::string &filename );
    void AddVertexShader( const std::string &filename );
    
    void AttachShader( int shaderID ) const;
    void LinkProgram() const;
    
    void Bind() const;
    
    void AddUniform( const std::string &name );
    inline GLuint GetUniform( const std::string &name ) const { return s_uniformMap[ name ]; }
    void AddAttribute( const std::string &name );
    inline GLuint GetAttribute( const std::string &name ) const { return s_attributeMap[ name ]; };
};

#endif /* shader_h */
