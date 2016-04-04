//
//  terrain.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "terrain.h"

#include <thread>

#include "cameraSystem.h"
#include "simplexNoise.h"

Terrain::Terrain( const std::string &file, float radius, unsigned int level, float direction, bool x, bool y, bool z, float xOffset, float yOffset, float zOffset, float scale, const TerrainLocation &location, float lastX, float lastY, float lastZ, Material *material ) {
    m_file = file;
    
    m_radius = radius;
    m_level = level;
    
    m_maxLevel  = ( int ) log2f( radius * 2.0f );
    m_maxLevel -= ( int ) log2f( GRID_SIZE );
    
    m_splitX = x;
    m_splitY = y;
    m_splitZ = z;
    m_split = false;
    
    m_position = Vector3<float>( xOffset, yOffset, zOffset );
    m_realPosition = m_position;
    m_direction = direction;
    if ( !x ) {
        m_realPosition.SetX( direction );
    }
    
    if ( !y ) {
        m_realPosition.SetY( direction );
    }
    
    if ( !z ) {
        m_realPosition.SetZ( direction );
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
    
    TerrainMesh *terrain = new TerrainMesh( m_file, radius, xOffset, yOffset, zOffset, scale, true, location, lastX, lastY, lastZ, direction );
    SetMesh( terrain );
	
	m_location = location;
	/*if ( location == TERRAIN_ROOT ) {
		// GenerateTexture( xOffset, yOffset, zOffset, direction );
		// SetMaterial( m_material );
	} else {
		m_material = material;
		// SetMaterial( m_material );
	}*/
	
	SetIsVisible( true );
	
	m_lastXOffset = lastX;
	m_lastYOffset = lastY;
	m_lastZOffset = lastZ;
}

Terrain::~Terrain() {
    
}

void Terrain::Update() {
	float distance = Math3D::Distance( CameraSystem::GetMainCamera()->GetPosition(), m_realPosition );
	if ( !m_split ) {
		if ( distance < SplitDistance( m_level ) ) {
			Split();
		}
	} else {
		if ( distance > SplitDistance( m_level ) ) {
			Join();
		}
	}
}

void Terrain::Split() {
    float scale = 1.0f / powf( 2, m_level );
    
    Terrain *t1;
    Terrain *t2;
    Terrain *t3;
    Terrain *t4;
	
    if ( m_splitX && m_splitZ ) {
        float x = m_position.GetX();
        float z = m_position.GetZ();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z + scale, scale, TERRAIN_TOP_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z + scale, scale, TERRAIN_TOP_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z - scale, scale, TERRAIN_BOTTOM_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z - scale, scale, TERRAIN_BOTTOM_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
    } else if ( m_splitX && m_splitY ) {
        float x = m_position.GetX();
        float y = m_position.GetY();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y + scale, 0.0f, scale, TERRAIN_TOP_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y + scale, 0.0f, scale, TERRAIN_TOP_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y - scale, 0.0f, scale, TERRAIN_BOTTOM_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y - scale, 0.0f, scale, TERRAIN_BOTTOM_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
    } else if ( m_splitY && m_splitZ ) {
        float y = m_position.GetY();
        float z = m_position.GetZ();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z + scale, scale, TERRAIN_TOP_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z + scale, scale, TERRAIN_TOP_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z - scale, scale, TERRAIN_BOTTOM_RIGHT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z - scale, scale, TERRAIN_BOTTOM_LEFT, m_lastXOffset, m_lastYOffset, m_lastZOffset, m_material );
    }
    
    AddChild( t1 );
    AddChild( t2 );
    AddChild( t3 );
    AddChild( t4 );
    
    SetIsVisible( false );
    m_split = true;
}

void Terrain::Join() {
    ClearChildren();
    SetIsVisible( true );
    m_split = false;
}

float Terrain::SplitDistance( int level ) {
    if ( level > m_maxLevel ) {
        return 0.0f;
    }
    
    if ( level == m_maxLevel ) {
        return 50.0f;
    }
    
    return SplitDistance( level + 1 ) * 2.0f;
}

