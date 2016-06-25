//
//  testTerrain.cpp
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testTerrain.h"

#include "cameraSystem.h"
#include "simplexNoise.h"

#include "testMesh.h"

TestTerrain::TestTerrain( const std::string &pFilename, float pRadius, unsigned int pSize, unsigned int pLevel, const Vector3<bool> &pSplits, float pDirection, const Vector3<float> &pOffset, float pScale, const Vector3<float> &pLastPosition ) {
	m_filename = pFilename;
	m_size = pSize;
	
	m_radius = pRadius;
	m_level = pLevel;
	
	m_maxLevel  = ( int ) log2f( pRadius * 2.0f );
	m_maxLevel -= ( int ) log2f( GRID_SIZE );
	
	m_splits = pSplits;
	m_split = false;
	
	m_position = pOffset;
	m_realPosition = m_position;
	m_direction = pDirection;
	
	if ( !m_splits.GetX() ) {
		m_realPosition.SetX( pDirection );
	}
	
	if ( !m_splits.GetY() ) {
		m_realPosition.SetY( pDirection );
	}
	
	if ( !m_splits.GetZ() ) {
		m_realPosition.SetZ( pDirection );
	}
	
	Vector3<float> pos = m_realPosition;
	float x2 = pos.GetX() * pos.GetX();
	float y2 = pos.GetY() * pos.GetY();
	float z2 = pos.GetZ() * pos.GetZ();
	
	float dx = pos.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
	float dy = pos.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
	float dz = pos.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
	
	if ( isnan( dx ) ) {
		dx = 0.0f;
	}
	
	if ( isnan( dy ) ) {
		dy = 0.0f;
	}
	
	if ( isnan( dz ) ) {
		dz = 0.0f;
	}
	
	m_realPosition = Vector3<float>( dx, dy, dz ).Normalized() * m_radius;
	m_lastOffset = pLastPosition;
	
	/*
            ( 0, size, 0 )  ( size, size, 0 )
					  +------+
	                  |\      \
	                  | \      \
	                  |  \      \ <- ( size, 0, 0 )
          ( 0, 0, 0 ) +   +------+ ( size, size, size )
 ( 0, size, size ) ->  \  |      |
			            \ |      |
	                     \|      |
	                      +------+
               ( 0, 0, size ) ( size, 0, size )
	 */
	
	int mySplit = m_maxLevel - m_level + 1;
	mySplit = 1;
	
	mySplit = powf( 2.0f, ceilf( log2f( mySplit ) ) );
	
	int myMultiplier = mySplit;
	
	if ( pSplits.GetX() && pSplits.GetY() ) {
		m_textureData = TextureZProcedure( pSize, pDirection, mySplit, myMultiplier, pScale, pOffset, m_lastOffset );
	} else if ( pSplits.GetX() && pSplits.GetZ() ) {
		m_textureData = TextureYProcedure( pSize, pDirection, mySplit );
	} else if ( pSplits.GetY() && pSplits.GetZ() ) {
		m_textureData = TextureXProcedure( pSize, pDirection, mySplit );
	} else {
		fprintf( stderr, "Error: Terrain not splitting on correct axis" );
	}

	SetMaterial( new Material( new Texture( pSize, pSize, &m_textureData[ 0 ] ) ) );
	SetMesh( new TestMesh( pFilename, pRadius, pScale, pOffset ) );
	// m_lastOffset = Vector3<float>( myLastX, myLastY, myLastZ );

	SetIsVisible( true );
}

void TestTerrain::Update() {
	float myCameraDistance = Math3D::Distance( CameraSystem::GetMainCamera()->GetPosition(), m_realPosition );
	float mySplitDistace = SplitDistance( m_level );
	
	if ( !m_split ) {
		if ( myCameraDistance < mySplitDistace ) {
			Split();
		}
	} else {
		if ( myCameraDistance > mySplitDistace ) {
			Join();
		}
	}
}

void TestTerrain::Split() {
	float scale = 1.0f / powf( 2, m_level );
	
	TestTerrain *t1;
	TestTerrain *t2;
	TestTerrain *t3;
	TestTerrain *t4;
	
	if ( m_splits.GetX() && m_splits.GetZ() ) {
		// float x = m_position.GetX();
		// float z = m_position.GetZ();
		
		/*t1 = new TestTerrain( m_filename, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z + scale, scale, TERRAIN_TOP_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
		t2 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z + scale, scale, TERRAIN_TOP_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );
		t3 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z - scale, scale, TERRAIN_BOTTOM_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );
		t4 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z - scale, scale, TERRAIN_BOTTOM_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );*/
	} else if ( m_splits.GetX() && m_splits.GetY() ) {
		float x = m_position.GetX();
		float y = m_position.GetY();
		
		t1 = new TestTerrain( m_filename, m_radius, m_size, m_level + 1, m_splits, m_direction, Vector3<float>( x + scale, y + scale, 0.0f ), scale, m_lastOffset );
		t2 = new TestTerrain( m_filename, m_radius, m_size, m_level + 1, m_splits, m_direction, Vector3<float>( x - scale, y + scale, 0.0f ), scale, m_lastOffset  );
		t3 = new TestTerrain( m_filename, m_radius, m_size, m_level + 1, m_splits, m_direction, Vector3<float>( x + scale, y - scale, 0.0f ), scale, m_lastOffset  );
		t4 = new TestTerrain( m_filename, m_radius, m_size, m_level + 1, m_splits, m_direction, Vector3<float>( x - scale, y - scale, 0.0f ), scale, m_lastOffset  );
	} else if ( m_splits.GetY() && m_splits.GetZ() ) {
		// float y = m_position.GetY();
		// float z = m_position.GetZ();
		
		/*t1 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z + scale, scale, TERRAIN_TOP_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );
		t2 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z + scale, scale, TERRAIN_TOP_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );
		t3 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z - scale, scale, TERRAIN_BOTTOM_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );
		t4 = new TestTerrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z - scale, scale, TERRAIN_BOTTOM_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material  );*/
	}
	
	AddChild( t1 );
	AddChild( t2 );
	AddChild( t3 );
	AddChild( t4 );
	
	SetIsVisible( false );
	m_split = true;
}

