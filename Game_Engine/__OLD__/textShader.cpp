//
//  text2d.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "textShader.h"

#include <vector>

#include "texture.h"

TextShader::TextShader( const std::string &file ) {
    m_file = file;
}

TextShader::~TextShader() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_uvBuffer );
    
    if ( m_texture ) delete m_texture;
}

void TextShader::Init() {
    m_texture = new Texture( "fonts/" + m_file );
    
    glGenBuffers( 1, &m_vertexBuffer );
    glGenBuffers( 1, &m_uvBuffer );
    
    AddVertexShader( "TextVertexShader.vs" );
    AddFragmentShader( "TextVertexShader.fs" );
    LinkProgram();
    
    AddUniform( "sampler" );
}

void TextShader::Render( const char *text, int x, int y, int size ) {
    unsigned int length = ( unsigned int ) strlen( text );
    
    std::vector<Vector2<float>> vertices;
    std::vector<Vector2<float>> uvs;
    
    for ( unsigned int i = 0; i < length; i++ ) {
        Vector2<float> vertex_up_left( x + i * size, y + size );
        Vector2<float> vertex_up_right( x + i * size + size, y + size );
        Vector2<float> vertex_down_right( x + i * size + size, y );
        Vector2<float> vertex_down_left( x + i * size, y );
        
        vertices.push_back( vertex_up_left );
        vertices.push_back( vertex_down_left );
        vertices.push_back( vertex_up_right );
        
        vertices.push_back( vertex_down_right );
        vertices.push_back( vertex_up_right );
        vertices.push_back( vertex_down_left );
        
        char character = text[ i ];
        float uv_x = ( character % ( int ) FONT_SIZE ) / FONT_SIZE;
        float uv_y = ( character / ( int ) FONT_SIZE ) / FONT_SIZE;
        
        Vector2<float> uv_up_left( uv_x, uv_y );
        Vector2<float> uv_up_right( uv_x + 1.0f / 16.0f, uv_y );
        Vector2<float> uv_down_right( uv_x + 1.0f / 16.0f, ( uv_y + 1.0f / 16.0f ) );
        Vector2<float> uv_down_left( uv_x, ( uv_y + 1.0f / 16.0f ) );
        
        uvs.push_back( uv_up_left );
        uvs.push_back( uv_down_left );
        uvs.push_back( uv_up_right );
        
        uvs.push_back( uv_down_right );
        uvs.push_back( uv_up_right );
        uvs.push_back( uv_down_left );
    }
    
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vector2<float> ), &vertices[ 0 ], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glBufferData( GL_ARRAY_BUFFER, uvs.size() * sizeof( Vector2<float> ), &uvs[ 0 ], GL_STATIC_DRAW );
    
    Bind();
    
    m_texture->Bind();
    Uniform1i( "sampler", 0 );
    
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    glDrawArrays( GL_TRIANGLES, 0, ( GLuint ) vertices.size() );
    
    glDisable( GL_BLEND );
    
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}














