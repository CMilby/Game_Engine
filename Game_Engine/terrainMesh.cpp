//
//  terrainMesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "terrainMesh.h"

#include <cassert>
#include <cfloat>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "input.h"
#include "random.h"
#include "simplexNoise.h"
#include "utility.h"

TerrainMesh::TerrainMesh( const std::string &file, float radius, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers, const std::string &position, int level, float &lastX, float &lastY, float &lastZ ) {
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
		m_vertices[ i ] = CalculateHeight( m_vertices[ i ], m_normals[ i ] );
    }
	
	
	/*
	 
	 Quadtree Example
	 +---------------+-------+---+---+
	 |               |       |       |
	 |               |       |       |
	 |               |       |       |
	 |               +-------+---+---+
	 |               |       |   |   |
		             |		 +---+---+
	 |               |       |   |   |
	 +-------+-------+-------+---+---+
	 |       |       |               |
	 |       |       |               |
	 |       |       |               |
	 +-------+-------+               |
	 |       |       |               |
	 |       |       |               |
	 |       |       |               |
	 +-------+-------+---------------+
	 
	*/
	
	if ( position == "top_right" ) {
		if ( zOffset == 0.0f ) {
			lastX += scale;
			lastY += scale;
			
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), lastX, lastX + scale, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( -Math3D::Scale( m_uvs[ i ].GetY(), lastY, lastY + scale, 1.0f, 0.0f ) );
			}
		}
	} else if ( position == "top_left" ) {
		if ( zOffset == 0.0f ) {
			lastY += scale;
			
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), lastX, lastX + scale, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( -Math3D::Scale( m_uvs[ i ].GetY(), lastY, lastY + scale, 1.0f, 0.0f ) );
			}
		}
	} else if ( position == "bottom_right" ) {
		if ( zOffset == 0.0f ) {
			lastX += scale;
			
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX(  Math3D::Scale( m_uvs[ i ].GetX(), lastX, lastX + scale, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( -Math3D::Scale( m_uvs[ i ].GetY(), lastY, lastY + scale, 1.0f, 0.0f ) );
			}
		}
	} else if ( position == "bottom_left" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX(  Math3D::Scale( m_uvs[ i ].GetX(), lastX, lastX + scale, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( -Math3D::Scale( m_uvs[ i ].GetY(), lastY, lastY + scale, 1.0f, 0.0f ) );
			}
		}
	}
    
    if ( generateBuffers ) {
        GenerateBuffers();
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
    
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 1 );
    
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
    
    return position + normal * noise;
}




