//
//  planet.h
//  Game_Engine_New
//
//  Created by Craig Milby on 11/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANET_H__
#define __PLANET_H__

#include <list>
#include <set>
#include <vector>

#include "colorized_mesh.h"
#include "random.h"
#include "vector.h"

namespace PlateType {
    enum PlateType {
        PLATE_LAND,
        PLATE_WATER
    };
}

struct Plate;
struct Tri;

struct Hex {
    std::string m_id;
    bool m_pentagon;
    
    Plate* m_plate;
	Vector3f m_stress;
	float m_elevation;
    
    std::vector<Tri*> m_tris;
    std::vector<Hex*> m_neighbors;
    
    Vector3f m_center;
    Vector3f m_color;
    
    Hex() {}
    Hex( const std::vector<Tri*> &p_tris );
    Hex( const std::vector<Tri*> &p_tris, bool p_isPent );

    unsigned long TriCount() const { return m_tris.size(); }
    
    bool operator==( const Hex &p_other ) const {
        return m_id == p_other.m_id;
    }
    
    bool Equals( Hex *p_other ) const {
        return m_id == p_other->m_id;
    }
    
    bool operator<( const Hex &p_other ) const {
        if ( m_pentagon && !p_other.m_pentagon ) {
            return true;
        } else if ( !m_pentagon && p_other.m_pentagon ) {
            return false;
        }
        return m_id < p_other.m_id;
    }
    
    void Colorize( std::vector<Vector3f> &p_colors ) {
        if ( m_pentagon ) {
            for ( unsigned int i = 0; i < 3; i++ ) {
                p_colors.push_back( m_color );
                p_colors.push_back( m_color );
                p_colors.push_back( m_color );
            }
        } else {
            for ( unsigned int i = 0; i < 4; i++ ) {
                p_colors.push_back( m_color );
                p_colors.push_back( m_color );
                p_colors.push_back( m_color );
            }
        }
    }
    
    std::vector<Tri*> NeighborTriangles() const;
    Vector3f Centroid() const;
    
    Tri* operator[]( unsigned long p_index ) const { return m_tris[ p_index ]; }
};

struct Tri {
    int m_id;
    
    Vector3i m_indices;
    Vector3f m_x;
    Vector3f m_y;
    Vector3f m_z;
    
    Vector3f m_color;
    
    Tri* m_a;
    Tri *m_b;
    Tri *m_c;
    
    Tri *m_parent;
    Tri *m_child;
    
    std::vector<Hex*> m_hexes;
    
    Tri( int p_id, const Vector3i &p_indices, const Vector3f &p_x, const Vector3f &p_y, const Vector3f &p_z, Tri *p_a = 0, Tri *p_b = 0, Tri *p_c = 0 ) : m_id( p_id ), m_indices( p_indices ), m_x( p_x ), m_y( p_y ), m_z( p_z ), m_a( p_a ), m_b( p_b ), m_c( p_c ), m_parent( 0 ), m_child( 0 ), m_color( Vector3f( 0.5f, 0.5f, 0.5f ) ) {}
    
    bool IsTriNeighbor( Tri *p_tri ) const {
        return ( m_a == p_tri || m_b == p_tri || m_c == p_tri );
    }
    
    bool IsXYAdjacent( Tri *p_tri ) const {
        if  ( ( ( m_x == p_tri->m_x ) && ( m_y == p_tri->m_y ) ) ||
             ( ( m_x == p_tri->m_y ) && ( m_y == p_tri->m_z ) ) ||
             ( ( m_x == p_tri->m_z ) && ( m_y == p_tri->m_x ) ) ||
             ( ( m_y == p_tri->m_x ) && ( m_x == p_tri->m_y ) ) ||
             ( ( m_y == p_tri->m_y ) && ( m_x == p_tri->m_z ) ) ||
             ( ( m_y == p_tri->m_z ) && ( m_x == p_tri->m_x ) ) ) {
            return true;
        }
        return false;
    }
    
    bool IsYZAdjacent( Tri *p_tri ) const {
        if  ( ( ( m_y == p_tri->m_x ) && ( m_z == p_tri->m_y ) ) ||
             ( ( m_y == p_tri->m_y ) && ( m_z == p_tri->m_z ) ) ||
             ( ( m_y == p_tri->m_z ) && ( m_z == p_tri->m_x ) ) ||
             ( ( m_z == p_tri->m_x ) && ( m_y == p_tri->m_y ) ) ||
             ( ( m_z == p_tri->m_y ) && ( m_y == p_tri->m_z ) ) ||
             ( ( m_z == p_tri->m_z ) && ( m_y == p_tri->m_x ) ) ) {
            return true;
        }
        return false;
    }
    