/*void Terrain::GenerateTexture( float xOffset, float yOffset, float zOffset, float direction ) {
	int width = m_radius * 4.0f;
	int height = width;
	std::vector<float> values;
	
	if ( !m_splitZ ) {
		std::thread texThread( &Terrain::GenerateXTexture, this, width, height, direction, std::ref( values ) );
		texThread.join();
	} else if ( !m_splitY ) {
		std::thread texThread( &Terrain::GenerateYTexture, this, width, height, direction, std::ref( values ) );
		texThread.join();
	} else if ( !m_splitX ) {
		std::thread texThread( &Terrain::GenerateZTexture, this, width, height, direction, std::ref( values ) );
		texThread.join();
	}
	
	m_material = new Material( new Texture( width, height, &values[ 0 ] ) );
}

void Terrain::GenerateXTexture( int width, int height, float direction, std::vector<float> &values ) {
	if ( direction == 1.0f ) {
		for ( int i = height - 1; i >= 0; i-- ) {
			for ( int j = 0; j < width; j++ ) {
				std::vector<float> insertValues = XProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	} else if ( direction == -1.0f ) {
		for ( int i = height - 1; i >= 0; i-- ) {
			for ( int j = width - 1; j >= 0; j-- ) {
				std::vector<float> insertValues = XProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	}
}

std::vector<float> Terrain::XProcedure( int width, int height, int i, int j, float direction ) {
	std::vector<float> values;
	
	static const float HEIGHT_MAX = 24.5f;
	static const float HEIGHT_MIN = -31.0f;
	static const float NOISE_PERSISTENCE = 0.3f;
	static const float NOISE_OCTAVES = 8.0f;
	static const float NOISE_SCALE = 0.007f;
	
	Vector3<float> position = Vector3<float>( Math3D::Scale( j, -1.0f, 1.0f, 0.0f, width - 1 ), Math3D::Scale( i, -1.0f, 1.0f, 0.0f, height - 1 ), direction );
	
	float x2 = position.GetX() * position.GetX();
	float y2 = position.GetY() * position.GetY();
	float z2 = position.GetZ() * position.GetZ();
	
	float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
	float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
	float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
	
	Vector3<float> normal = Vector3<float>( dx, dy, dz ).Normalized();
	Vector3<float> point = normal * m_radius;
	
	float noise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, point.GetX(), point.GetY(), point.GetZ() );
	
	if ( noise > 0.0f ) {
		noise = Math3D::Scale( noise, 0.5f, 1.0f, 0.0f, HEIGHT_MAX );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 0 );
		values.push_back( 1.0f );
		
	} else {
		noise = Math3D::Scale( -noise, 0.5f, 1.0f, HEIGHT_MIN, 0.0f );
		values.push_back( 0 );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 1.0f );
	}
	
	return values;
}

void Terrain::GenerateYTexture( int width, int height, float direction, std::vector<float> &values ) {
	if ( direction == 1.0f ) {
		for ( int i = 0; i < height; i++ ) {
			for ( int j = 0; j < width; j++ ) {
				std::vector<float> insertValues = YProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	} else if ( direction == -1.0f ) {
		for ( int i = 0; i < height; i++ ) {
			for ( int j = width - 1; j >= 0; j-- ) {
				std::vector<float> insertValues = YProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	}
}

std::vector<float> Terrain::YProcedure( int width, int height, int i, int j, float direction ) {
	std::vector<float> values;
	
	static const float HEIGHT_MAX = 24.5f;
	static const float HEIGHT_MIN = -31.0f;
	static const float NOISE_PERSISTENCE = 0.3f;
	static const float NOISE_OCTAVES = 8.0f;
	static const float NOISE_SCALE = 0.007f;
	
	Vector3<float> position = Vector3<float>( Math3D::Scale( j, -1.0f, 1.0f, 0.0f, height - 1 ), direction, Math3D::Scale( i, -1.0f, 1.0f, 0.0f, width - 1 ) );
	
	float x2 = position.GetX() * position.GetX();
	float y2 = position.GetY() * position.GetY();
	float z2 = position.GetZ() * position.GetZ();
	
	float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
	float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
	float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
	
	Vector3<float> normal = Vector3<float>( dx, dy, dz ).Normalized();
	Vector3<float> point = normal * m_radius;
	
	float noise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, point.GetX(), point.GetY(), point.GetZ() );
	
	if ( noise > 0.0f ) {
		noise = Math3D::Scale( noise, 0.5f, 1.0f, 0.0f, HEIGHT_MAX );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 0 );
		values.push_back( 1.0f );
		
	} else {
		noise = Math3D::Scale( -noise, 0.5f, 1.0f, HEIGHT_MIN, 0.0f );
		values.push_back( 0 );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 1.0f );
	}
	
	return values;
}

void Terrain::GenerateZTexture( int width, int height, float direction, std::vector<float> &values ) {
	if ( direction == 1.0f ) {
		for ( int i = height - 1; i >= 0; i-- ) {
			for ( int j = width - 1; j >= 0; j-- ) {
				std::vector<float> insertValues = ZProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	} else if ( direction == -1.0f ) {
		for ( int i = height - 1; i >= 0; i-- ) {
			for ( int j = 0; j < width; j++ ) {
				std::vector<float> insertValues = ZProcedure( width, height, i, j, direction );
				values.insert( values.end(), insertValues.begin(), insertValues.end() );
			}
		}
	}
}

std::vector<float> Terrain::ZProcedure( int width, int height, int i, int j, float direction ) {
	std::vector<float> values;
	
	static const float HEIGHT_MAX = 24.5f;
	static const float HEIGHT_MIN = -31.0f;
	static const float NOISE_PERSISTENCE = 0.3f;
	static const float NOISE_OCTAVES = 8.0f;
	static const float NOISE_SCALE = 0.007f;
	
	Vector3<float> position = Vector3<float>( direction, Math3D::Scale( i, -1.0f, 1.0f, 0.0f, height - 1 ), Math3D::Scale( j, -1.0f, 1.0f, 0.0f, width - 1 ) );
	
	float x2 = position.GetX() * position.GetX();
	float y2 = position.GetY() * position.GetY();
	float z2 = position.GetZ() * position.GetZ();
	
	float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
	float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
	float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
	
	Vector3<float> normal = Vector3<float>( dx, dy, dz ).Normalized();
	Vector3<float> point = normal * m_radius;
	
	float noise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, point.GetX(), point.GetY(), point.GetZ() );
	
	if ( noise > 0.0f ) {
		noise = Math3D::Scale( noise, 0.5f, 1.0f, 0.0f, HEIGHT_MAX );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 0 );
		values.push_back( 1.0f );
		
	} else {
		noise = Math3D::Scale( -noise, 0.5f, 1.0f, HEIGHT_MIN, 0.0f );
		values.push_back( 0 );
		values.push_back( 0 );
		values.push_back( noise );
		values.push_back( 1.0f );
	}
	
	return values;
}
*/










