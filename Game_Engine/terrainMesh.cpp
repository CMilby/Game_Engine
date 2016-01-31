//
//  terrainMesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "terrainMesh.h"

#include <cassert>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "input.h"
#include "random.h"
#include "simplexNoise.h"
#include "utility.h"

TerrainMesh::TerrainMesh( const std::string &file, float radius, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + file );
    
    float r = Random::InRangeF( 0.0f, 1.0f );
    float g = Random::InRangeF( 0.0f, 1.0f );
    float b = Random::InRangeF( 0.0f, 1.0f );
    
    for ( unsigned int i = 0; i < m_vertices.size(); i++ ) {
        if ( xOffset != 0.0f ) {
            m_vertices[ i ].SetX( m_vertices[ i ].GetX() * scale );
        }
        
        if ( yOffset != 0.0f ) {
            m_vertices[ i ].SetY( m_vertices[ i ].GetY() * scale );
        }
        
        if ( zOffset != 0.0f ) {
            m_vertices[ i ].SetZ( m_vertices[ i ].GetZ() * scale );
        }
        
        m_vertices[ i ] += Vector3<float>( xOffset, yOffset, zOffset );
        
        Vector3<float> position = m_vertices[ i ];
        
        float x2 = position.GetX() * position.GetX();
        float y2 = position.GetY() * position.GetY();
        float z2 = position.GetZ() * position.GetZ();
        
        float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
        float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
        float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
        
        m_normals[ i ] = Vector3<float>( dx, dy, dz ).Normalized();
        m_vertices[ i ] = m_normals[ i ] * radius;
        m_vertices[ i ] = CalculateHeight( m_vertices[ i ], m_normals[ i ] );
    
        m_colors.push_back( Vector3<float>( r, g, b ) );
    }
    
    if ( generateBuffers ) {
        glGenBuffers( 1, &m_vertexBuffer );
        glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
        glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof( Vector3<float> ), &m_vertices[ 0 ], GL_STATIC_DRAW );
        
        glGenBuffers( 1, &m_colorBuffer );
        glBindBuffer( GL_ARRAY_BUFFER, m_colorBuffer );
        glBufferData( GL_ARRAY_BUFFER, m_colors.size() * sizeof( Vector3<float> ), &m_colors[ 0 ], GL_STATIC_DRAW );
        
        glGenBuffers( 1, &m_normalBuffer );
        glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
        glBufferData( GL_ARRAY_BUFFER, m_normals.size() * sizeof( Vector3<float> ), &m_normals[ 0 ], GL_STATIC_DRAW );
        
        glGenBuffers( 1, &m_elementBuffer );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof( unsigned short ), &m_indices[ 0 ], GL_STATIC_DRAW );
        
        // GenerateBuffers();
    }
}

TerrainMesh::~TerrainMesh() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_colorBuffer );
    glDeleteBuffers( 1, &m_normalBuffer );
    glDeleteBuffers( 1, &m_elementBuffer );
}


void TerrainMesh::Render() const {
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_colorBuffer );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 1 );
    
    // glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    // glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    // glEnableVertexAttribArray( 1 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 2 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
    
    glDrawElements( GL_TRIANGLES, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
    
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
}

Vector3<float> TerrainMesh::CalculateHeight( const Vector3<float> &position, const Vector3<float> &normal ) {
    static const float HEIGHT_MAX = 24.5f;
    static const float HEIGHT_MIN = -31.0f;
    static const float NOISE_PERSISTENCE = 0.3f;
    static const float NOISE_OCTAVES = 8.0f;
    static const float NOISE_SCALE = 0.007f;
    
    float noise = ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, position.GetX(), position.GetY(), position.GetZ() );
    
    /*if ( noise <= 0.0f ) {
        // noise = 0.0f;
        // color = Vector3<float>( 0.0f, 0.0f, 1.0f );
        // m_texture.push_back( 0.0f );
        // m_texture.push_back( 0.0f );
        // m_texture.push_back( 1.0f );
    } else {
        // color = Vector3<float>( 0.0f, Math3D::Scale( noise, 0.5f, 1.0f ), 0.0f );
        // m_texture.push_back( 0.0f );
        // m_texture.push_back( 1.0f );
        // m_texture.push_back( 0.0f );
    }
    
    float tex = noise; // Math3D::Scale( noise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
    m_texture.push_back( tex );
    m_texture.push_back( tex );
    m_texture.push_back( tex );*/
    
    return position + normal * noise;
}




