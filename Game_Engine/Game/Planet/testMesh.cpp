//
//  testMesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testMesh.h"

#include "utility.h"

TestMesh::TestMesh( const std::string &pFilename, float pRadius, const float pScale, const Vector3<float> &pOffset ) {
	/*LoadOBJ( Utility::DirectoryPath() + "models/" + pFilename );
	
	for ( unsigned int i = 0; i < m_vertices.size(); i++ ) {
		if ( pOffset.GetX() != 0.0f ) {
			m_vertices[ i ].SetX( m_vertices[ i ].GetX() * pScale );
		}
		
		if ( pOffset.GetY() != 0.0f ) {
			m_vertices[ i ].SetY( m_vertices[ i ].GetY() * pScale );
		}
		
		if ( pOffset.GetZ() != 0.0f ) {
			m_vertices[ i ].SetZ( m_vertices[ i ].GetZ() * pScale );
		}
		
		m_vertices[ i ] += pOffset;
		Vector3<float> position = m_vertices[ i ];
		
		float x2 = position.GetX() * position.GetX();
		float y2 = position.GetY() * position.GetY();
		float z2 = position.GetZ() * position.GetZ();
		
		float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
		float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
		float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
		
		m_normals[ i ] = Vector3<float>( dx, dy, dz ).Normalized();
		m_vertices[ i ] = m_normals[ i ] * pRadius;
		// m_vertices[ i ] = CalculateHeight( m_vertices[ i ], m_normals[ i ] );
	}
	 
	 Quadtree Example
	 +---------------+-------+---+---+
	 |               |       |       |
	 |               |       |       |
	 |               |       |       |
	 |               +-------+---+---+
	 |               |       |   |   |
	 |		                 +---+---+
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
	
	// GenerateBuffers( false );
}





