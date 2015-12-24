//
//  fullscreenQuad.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "fullscreenQuad.h"

#include <vector>

FullscreenQuad::FullscreenQuad() {
    std::vector<GLfloat> positions = {
        1.0f, 1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f
    };
    
    std::vector<GLuint> indices = {
        0, 1, 3,
        1, 2, 3
    };
    
    glGenVertexArrays( 1, &m_vao );
    glGenBuffers( 1, &m_indexBuffer );
    glGenBuffers( 1, &m_positionBuffer );
    
    m_numIndices = int( indices.size() );
    glBindVertexArray( m_vao );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_positionBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * positions.size(), &positions[ 0 ], GL_STATIC_DRAW );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), &indices[ 0 ], GL_STATIC_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_positionBuffer );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindVertexArray( 0 );
}

FullscreenQuad::~FullscreenQuad() {
    glDeleteVertexArrays( 1, &m_vao );
    glDeleteBuffers( 1, &m_indexBuffer );
    glDeleteBuffers( 1, &m_positionBuffer );
}

void FullscreenQuad::Render() {
    glBindVertexArray( m_vao );
    glDrawElements( GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0 );
}















