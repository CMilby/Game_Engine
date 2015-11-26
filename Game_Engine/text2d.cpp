//
//  text2d.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "text2d.h"

#include <vector>

#include "texture.h"

Text2D::Text2D( const std::string &file ) {
    m_file = file;
}

Text2D::~Text2D() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_uvBuffer );
    
    if ( m_texture ) delete m_texture;
    if ( m_shader ) delete m_shader;
}

void Text2D::Init() {
    m_texture = new Texture( m_file, TextureType::TYPE_DDS );
    
    glGenBuffers( 1, &m_vertexBuffer );
    glGenBuffers( 1, &m_uvBuffer );
    
    m_shader = new Shader();
    m_shader->AddVertexShader( "TextVertexShader.vertexshader" );
    m_shader->AddFragmentShader( "TextVertexShader.fragmentshader" );
    m_shader->LinkProgram();
    
    m_shader->AddAttribute( "vertexPosition_screenspace" );
    m_shader->AddAttribute( "vertexUV" );
    
    m_shader->AddUniform( "myTextureSampler" );
}

void Text2D::PrintText2D( const char *text, int x, int y, int size ) {
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
        float uv_x = ( character % 16 ) / 16.0f;
        float uv_y = ( character / 16 ) / 16.0f;
        
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
    
    m_shader->Bind();
    
    m_texture->Bind();
    glUniform1i( m_shader->GetUniform( "myTextureSampler" ), 0 );
    
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_screenspace" ) );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glVertexAttribPointer( m_shader->GetAttribute( "vertexPosition_screenspace" ), 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glEnableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( m_shader->GetAttribute( "vertexUV" ), 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    glDrawArrays( GL_TRIANGLES, 0, ( GLuint ) vertices.size() );
    
    glDisable( GL_BLEND );
    
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexPosition_screenspace" ) );
    glDisableVertexAttribArray( m_shader->GetAttribute( "vertexUV" ) );
}














