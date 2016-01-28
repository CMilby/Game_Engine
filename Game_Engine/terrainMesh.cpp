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
#include "utility.h"

TerrainMesh::TerrainMesh( const std::string &file, float radius, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + file );
    
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
    }
    
    if ( generateBuffers ) {
        GenerateBuffers();
    }
}

TerrainMesh::~TerrainMesh() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_uvBuffer );
    glDeleteBuffers( 1, &m_normalBuffer );
    glDeleteBuffers( 1, &m_elementBuffer );
}