    bool IsZXAdjacent( Tri *p_tri ) const {
        if  ( ( ( m_z == p_tri->m_x ) && ( m_x == p_tri->m_y ) ) ||
             ( ( m_z == p_tri->m_y ) && ( m_x == p_tri->m_z ) ) ||
             ( ( m_z == p_tri->m_z ) && ( m_x == p_tri->m_x ) ) ||
             ( ( m_x == p_tri->m_x ) && ( m_z == p_tri->m_y ) ) ||
             ( ( m_x == p_tri->m_y ) && ( m_z == p_tri->m_z ) ) ||
             ( ( m_x == p_tri->m_z ) && ( m_z == p_tri->m_x ) ) ) {
            return true;
        }
        return false;
    }
    
    Vector3f Centroid() const {
        return ( m_x + m_y + m_z ) / 3.0f;
    }
    
    int GetX() const { return m_indices.GetX(); }
    int GetY() const { return m_indices.GetY(); }
    int GetZ() const { return m_indices.GetZ(); }
    
    std::vector<Tri*> Neighbors() const {
        std::vector<Tri*> nbrs;
        nbrs.push_back( m_a );
        nbrs.push_back( m_b );
        nbrs.push_back( m_c );
        return nbrs;
    }
    
    std::vector<Tri*> Neighbors( Tri* p_exclude ) const {
        std::vector<Tri*> nbrs;
        if ( m_a != p_exclude ) {
            nbrs.push_back( m_a );
        }
        
        if ( m_b != p_exclude ) {
            nbrs.push_back( m_b );
        }
        
        if ( m_c != p_exclude ) {
            nbrs.push_back( m_c );
        }
        
        return nbrs;
    }
    
    bool operator==( const Tri &p_other ) const {
        return m_indices == p_other.m_indices;
    }
    
    bool operator<( const Tri &p_other ) const {
        return ( m_x < p_other.m_x ) && ( m_y < p_other.m_y ) && ( m_z < p_other.m_z );
    }
};

struct Plate {
    std::vector<Hex*> m_hexes;
    std::vector<Hex*> m_neighbors;
    
    Vector3f m_color;
    
    // Vector3f m_rotationAxis;
    // float m_rotationAmount;
    
    // Vector3f m_driftDirection;
    // float m_driftAmount;
	Vector3f m_drift;
	
    PlateType::PlateType m_plateType;
    
    Plate() {}
    Plate( const std::vector<Hex*> &p_hexes ) : m_hexes( p_hexes ) {}

    void Add( Hex* p_hex );
};

class Planet {
    
private:
    std::vector<Hex*> m_hexes;
    std::vector<Plate*> m_plates;
    
    std::vector<unsigned int> m_indices;
    std::vector<Vector3f> m_vertices;
    std::vector<Vector3f> m_normals;
    std::vector<Vector3f> m_colors;
    
    Random *m_random;
    unsigned int m_seed;
    
    float m_waterPercentage;
    
protected:
    void CreateIcosahedron( float p_radius, std::vector<Vector3f> &p_vertices, std::vector<Tri*> &p_tris );
    void SubdivideIcosahedron( float p_radius, unsigned int p_recursions, std::vector<Vector3f> &p_vertices, std::vector<Tri*> &p_tris );
    void CreateHexagons( const std::vector<Tri*> &p_tris, std::vector<Hex*> &p_hexes, std::vector<unsigned int> &p_indices, std::vector<Vector3f> &p_vertices, std::vector<Vector3f> &p_normals );
    void CreatePlates( unsigned int p_numPlates, const std::vector<Hex*> &p_hexes, std::vector<Plate*> &p_plates );
    void CalculateStress( std::vector<Plate*> &p_plate );
    
public:
    Planet( unsigned int p_seed, unsigned int p_recursions, float p_radius, unsigned int p_numPlates );
    virtual ~Planet();
    
    ColorizedMesh* CreateMesh() {
        return new ColorizedMesh( m_indices, m_vertices, m_normals, m_colors );
    }
	
	void ColorizeNeighbors( std::vector<Vector3f> &p_colors, int p_index, const std::vector<Hex*> &p_hexes );
	void ColorizeRandom( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes );
	void ColorizePlates( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes );
	void ColorizePlateTypes( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes );
	void ColorizeStressVector(  std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes );
	
	std::vector<Vector3f> ColorizeRandom();
	std::vector<Vector3f> ColorizePlates();
	std::vector<Vector3f> ColorizePlateTypes();
	std::vector<Vector3f> ColorizeStressVector();
private:
    void Colorize( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes );
	
    std::vector<Tri*> BFS( Tri* p_start, Tri* p_end, Tri* p_exclude );
};

#endif /* planet_h */
