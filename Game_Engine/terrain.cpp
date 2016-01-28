//
//  terrain.cpp
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "terrain.h"

Terrain::Terrain( const std::string &file, float radius, unsigned int level, float direction, bool x, bool y, bool z, float xOffset, float yOffset, float zOffset, float scale ) {
    m_file = file;
    
    m_radius = radius;
    m_level = level;    
    
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
    
    Vector3<float> position = m_realPosition;
    float x2 = position.GetX() * position.GetX();
    float y2 = position.GetY() * position.GetY();
    float z2 = position.GetZ() * position.GetZ();
    
    float dx = position.GetX() * sqrtf( 1.0f - ( y2 * 0.5f ) - ( z2 * 0.5f ) + ( ( y2 * z2 ) / 3.0f ) );
    float dy = position.GetY() * sqrtf( 1.0f - ( z2 * 0.5f ) - ( x2 * 0.5f ) + ( ( z2 * x2 ) / 3.0f ) );
    float dz = position.GetZ() * sqrtf( 1.0f - ( x2 * 0.5f ) - ( y2 * 0.5f ) + ( ( x2 * y2 ) / 3.0f ) );
    
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
    
    SetMesh( new TerrainMesh( m_file, radius, xOffset, yOffset, zOffset, scale, true ) );
    SetMaterial( new Material( new Texture( "test.png" ) ) );
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
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z + scale, scale );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z + scale, scale );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, 0.0f, z - scale, scale );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, 0.0f, z - scale, scale );
    } else if ( m_splitX && m_splitY ) {
        float x = m_position.GetX();
        float y = m_position.GetY();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y + scale, 0.0f, scale );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y + scale, 0.0f, scale );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x + scale, y - scale, 0.0f, scale );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, x - scale, y - scale, 0.0f, scale );
    } else if ( m_splitY && m_splitZ ) {
        float y = m_position.GetY();
        float z = m_position.GetZ();
        
        t1 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z + scale, scale );
        t2 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z + scale, scale );
        t3 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y + scale, z - scale, scale );
        t4 = new Terrain( m_file, m_radius, m_level + 1, m_direction, m_splitX, m_splitY, m_splitZ, 0.0f, y - scale, z - scale, scale );
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
    if ( level == 10 ) {
        return 50;
    }
    if ( level == 9 ) {
        return 100;
    }
    if ( level == 8 ) {
        return 200;
    }
    if ( level == 7 ) {
        return 400;
    }
    if ( level == 6 ) {
        return 800;
    }
    if ( level == 5 ) {
        return 1600;
    }
    if ( level == 4 ) {
        return 3200;
    }
    if ( level == 3 ) {
        return 6400;
    }
    if ( level == 2 ) {
        return 12000;
    }
    if ( level == 1 ) {
        return 24000;
    }
    return 0;
}












