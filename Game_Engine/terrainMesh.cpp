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

TerrainMesh::TerrainMesh( const std::string &file, float radius, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers, const std::string &position, int level ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + file );
    
    /*float r = Random::InRangef( 0.0f, 1.0f );
    float g = Random::InRangef( 0.0f, 1.0f );
    float b = Random::InRangef( 0.0f, 1.0f );*/
    
    Vector3<float> smallest( FLT_MAX, FLT_MAX, FLT_MAX );
    Vector3<float> largest( FLT_MIN, FLT_MIN, FLT_MIN );
    
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
    
        if ( position <= smallest ) {
            smallest = position;
        }
        
        if ( position >= largest ) {
            largest = position;
        }
        
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
	
	if ( position == "top_right" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				if ( xOffset < 0.0f ) {
					
				} else {
					
				}
				
				if ( yOffset < 0.0f ) {
					
				} else {
					
				}
			}
		}
	} else if ( position == "top_left" ) {
		if ( zOffset == 0.0f ) {
			
		}
	} else if ( position == "bottom_right" ) {
		if ( zOffset == 0.0f ) {
			
		}
	} else if ( position == "bottom_left" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				if ( xOffset < 0.0f ) {
					
				} else {
					
				}
				
				if ( yOffset < 0.0f ) {
				
				} else {
					
				}
			}
		}
	}
	
	/*for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
		if ( zOffset == 0.0f ) {
			if ( xOffset < 0.0f ) {
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), xOffset - scale, xOffset, 0.0f, 1.0f ) );
			} else {
				
			}

			if ( yOffset < 0.0f ) {
				m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), yOffset - scale, yOffset, 0.0f, 1.0f ) - scale );
			} else {
				// m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), scale, scale * 2, 0.0f, 1.0f ) - scale );
			}
		}
	}*/
	
	/*if ( position == "top_right" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), xOffset, xOffset + scale, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), yOffset, yOffset + scale, 0.0f, 1.0f ) + 0.5f );
			}
		}
    } else if ( position == "top_left" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), 0.0f, 0.5f, 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), 0.5f, 1.0f, 0.0f, 1.0f ) + 0.5f );
			}
		}
    } else if ( position == "bottom_right" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				float x2 = xOffset * 2;
				float y2 = yOffset * 2;
				
				x2 = ( x2 < 0.0f ) ? 0.0f : ( x2 > 1.0f ) ? 1.0f : x2;
				y2 = ( y2 < 0.0f ) ? 0.0f : ( y2 > 1.0f ) ? 1.0f : y2;
				
				m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), x2 + scale, x2 + ( scale * 2 ), 0.0f, 1.0f ) );
				m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), y2, y2 + scale, 0.0f, 1.0f ) - scale );
			}
		}
    } else if ( position == "bottom_left" ) {
		if ( zOffset == 0.0f ) {
			for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
				// float x2 = xOffset * 2;
				// float y2 = yOffset * 2;
				
				// x2 = ( x2 < 0.0f ) ? 0.0f : ( x2 > 1.0f ) ? 1.0f : x2;
				// y2 = ( y2 < 0.0f ) ? 0.0f : ( y2 > 1.0f ) ? 1.0f : y2;
				
				// int power = level;
				
				// m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), power, power + scale, 0.0f, 1.0f ) );
				// m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), power, power + scale, 0.0f, 1.0f ) - scale );
				
				int power = powf( 2, ( level - 2 ) );
				
				if ( xOffset > 0.0f ) {
					m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), xOffset * ( level - 1 ), xOffset * ( level - 1 ) + scale, 0.0f, 1.0f ) );
				} else {
					// xOffset = fabsf( xOffset );
					m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), xOffset * ( level - 1 ), xOffset * ( level - 1 ) + scale, 0.0f, 1.0f ) );
				}
				
				if ( yOffset > 0.0f ) {
					m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), scale * ( level - 1 ), scale * ( level - 1 ) + scale, 0.0f, 1.0f ) );
				} else {
					yOffset = fabsf( yOffset );
					m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), yOffset + scale, yOffset, 0.0f, 1.0f ) );
				}
			}
			
			printf( "%f, %f", xOffset, yOffset );
		}
	}*/
	
	/*for ( unsigned int i = 0; i < m_uvs.size(); i++ ) {
		m_uvs[ i ].SetX( Math3D::Scale( m_uvs[ i ].GetX(), smallest.GetX(), largest.GetX(), -1.0f + ( scale * ( level - 1 ) ), 1.0f ) );
		m_uvs[ i ].SetY( Math3D::Scale( m_uvs[ i ].GetY(), smallest.GetY(), largest.GetY(), -1.0f + ( scale * ( level - 1 ) ),  1.0f ) );
	}*/
	
    // printf( "%f, %f, %f\n", smallest.GetX(), smallest.GetY(), smallest.GetZ() );
    // printf( "%f, %f, %f\n\n", largest.GetX(), largest.GetY(), largest.GetZ() );
    
    if ( generateBuffers ) {
        /*glGenBuffers( 1, &m_vertexBuffer );
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
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof( unsigned short ), &m_indices[ 0 ], GL_STATIC_DRAW );*/
        
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
    
    // glBindBuffer( GL_ARRAY_BUFFER, m_colorBuffer );
    // glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    // glEnableVertexAttribArray( 1 );
    
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
    
    if ( noise <= 0.0f ) {
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
    
    float tex = Math3D::Scale( noise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
    m_texture.push_back( tex );
    m_texture.push_back( tex );
    m_texture.push_back( tex );
    
    return position + normal * noise;
}




