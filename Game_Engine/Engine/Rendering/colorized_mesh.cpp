//
//  colorized_mesh.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 11/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "colorized_mesh.h"

ColorizedMesh::ColorizedMesh(  const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector3f> &p_normals, const std::vector<Vector3f> &p_colors ) {
    m_colors = p_colors;
    
    m_entries.push_back( MeshEntry() );
    m_entries[ 0 ].m_baseIndex = 0;
    m_entries[ 0 ].m_baseVertex = 0;
    m_entries[ 0 ].m_numIndices = ( unsigned int ) p_indices.size();
    m_entries[ 0 ].m_materialIndex = 0xFFFFFFFF;
    
    GenerateBuffers( p_indices, p_vertices, std::vector<Vector2f>(), p_normals, false );
}

ColorizedMesh::~ColorizedMesh() {
    glDeleteBuffers( NUM_BUFFERS, m_buffers );
    glDeleteBuffers( 1, &m_colorBuffer );
    glDeleteVertexArrays( 1, &m_vao );
}

void ColorizedMesh::GenerateBuffers( const std::vector<unsigned int> &pIndices, const std::vector<Vector3f> &pVertices, const std::vector<Vector2f> pUVs, const std::vector<Vector3f> pNormals, bool pInstance ) {
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray( m_vao );
    
    glGenBuffers( NUM_BUFFERS, m_buffers );
    glGenBuffers( 1, &m_colorBuffer );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ VERTEX_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, pVertices.size() * sizeof( Vector3f ), &pVertices[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ NORMAL_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, pNormals.size() * sizeof( Vector3f ), &pNormals[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 2 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_colorBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_colors.size() * sizeof( Vector3f ), &m_colors[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 3 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffers[ INDEX_BUFFER ] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof( unsigned int ), &pIndices[ 0 ], GL_STATIC_DRAW );
    
    glBindVertexArray( 0 );
}

void ColorizedMesh::Render() {
    glBindVertexArray( m_vao );
    
    for ( unsigned int i = 0; i < m_entries.size(); i++ ) {
        glDrawElementsBaseVertex( GL_TRIANGLES, m_entries[ i ].m_numIndices, GL_UNSIGNED_INT, ( void* ) ( sizeof( unsigned short ) * m_entries[ i ].m_baseIndex ), m_entries[ i ].m_baseVertex );
    }
    
    glBindVertexArray( 0 );
}
