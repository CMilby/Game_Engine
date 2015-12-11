//
//  geometryPassTech.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "geometryPassTech.h"

GBuffer GeometryPassTech::s_gBuffer = GBuffer();

GeometryPassTech::GeometryPassTech() {
    
}

void GeometryPassTech::Init() {
    AddVertexShader( "geometry_pass.vs" );
    AddFragmentShader( "geometry_pass.fs" );
    LinkProgram();
    
    AddAttribute( "Position" );
    AddAttribute( "TexCoord" );
    AddAttribute( "Normal" );
    AddAttribute( "WorldPosOut" );
    AddAttribute( "DiffuseOut" );
    AddAttribute( "NormalOut" );
    AddAttribute( "TexCoordOut" );
    
    AddUniform( "gWVP" );
    AddUniform( "gWorld" );
    AddUniform( "gColorMap" );
    
    m_pass = GEOMETRY_PASS;
}

void GeometryPassTech::UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material ) {
    if ( m_pass == GEOMETRY_PASS ) {
        Enable();
        s_gBuffer.BindWrite();
    
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
        UniformMatrix4f( "gWVP", projected );
        UniformMatrix4f( "gWorld", world );
        
        m_pass = LIGHT_PASS;
    } else if ( m_pass == LIGHT_PASS ) {
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        s_gBuffer.BindRead();
        
        GLuint width = 1024;
        GLuint height = 1024;
        GLuint halfWidth = ( GLint ) ( width / 2.0f );
        GLuint halfHeight = ( GLint ) ( height / 2.0f );
        
        /*s_gBuffer.SetReadBuffer( GBuffer::GBUFFER_TEXTURE_TYPE_POSITION );
        glBlitFramebuffer( 0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR );
        
        s_gBuffer.SetReadBuffer( GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE );
        glBlitFramebuffer( 0, 0, width, height, 0, halfHeight, halfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR );
        
        s_gBuffer.SetReadBuffer( GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL );
        glBlitFramebuffer( 0, 0, width, height, halfWidth, halfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR  );
        
        s_gBuffer.SetReadBuffer( GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD );
        glBlitFramebuffer( 0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR );
        */
        m_pass = GEOMETRY_PASS;
    }
}

void GeometryPassTech::SetWVP( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWVP", WVP );
}

void GeometryPassTech::SetWorldMatrix( const Matrix4<float> &WVP ) {
    UniformMatrix4f( "gWorld", WVP );
}

void GeometryPassTech::SetColorTextureUint( unsigned int textureUnit ) {
    Uniform1i( "gColorMap", textureUnit );
}