void TestTerrain::Join() {
	ClearChildren();
	SetIsVisible( true );
	m_split = false;
}

float TestTerrain::SplitDistance( int pLevel ) const {
	if ( pLevel > m_maxLevel ) {
		return 0.0f;
	}
	
	if ( pLevel == m_maxLevel ) {
		return 50.0f;
	}
	
	return SplitDistance( pLevel + 1 ) * 2.0f;
}

void TestTerrain::ColorizeTerrain() {
	for ( unsigned int i = 0; i < m_textureData.size(); i += 4 ) {
		float myColor = m_textureData[ i ];
		
		float myRed = 0.0f;
		float myGreen = 0.0f;
		float myBlue = 0.0f;
		float myAlpha = 0.0f;
		
		if ( myColor < 0.5f ) {
			myBlue = Math3D::Scale( myColor, 0.5f, 1.0f, 0.0f, 0.5f );
		} else {
			myGreen = Math3D::Scale( myColor, 0.5f, 1.0f, 0.5f, 1.0f );
		}
		
		m_textureData[ i ] = myRed;
		m_textureData[ i + 1 ] = myGreen;
		m_textureData[ i + 2 ] = myBlue;
		m_textureData[ i + 3 ] = myAlpha;
	}
	
	SetMaterial( new Material( new Texture ( m_size, m_size, &m_textureData[ 0 ] ) ) );
}

static const float HEIGHT_MAX = 24.5f;
static const float HEIGHT_MIN = -31.0f;
static const float NOISE_PERSISTENCE = 0.3f;
static const float NOISE_OCTAVES = 8.0f;
static const float NOISE_SCALE = 0.007f;

std::vector<float> TestTerrain::TextureXProcedure( const unsigned int pSize, const float pDirection, const int pSplit ) const {
	std::vector<float> myTexture;
	
	if ( pDirection == 1.0f ) {
		for ( int i = pSize - 1; i >= 0; i-- ) {
			for ( int j = pSize - 1; j >= 0; j-- ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, pSize, i, j );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	} else if ( pDirection == -1.0f ) {
		for ( int j = pSize - 1; j >= 0; j-- ) {
			for ( unsigned int i = 0; i < pSize; i++ ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, 0.0f, j, i );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	}
	
	return myTexture;
}

std::vector<float> TestTerrain::TextureYProcedure( const unsigned int pSize, const float pDirection, const int pSplit ) const {
	std::vector<float> myTexture;
	
	if ( pDirection == 1.0f ) {
		for ( unsigned int i = 0; i < pSize; i++ ) {
			for ( unsigned int j = 0; j < pSize; j++ ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, j, pSize, i );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	} else if ( pDirection == -1.0f ) {
		for ( unsigned int i = 0; i < pSize; i++ ) {
			for ( int j = pSize - 1; j >= 0; j-- ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, j, 0.0f, i );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	}
	
	return myTexture;
}

std::vector<float> TestTerrain::TextureZProcedure( const unsigned int pSize, const float pDirection, const int pSplit, const int pMultiplier, const float pScale, const Vector3<float> &pOffset, Vector3<float> &pLastOffset ) const {
	std::vector<float> myTexture;
	
	
	/*
	 
	 Quadtree Example
	 
	 +---------------+-------+---+---+
	 |               |       |       |
	 |               |       |       |
	 |               |       |       |
	 |               +-------+---+---+
	 |               |       |   |   |
	 |				 |		 +---+---+
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
	 
	 m_uvs[ i ].SetX(  Math3D::Scale( m_uvs[ i ].GetX(), lastZ, lastZ + scale, 0.0f, 1.0f ) );
	 m_uvs[ i ].SetY( -Math3D::Scale( m_uvs[ i ].GetY(), lastY, lastY + scale, 1.0f, 0.0f ) );
	 
	*/
	
	// int myStart = pSize * pMultiplier;
	// int myEnd = pSize * pMultiplier;
	
	if ( pDirection == 1.0f ) {
		for ( int j = pSize * pMultiplier - 1; j >= 0; j -= pSplit ) {
			for ( unsigned int i = 0; i < pSize * pMultiplier; i += pSplit ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, i, j, pSize );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	} else if ( pDirection == -1.0f ) {
		for ( int i = pSize - 1; i >= 0; i-- ) {
			for ( int j = pSize - 1; j >= 0; j-- ) {
				float myNoise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, j, i, 0.0f );
				myNoise = Math3D::Scale( myNoise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
				
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( myNoise );
				myTexture.push_back( 1.0f );
			}
		}
	}
	
	return myTexture;
}









