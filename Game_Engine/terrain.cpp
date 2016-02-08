//
//  terrain.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "terrain.h"

#include "simplexNoise.h"

Terrain::Terrain( const std::string &file, float radius, unsigned int level, float direction, bool x, bool y, bool z, float xOffset, float yOffset, float zOffset, float scale, const std::string &position ) {
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
    
    TerrainMesh *terrain = new TerrainMesh( m_file, radius, xOffset, yOffset, zOffset, scale, true, position, level );
    SetMesh( terrain );
    SetMaterial( new Material( new Texture( "earth.jpg" ) ) );
    // SetMaterial( new Material( new Texture( 8, 8, &terrain->GetTextureData()[ 0 ] ) ) );
    // GenerateTexture();
    SetVisible( true );
}

Terrain::~Terrain() {
    
}

void Terrain::RenderAll( const std::vector<Shader*> &shaders, const Camera &camera ) {
    RenderableEntity::RenderAll( shaders, camera );
   
    float distance = Math3D::Distance( camera.GetPosition(), m_realPosition );
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
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z + scale, scale, "top_right" );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z + scale, scale, "top_left" );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z - scale, scale, "bottom_right" );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z - scale, scale, "bottom_left" );
    } else if ( m_splitX && m_splitY ) {
        float x = m_position.GetX();
        float y = m_position.GetY();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y + scale, 0.0f, scale, "top_right" );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y + scale, 0.0f, scale, "top_left" );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y - scale, 0.0f, scale, "bottom_right" );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y - scale, 0.0f, scale, "bottom_left" );
    } else if ( m_splitY && m_splitZ ) {
        float y = m_position.GetY();
        float z = m_position.GetZ();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z + scale, scale, "top_right" );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z + scale, scale, "top_left" );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z - scale, scale, "bottom_right" );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z - scale, scale, "bottom_left" );
    }
    
    AddChild( t1 );
    AddChild( t2 );
    AddChild( t3 );
    AddChild( t4 );
    
    SetVisible( false );
    m_split = true;
}

void Terrain::Join() {
    ClearChildren();
    SetVisible( true );
    m_split = false;
}

float Terrain::SplitDistance( int level ) {
    /*if ( level > m_maxLevel ) {
        return 0.0f;
    }
    
    if ( level == m_maxLevel ) {
        return 50.0f;
    }
    
    return SplitDistance( level + 1 ) * 2.0f;*/
	
	if ( m_level == 3 ) {
		return 150.0f;
	}
	
	if ( m_level == 2 ) {
		return 175.0f;
	}
    if ( m_level == 1 ) {
        return 200.0f;
		// return 50.0f;
    }
    
    return 0.0f;
}

void Terrain::GenerateTexture() {
    std::vector<float> values;
    
    for ( int i = 0; i < 32; i++ ) {
        for ( int j = 0; j < 32; j++ ) {
            static const float HEIGHT_MAX = 24.5f;
            static const float HEIGHT_MIN = -31.0f;
            static const float NOISE_PERSISTENCE = 0.3f;
            static const float NOISE_OCTAVES = 8.0f;
            static const float NOISE_SCALE = 0.007f;
            
            float noise = ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, j, i, -1 );
            // noise = Math3D::Scale( noise, 0.0f, 1.0f );
            values.push_back( noise );
            values.push_back( noise );
            values.push_back( noise );
        }
    }
    
    SetMaterial( new Material( new Texture( GRID_SIZE, GRID_SIZE, &values[ 0 ] ) ) );
}











