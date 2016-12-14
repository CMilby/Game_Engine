//
//  planet.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 11/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planet.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <random>

#include "math3d.h"

Hex::Hex( const std::vector<Tri*> &p_tris ) : m_tris( p_tris ), m_color( Vector3f( 0.5f, 0.5f, 0.5f ) ), m_plate( 0 ) {
    m_pentagon = p_tris.size() == 5 ? true : false;
    
    std::vector<int> ids;
    for ( unsigned int i = 0; i < p_tris.size(); i++ ) {
        ids.push_back( p_tris[ i ]->m_id );
    }
    
    std::sort( ids.begin(), ids.end() );
    for ( unsigned int i = 0; i < ids.size(); i++ ) {
        m_id += "_" + std::to_string( ids[ i ] );
    }
    
    m_center = Centroid();
    m_elevation = 0.0f;
}

Hex::Hex( const std::vector<Tri*> &p_tris, bool p_pentagon ) : m_tris( p_tris ), m_pentagon( p_pentagon ), m_color( Vector3f( 0.5f, 0.5f, 0.5f ) ), m_plate( 0 ) {
    std::vector<int> ids;
    for ( unsigned int i = 0; i < p_tris.size(); i++ ) {
        ids.push_back( p_tris[ i ]->m_id );
    }
    
    std::sort( ids.begin(), ids.end() );
    for ( unsigned int i = 0; i < ids.size(); i++ ) {
        m_id += "_" + std::to_string( ids[ i ] );
    }
    
    m_center = Centroid();
    m_elevation = 0.0f;
}

std::vector<Tri*> Hex::NeighborTriangles() const {
    std::vector<Tri*> nbrs;
    for ( unsigned int i = 0; i < m_tris.size(); i++ ) {
        if ( std::find( m_tris.begin(), m_tris.end(), m_tris[ i ]->m_a ) == m_tris.end() ) {
            nbrs.push_back( m_tris[ i ]->m_a );
        }
        
        if ( std::find( m_tris.begin(), m_tris.end(), m_tris[ i ]->m_b ) == m_tris.end() ) {
            nbrs.push_back( m_tris[ i ]->m_b );
        }
        
        if ( std::find( m_tris.begin(), m_tris.end(), m_tris[ i ]->m_c ) == m_tris.end() ) {
            nbrs.push_back( m_tris[ i ]->m_c );
        }
    }
    
    return nbrs;
}

Vector3f Hex::Centroid() const {
    if ( m_pentagon ) {
        return m_tris[ 2 ]->Centroid().Midpoint( m_tris[ 0 ]->Centroid().Midpoint( m_tris[ 4 ]->Centroid() ) );
    } else {
        return m_tris[ 1 ]->Centroid().Midpoint( m_tris[ 4 ]->Centroid() );
    }
}

bool HexLess( Hex *p_a, Hex *p_b ) {
    return *p_a < *p_b;
}

bool HexEquals( Hex *p_a, Hex *p_b ) {
    return p_a->Equals( p_b );
}

void Plate::Add( Hex* p_hex ) {
    m_hexes.push_back( p_hex );
    
    for ( unsigned int i = 0; i < p_hex->m_neighbors.size(); i++ ) {
        if ( std::find( m_neighbors.begin(), m_neighbors.end(), p_hex->m_neighbors[ i ] ) == m_neighbors.end() ) {
            m_neighbors.push_back( p_hex->m_neighbors[ i ] );
        }
    }
}

Planet::Planet( unsigned int p_seed, unsigned int p_recursions, float p_radius, unsigned int p_numPlates ) {
    std::vector<unsigned int> indices;
    std::vector<Vector3f> vertices;
    std::vector<Vector3f> normals;
    std::vector<Vector3f> colors;
    
    std::vector<Tri*> tris;
    std::vector<Hex*> hexes;
    std::vector<Plate*> plates;
    
    m_seed = p_seed;
    m_random = new Random( p_seed );
    
    m_waterPercentage = 0.65f;
    
    CreateIcosahedron( p_radius, vertices, tris );
    SubdivideIcosahedron( p_radius, p_recursions, vertices, tris );
    CreateHexagons( tris, hexes, indices, vertices, normals );
    CreatePlates( p_numPlates, hexes, plates );
	CalculateStress( plates );
	
    // ColorizeRandom( colors, hexes );
    ColorizePlates( colors, hexes );
    // ColorizePlateTypes( colors, hexes );
	// ColorizeStressVector( colors, hexes );
	
    m_hexes = hexes;
    m_indices = indices;
    m_vertices = vertices;
    m_normals = normals;
    m_colors = colors;
}

Planet::~Planet() {
    
}

void Planet::CreateIcosahedron( float p_radius, std::vector<Vector3f> &p_vertices, std::vector<Tri*> &p_tris ) {
    std::vector<Vector3f> vertList;
    std::vector<Tri*> tris;
    
    float t = ( 1.0f + sqrtf( 5.0f ) ) / 2.0f;
    vertList.push_back( Vector3f( -1.0f,  t, 0.0f ).Normalized() * p_radius ); // 0
    vertList.push_back( Vector3f( -t, 0.0f,  1.0f ).Normalized() * p_radius ); // 11
    vertList.push_back( Vector3f( 0.0f,  1.0f,  t ).Normalized() * p_radius ); // 5
    
    vertList.push_back( Vector3f( -1.0f,  t, 0.0f ).Normalized() * p_radius ); // 0
    vertList.push_back( Vector3f( 0.0f,  1.0f,  t ).Normalized() * p_radius ); // 5
    vertList.push_back( Vector3f(  1.0f,  t, 0.0f ).Normalized() * p_radius ); // 1
    
    vertList.push_back( Vector3f( -1.0f,  t, 0.0f ).Normalized() * p_radius ); // 0
    vertList.push_back( Vector3f(  1.0f,  t, 0.0f ).Normalized() * p_radius ); // 1
    vertList.push_back( Vector3f( 0.0f,  1.0f, -t ).Normalized() * p_radius ); // 7
    
    vertList.push_back( Vector3f( -1.0f,  t, 0.0f ).Normalized() * p_radius ); // 0
    vertList.push_back( Vector3f( 0.0f,  1.0f, -t ).Normalized() * p_radius ); // 7
    vertList.push_back( Vector3f( -t, 0.0f, -1.0f ).Normalized() * p_radius ); // 10
    
    vertList.push_back( Vector3f( -1.0f,  t, 0.0f ).Normalized() * p_radius ); // 0
    vertList.push_back( Vector3f( -t, 0.0f, -1.0f ).Normalized() * p_radius ); // 10
    vertList.push_back( Vector3f( -t, 0.0f,  1.0f ).Normalized() * p_radius ); // 11
    
    vertList.push_back( Vector3f(  1.0f,  t, 0.0f ).Normalized() *p_radius ); // 1
    vertList.push_back( Vector3f( 0.0f,  1.0f,  t ).Normalized() *p_radius ); // 5
    vertList.push_back( Vector3f(  t, 0.0f,  1.0f ).Normalized() *p_radius ); // 9
    
    vertList.push_back( Vector3f( 0.0f,  1.0f,  t ).Normalized() *p_radius ); // 5
    vertList.push_back( Vector3f( -t, 0.0f,  1.0f ).Normalized() *p_radius ); // 11
    vertList.push_back( Vector3f( 0.0f, -1.0f,  t ).Normalized() *p_radius ); // 4
    
    vertList.push_back( Vector3f( -t, 0.0f,  1.0f ).Normalized() *p_radius ); // 11
    vertList.push_back( Vector3f( -t, 0.0f, -1.0f ).Normalized() *p_radius ); // 10
    vertList.push_back( Vector3f( -1.0f, -t, 0.0f ).Normalized() *p_radius ); // 2
    
    vertList.push_back( Vector3f( -t, 0.0f, -1.0f ).Normalized() *p_radius ); // 10
    vertList.push_back( Vector3f( 0.0f,  1.0f, -t ).Normalized() *p_radius ); // 7
    vertList.push_back( Vector3f( 0.0f, -1.0f, -t ).Normalized() *p_radius ); // 6
    
    vertList.push_back( Vector3f( 0.0f,  1.0f, -t ).Normalized() *p_radius ); // 7
    vertList.push_back( Vector3f(  1.0f,  t, 0.0f ).Normalized() *p_radius ); // 1
    vertList.push_back( Vector3f(  t, 0.0f, -1.0f ).Normalized() *p_radius ); // 8
    
    vertList.push_back( Vector3f(  1.0f, -t, 0.0f ).Normalized() *p_radius ); // 3
    vertList.push_back( Vector3f(  t, 0.0f,  1.0f ).Normalized() *p_radius ); // 9
    vertList.push_back( Vector3f( 0.0f, -1.0f,  t ).Normalized() *p_radius ); // 4
    
    vertList.push_back( Vector3f(  1.0f, -t, 0.0f ).Normalized() *p_radius ); // 3
    vertList.push_back( Vector3f( 0.0f, -1.0f,  t ).Normalized() *p_radius ); // 4
    vertList.push_back( Vector3f( -1.0f, -t, 0.0f ).Normalized() *p_radius ); // 2
    
    vertList.push_back( Vector3f(  1.0f, -t, 0.0f ).Normalized() *p_radius ); // 3
    vertList.push_back( Vector3f( -1.0f, -t, 0.0f ).Normalized() *p_radius ); // 2
    vertList.push_back( Vector3f( 0.0f, -1.0f, -t ).Normalized() *p_radius ); // 6
    
    vertList.push_back( Vector3f(  1.0f, -t, 0.0f ).Normalized() *p_radius ); // 3
    vertList.push_back( Vector3f( 0.0f, -1.0f, -t ).Normalized() *p_radius ); // 6
    vertList.push_back( Vector3f(  t, 0.0f, -1.0f ).Normalized() *p_radius ); // 8
    
    vertList.push_back( Vector3f(  1.0f, -t, 0.0f ).Normalized() *p_radius ); // 3
    vertList.push_back( Vector3f(  t, 0.0f, -1.0f ).Normalized() *p_radius ); // 8
    vertList.push_back( Vector3f(  t, 0.0f,  1.0f ).Normalized() *p_radius ); // 9
    
    vertList.push_back( Vector3f( 0.0f, -1.0f,  t ).Normalized() *p_radius ); // 4
    vertList.push_back( Vector3f(  t, 0.0f,  1.0f ).Normalized() *p_radius ); // 9
    vertList.push_back( Vector3f( 0.0f,  1.0f,  t ).Normalized() *p_radius ); // 5
    
    vertList.push_back( Vector3f( -1.0f, -t, 0.0f ).Normalized() *p_radius ); // 2
    vertList.push_back( Vector3f( 0.0f, -1.0f,  t ).Normalized() *p_radius ); // 4
    vertList.push_back( Vector3f( -t, 0.0f,  1.0f ).Normalized() *p_radius ); // 11
    
    vertList.push_back( Vector3f( 0.0f, -1.0f, -t ).Normalized() *p_radius ); // 6
    vertList.push_back( Vector3f( -1.0f, -t, 0.0f ).Normalized() *p_radius ); // 2
    vertList.push_back( Vector3f( -t, 0.0f, -1.0f ).Normalized() *p_radius ); // 10
    
    vertList.push_back( Vector3f(  t, 0.0f, -1.0f ).Normalized() *p_radius ); // 8
    vertList.push_back( Vector3f( 0.0f, -1.0f, -t ).Normalized() *p_radius ); // 6
    vertList.push_back( Vector3f( 0.0f,  1.0f, -t ).Normalized() *p_radius ); // 7
    
    vertList.push_back( Vector3f(  t, 0.0f,  1.0f ).Normalized() *p_radius ); // 9
    vertList.push_back( Vector3f(  t, 0.0f, -1.0f ).Normalized() *p_radius ); // 8
    vertList.push_back( Vector3f(  1.0f,  t, 0.0f ).Normalized() *p_radius ); // 1
    
    tris.push_back( new Tri( 1, Vector3i( 0, 1, 2 ), vertList[ 0 ], vertList[ 1 ], vertList[ 2 ] ) );
    tris.push_back( new Tri( 2, Vector3i( 3, 4, 5 ), vertList[ 3 ], vertList[ 4 ], vertList[ 5 ], tris[ 0 ] ) );
    tris.push_back( new Tri( 3, Vector3i( 6, 7, 8 ), vertList[ 6 ], vertList[ 7 ], vertList[ 8 ], tris[ 1 ] ) );
    tris.push_back( new Tri( 4, Vector3i( 9, 10, 11 ), vertList[ 9 ], vertList[ 10 ], vertList[ 11 ], tris[ 2 ] ) );
    tris.push_back( new Tri( 5, Vector3i( 12, 13, 14 ), vertList[ 12 ], vertList[ 13 ], vertList[ 14 ], tris[ 0 ], tris[ 3 ] ) );
    
    tris.push_back( new Tri( 6, Vector3i( 15, 16, 17 ), vertList[ 15 ], vertList[ 16 ], vertList[ 17 ], tris[ 1 ] ) );
    tris.push_back( new Tri( 7, Vector3i( 18, 19, 20 ), vertList[ 18 ], vertList[ 19 ], vertList[ 20 ], tris[ 0 ] ) );
    tris.push_back( new Tri( 8, Vector3i( 21, 22, 23 ), vertList[ 21 ], vertList[ 22 ], vertList[ 23 ], tris[ 4 ] ) );
    tris.push_back( new Tri( 9, Vector3i( 24, 25, 26 ), vertList[ 24 ], vertList[ 25 ], vertList[ 26 ], tris[ 3 ] ) );
    tris.push_back( new Tri( 10, Vector3i( 27, 28, 29 ), vertList[ 27 ], vertList[ 28 ], vertList[ 29 ], tris[ 2 ] ) );
    
    tris.push_back( new Tri( 11, Vector3i( 30, 31, 32 ), vertList[ 30 ], vertList[ 31 ], vertList[ 32 ] ) );
    tris.push_back( new Tri( 12, Vector3i( 33, 34, 35 ), vertList[ 33 ], vertList[ 34 ], vertList[ 35 ], tris[ 10 ] ) );
    tris.push_back( new Tri( 13, Vector3i( 36, 37, 38 ), vertList[ 36 ], vertList[ 37 ], vertList[ 38 ], tris[ 11 ] ) );
    tris.push_back( new Tri( 14, Vector3i( 39, 40, 41 ), vertList[ 39 ], vertList[ 40 ], vertList[ 41 ], tris[ 12 ] ) );
    tris.push_back( new Tri( 15, Vector3i( 42, 43, 44 ), vertList[ 42 ], vertList[ 43 ], vertList[ 44 ], tris[ 10 ], tris[ 13 ] ) );
    
    tris.push_back( new Tri( 16, Vector3i( 45, 46, 47 ), vertList[ 45 ], vertList[ 46 ], vertList[ 47 ], tris[ 5 ], tris[ 6 ], tris[ 10 ] ) );
    tris.push_back( new Tri( 17, Vector3i( 48, 49, 50 ), vertList[ 48 ], vertList[ 49 ], vertList[ 50 ], tris[ 6 ], tris[ 7 ], tris[ 11 ] ) );
    tris.push_back( new Tri( 18, Vector3i( 51, 52, 53 ), vertList[ 51 ], vertList[ 52 ], vertList[ 53 ], tris[ 7 ], tris[ 8 ], tris[ 12 ] ) );
    tris.push_back( new Tri( 19, Vector3i( 54, 55, 56 ), vertList[ 54 ], vertList[ 55 ], vertList[ 56 ], tris[ 8 ], tris[ 9 ], tris[ 13 ] ) );
    tris.push_back( new Tri( 20, Vector3i( 57, 58, 59 ), vertList[ 57 ], vertList[ 58 ], vertList[ 59 ], tris[ 5 ], tris[ 9 ], tris[ 14 ] ) );
    
    tris[ 0 ]->m_a = tris[ 1 ];
    tris[ 0 ]->m_b = tris[ 4 ];
    tris[ 0 ]->m_c = tris[ 6 ];
    tris[ 1 ]->m_b = tris[ 2 ];
    tris[ 1 ]->m_c = tris[ 5 ];
    tris[ 2 ]->m_b = tris[ 3 ];
    tris[ 2 ]->m_c = tris[ 9 ];
    tris[ 3 ]->m_b = tris[ 4 ];
    tris[ 3 ]->m_c = tris[ 8 ];
    tris[ 4 ]->m_c = tris[ 7 ];
    
    tris[ 5 ]->m_b = tris[ 15 ];
    tris[ 5 ]->m_c = tris[ 19 ];
    tris[ 6 ]->m_b = tris[ 15 ];
    tris[ 6 ]->m_c = tris[ 16 ];
    tris[ 7 ]->m_b = tris[ 16 ];
    tris[ 7 ]->m_c = tris[ 17 ];
    tris[ 8 ]->m_b = tris[ 17 ];
    tris[ 8 ]->m_c = tris[ 18 ];
    tris[ 9 ]->m_b = tris[ 18 ];
    tris[ 9 ]->m_c = tris[ 19 ];
    
    tris[ 10 ]->m_a = tris[ 11 ];
    tris[ 10 ]->m_b = tris[ 14 ];
    tris[ 10 ]->m_c = tris[ 15 ];
    tris[ 11 ]->m_b = tris[ 12 ];
    tris[ 11 ]->m_c = tris[ 16 ];
    tris[ 12 ]->m_b = tris[ 13 ];
    tris[ 12 ]->m_c = tris[ 17 ];
    tris[ 13 ]->m_b = tris[ 14 ];
    tris[ 13 ]->m_c = tris[ 18 ];
    tris[ 14 ]->m_c = tris[ 19 ];
    
    p_vertices = vertList;
    p_tris = tris;
}

void Planet::SubdivideIcosahedron( float p_radius, unsigned int p_recursions, std::vector<Vector3f> &p_vertices, std::vector<Tri *> &p_tris ) {
    std::vector<Tri*> myOldTris;
    
    for ( int i = 0; i < p_recursions; i++ ) {
        std::vector<Tri*> tris2;
        std::vector<Vector3f> vertList2;
        int index = 1;
        for ( unsigned int i = 0; i < p_tris.size(); i++ ) {
            Tri *face = p_tris[ i ];
            unsigned int nextFace = ( unsigned int ) vertList2.size();
            
            Vector3f x = p_vertices[ face->GetX() ];
            Vector3f y = p_vertices[ face->GetY() ];
            Vector3f z = p_vertices[ face->GetZ() ];
            Vector3f p1 = x.Midpoint( y );
            Vector3f p2 = y.Midpoint( z );
            Vector3f p3 = z.Midpoint( x );
            
            vertList2.push_back( x.Normalized() *p_radius );
            vertList2.push_back( p1.Normalized() *p_radius );
            vertList2.push_back( p3.Normalized() *p_radius );
            
            vertList2.push_back( p1.Normalized() *p_radius );
            vertList2.push_back( y.Normalized() *p_radius );
            vertList2.push_back( p2.Normalized() *p_radius );
            
            vertList2.push_back( p3.Normalized() *p_radius );
            vertList2.push_back( p2.Normalized() *p_radius );
            vertList2.push_back( z.Normalized() *p_radius );
            
            vertList2.push_back( p2.Normalized() *p_radius );
            vertList2.push_back( p3.Normalized() *p_radius );
            vertList2.push_back( p1.Normalized() *p_radius );
            
            Tri *t0 = new Tri( index++, Vector3i( nextFace + 0, nextFace + 1,  nextFace + 2 ), vertList2[ nextFace + 0 ], vertList2[ nextFace + 1 ], vertList2[ nextFace + 2 ] );
            Tri *t1 = new Tri( index++, Vector3i( nextFace + 3, nextFace + 4,  nextFace + 5 ), vertList2[ nextFace + 3 ], vertList2[ nextFace + 4 ], vertList2[ nextFace + 5 ] );
            Tri *t2 = new Tri( index++, Vector3i( nextFace + 6, nextFace + 7,  nextFace + 8 ), vertList2[ nextFace + 6 ], vertList2[ nextFace + 7 ], vertList2[ nextFace + 8 ] );
            Tri *t3 = new Tri( index++, Vector3i( nextFace + 9, nextFace + 10, nextFace + 11 ), vertList2[ nextFace + 9 ], vertList2[ nextFace + 10 ], vertList2[ nextFace + 11 ], t0, t1, t2 );
            
            t0->m_parent = face;
            t1->m_parent = face;
            t2->m_parent = face;
            t3->m_parent = face;
            face->m_child = t3;
            
            t0->m_b = t3;
            t1->m_c = t3;
            t2->m_a = t3;
            
            tris2.push_back( t0 );
            tris2.push_back( t1 );
            tris2.push_back( t2 );
            tris2.push_back( t3 );
        }
        
        for ( unsigned int i = 0; i < tris2.size(); i++ ) {
            Tri *face = tris2[ i ];
            Tri *parent = tris2[ i ]->m_parent;
            
            Tri *a = parent->m_a->m_child;
            Tri *b = parent->m_b->m_child;
            Tri *c = parent->m_c->m_child;
            
            // Check A
            if ( face->IsXYAdjacent( a->m_a ) ) { face->m_a = a->m_a; }
            if ( face->IsXYAdjacent( a->m_b ) ) { face->m_a = a->m_b; }
            if ( face->IsXYAdjacent( a->m_c ) ) { face->m_a = a->m_c; }
            if ( face->IsYZAdjacent( a->m_a ) ) { face->m_b = a->m_a; }
            if ( face->IsYZAdjacent( a->m_b ) ) { face->m_b = a->m_b; }
            if ( face->IsYZAdjacent( a->m_c ) ) { face->m_b = a->m_c; }
            if ( face->IsZXAdjacent( a->m_a ) ) { face->m_c = a->m_a; }
            if ( face->IsZXAdjacent( a->m_b ) ) { face->m_c = a->m_b; }
            if ( face->IsZXAdjacent( a->m_c ) ) { face->m_c = a->m_c; }
            // Done A
            
            // Check B
            if ( face->IsXYAdjacent( b->m_a ) ) { face->m_a = b->m_a; }
            if ( face->IsXYAdjacent( b->m_b ) ) { face->m_a = b->m_b; }
            if ( face->IsXYAdjacent( b->m_c ) ) { face->m_a = b->m_c; }
            if ( face->IsYZAdjacent( b->m_a ) ) { face->m_b = b->m_a; }
            if ( face->IsYZAdjacent( b->m_b ) ) { face->m_b = b->m_b; }
            if ( face->IsYZAdjacent( b->m_c ) ) { face->m_b = b->m_c; }
            if ( face->IsZXAdjacent( b->m_a ) ) { face->m_c = b->m_a; }
            if ( face->IsZXAdjacent( b->m_b ) ) { face->m_c = b->m_b; }
            if ( face->IsZXAdjacent( b->m_c ) ) { face->m_c = b->m_c; }
            // Done B
            
            // Check C
            if ( face->IsXYAdjacent( c->m_a ) ) { face->m_a = c->m_a; }
            if ( face->IsXYAdjacent( c->m_b ) ) { face->m_a = c->m_b; }
            if ( face->IsXYAdjacent( c->m_c ) ) { face->m_a = c->m_c; }
            if ( face->IsYZAdjacent( c->m_a ) ) { face->m_b = c->m_a; }
            if ( face->IsYZAdjacent( c->m_b ) ) { face->m_b = c->m_b; }
            if ( face->IsYZAdjacent( c->m_c ) ) { face->m_b = c->m_c; }
            if ( face->IsZXAdjacent( c->m_a ) ) { face->m_c = c->m_a; }
            if ( face->IsZXAdjacent( c->m_b ) ) { face->m_c = c->m_b; }
            if ( face->IsZXAdjacent( c->m_c ) ) { face->m_c = c->m_c; }
            // Done C
            
            if ( i % 4 == 0 ) {
                myOldTris.push_back( face->m_parent );
            }
        }
        
        p_tris = tris2;
        p_vertices = vertList2;
    }
    
    for ( unsigned int i = 0; i < myOldTris.size(); i++ ) {
        if ( myOldTris[ i ] != 0 ) {
            delete myOldTris[ i ];
        }
    }
}

void Planet::CreateHexagons( const std::vector<Tri *> &p_tris, std::vector<Hex *> &p_hexes, std::vector<unsigned int> &p_indices, std::vector<Vector3f> &p_vertices, std::vector<Vector3f> &p_normals ) {
    for ( unsigned int i = 0; i < p_tris.size(); i++ ) {
        std::vector<Tri*> hex = BFS( p_tris[ i ]->m_a, p_tris[ i ]->m_b, p_tris[ i ] );
        hex.push_back( p_tris[ i ] );
        p_hexes.push_back( new Hex( hex ) );
        
        hex = BFS( p_tris[ i ]->m_b, p_tris[ i ]->m_c, p_tris[ i ] );
        hex.push_back( p_tris[ i ] );
        p_hexes.push_back( new Hex( hex ) );
        
        hex = BFS( p_tris[ i ]->m_c, p_tris[ i ]->m_a, p_tris[ i ] );
        hex.push_back( p_tris[ i ] );
        p_hexes.push_back( new Hex( hex ) );
    }
    
    std::sort( p_hexes.begin(), p_hexes.end(), HexLess );
    p_hexes.erase( std::unique( p_hexes.begin(), p_hexes.end(), HexEquals ), p_hexes.end() );
    
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        for ( unsigned int j = 0; j < p_hexes[ i ]->m_tris.size(); j++ ) {
            p_hexes[ i ]->m_tris[ j ]->m_hexes.push_back( p_hexes [ i ] );
        }
    }
    
    std::vector<unsigned int> indices;
    std::vector<Vector3f> vertList;
    std::vector<Vector3f> normals;
    
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        for ( unsigned int j = 0; j < p_hexes[ i ]->m_tris.size(); j++ ) {
            std::vector<Hex*> hexes = p_hexes[ i ]->m_tris[ j ]->m_hexes;
            p_hexes[ i ]->m_neighbors.insert( p_hexes[ i ]->m_neighbors.begin(), hexes.begin(), hexes.end() );
        }
        
        p_hexes[ i ]->m_neighbors.erase( std::remove( p_hexes[ i ]->m_neighbors.begin(), p_hexes[ i ]->m_neighbors.end(), p_hexes[ i ] ), p_hexes[ i ]->m_neighbors.end() );
        std::sort( p_hexes[ i ]->m_neighbors.begin(), p_hexes[ i ]->m_neighbors.end(), HexLess );
        p_hexes[ i ]->m_neighbors.erase( std::unique( p_hexes[ i ]->m_neighbors.begin(), p_hexes[ i ]->m_neighbors.end(), HexEquals ), p_hexes[ i ]->m_neighbors.end() );
        
        unsigned int nextFace = ( unsigned int ) vertList.size();
        if ( p_hexes[ i ]->m_pentagon ) {
            Vector3f c0 = p_hexes[ i ]->m_tris[ 0 ]->Centroid();
            Vector3f c1 = p_hexes[ i ]->m_tris[ 1 ]->Centroid();
            Vector3f c2 = p_hexes[ i ]->m_tris[ 2 ]->Centroid();
            Vector3f c3 = p_hexes[ i ]->m_tris[ 3 ]->Centroid();
            Vector3f c4 = p_hexes[ i ]->m_tris[ 4 ]->Centroid();
            
            vertList.push_back( c0 );
            vertList.push_back( c4 );
            vertList.push_back( c3 );
            
            vertList.push_back( c0 );
            vertList.push_back( c3 );
            vertList.push_back( c1 );
            
            vertList.push_back( c1 );
            vertList.push_back( c3 );
            vertList.push_back( c2 );
            
            indices.push_back( nextFace + 0 );
            indices.push_back( nextFace + 1 );
            indices.push_back( nextFace + 2 );
            
            indices.push_back( nextFace + 3 );
            indices.push_back( nextFace + 4 );
            indices.push_back( nextFace + 5 );
            
            indices.push_back( nextFace + 6 );
            indices.push_back( nextFace + 7 );
            indices.push_back( nextFace + 8 );
        } else {
            Vector3f c0 = p_hexes[ i ]->m_tris[ 0 ]->Centroid();
            Vector3f c1 = p_hexes[ i ]->m_tris[ 1 ]->Centroid();
            Vector3f c2 = p_hexes[ i ]->m_tris[ 2 ]->Centroid();
            Vector3f c3 = p_hexes[ i ]->m_tris[ 3 ]->Centroid();
            Vector3f c4 = p_hexes[ i ]->m_tris[ 4 ]->Centroid();
            Vector3f c5 = p_hexes[ i ]->m_tris[ 5 ]->Centroid();
            
            vertList.push_back( c0 );
            vertList.push_back( c5 );
            vertList.push_back( c1 );
            
            vertList.push_back( c1 );
            vertList.push_back( c5 );
            vertList.push_back( c4 );
            
            vertList.push_back( c1 );
            vertList.push_back( c4 );
            vertList.push_back( c2 );
            
            vertList.push_back( c2 );
            vertList.push_back( c4 );
            vertList.push_back( c3 );
            
            indices.push_back( nextFace + 0 );
            indices.push_back( nextFace + 1 );
            indices.push_back( nextFace + 2 );
            
            indices.push_back( nextFace + 3 );
            indices.push_back( nextFace + 4 );
            indices.push_back( nextFace + 5 );
            
            indices.push_back( nextFace + 6 );
            indices.push_back( nextFace + 7 );
            indices.push_back( nextFace + 8 );
            
            indices.push_back( nextFace + 9 );
            indices.push_back( nextFace + 10 );
            indices.push_back( nextFace + 11 );
        }
    }

    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        int verts = p_hexes[ i ]->m_pentagon ? 3 : 4;
        Vector3f normal = p_hexes[ i ]->m_center.Normalized();
        for ( unsigned int j = 0; j < verts; j++ ) {
            normals.push_back( normal );
            normals.push_back( normal );
            normals.push_back( normal );
        }
    }
    
    p_indices = indices;
    p_vertices = vertList;
    p_normals = normals;
}

void Planet::CreatePlates( unsigned int p_numPlates, const std::vector<Hex*> &p_hexes, std::vector<Plate *> &p_plates ) {
    std::vector<Hex*> unusedHexes( p_hexes );
    std::vector<Plate*> plates;
    
    std::vector<int> nums( unusedHexes.size() );
    std::iota( std::begin( nums ), std::end( nums ), 0 );
    
    for ( int i = 0; i < nums.size(); i++ ) {
        int r = i + m_random->InRange( 0, INT_MAX ) % ( nums.size() - i );
        int temp = nums[ i ];
        nums[ i ] = nums[ r ];
        nums[ r ] = temp;
    }
    
    std::vector<Hex*> startHexes;
    for ( unsigned int i = 0; i < p_numPlates; i++ ) {
        startHexes.push_back( unusedHexes[ nums[ i ] ] );
        
        Plate *plate = new Plate();
        if ( m_random->InRange( 0.0f, 1.0f ) < m_waterPercentage ) {
            plate->m_plateType = PlateType::PLATE_WATER;
        } else {
            plate->m_plateType = PlateType::PLATE_LAND;
        }
        
        // plate->m_rotationAxis = Vector3f(); // Random unit vector
        // plate->m_rotationAmount = 0.0f; // small random num
        // plate->m_driftDirection = Vector3f(); // Random unit vector
        // plate->m_driftAmount = 0.0f; // small random num
		plate->m_drift = Vector3f( m_random->InRange( 0.0f, 1.0f ), m_random->InRange( 0.0f, 1.0f ), m_random->InRange( 0.0f, 1.0f ) ).Normalized();
        plate->m_color = Vector3f( m_random->InRange( 0.2f, 1.0f ), m_random->InRange( 0.2f, 1.0f ), m_random->InRange( 0.2f, 1.0f ) );
        plate->m_hexes.push_back( unusedHexes[ nums[ i ] ] );
        plate->m_neighbors.insert( plate->m_neighbors.begin(), unusedHexes[ nums[ i ] ]->m_neighbors.begin(), unusedHexes[ nums[ i ] ]->m_neighbors.end() );
        
        plates.push_back( plate );
    }
    
    for ( unsigned int i = 0; i < startHexes.size(); i++ ) {
        unusedHexes.erase( std::remove( unusedHexes.begin(), unusedHexes.end(), startHexes[ i ] ), unusedHexes.end() );
    }
    
    do {
        for ( unsigned int i = 0; i < plates.size(); i++ ) {
            std::vector<Hex*> myNeighbors = plates[ i ]->m_neighbors;
            
            int myIndex = 0;
            do {
                if ( myNeighbors[ myIndex ]->m_plate == 0 ) {
                    myNeighbors[ myIndex ]->m_plate = plates[ i ];
                    plates[ i ]->Add( myNeighbors[ myIndex ] );
                    unusedHexes.erase( std::remove( unusedHexes.begin(), unusedHexes.end(), myNeighbors[ myIndex ] ), unusedHexes.end() );
                    break;
                }
                
                myIndex++;
                if ( myIndex > myNeighbors.size() - 1 ) {
                    p_plates.push_back( plates[ i ] );
                    plates.erase( plates.begin() + i );
                    break;
                }
            } while ( true );
        }
    } while ( !unusedHexes.empty() );
}

void Planet::CalculateStress( std::vector<Plate*> &p_plates ) {
	for ( unsigned int i = 0; i < p_plates.size(); i++ ) {
		Plate* plate = p_plates[ i ];
		for ( unsigned int j = 0; j < plate->m_hexes.size(); j++ ) {
			Hex* hex = plate->m_hexes[ j ];
			for ( unsigned int k = 0; k < hex->m_neighbors.size(); k++ ) {
				if ( hex->m_plate != hex->m_neighbors[ k ]->m_plate ) {
					Vector3f stressVector = ( hex->m_plate->m_drift - hex->m_neighbors[ k ]->m_plate->m_drift ).Normalized();
					hex->m_stress += stressVector;
				}
			}
		}
	}
}

void Planet::Colorize( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes ) {
    p_colors.clear();
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        p_hexes[ i ]->Colorize( p_colors );
    }
}

void Planet::ColorizeNeighbors( std::vector<Vector3f> &p_colors, int p_index, const std::vector<Hex*> &p_hexes ) {
    p_hexes[ p_index ]->m_color = Vector3f( 1.0f, 0.0f, 0.0f );
    for ( unsigned int i = 0; i < p_hexes[ p_index ]->m_neighbors.size(); i++ ) {
        p_hexes[ p_index ]->m_neighbors[ i ]->m_color = Vector3f( 0.0f, 1.0f, 0.0f );
    }
    
    Colorize( p_colors, p_hexes );
}

void Planet::ColorizeRandom( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes ) {
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        p_hexes[ i ]->m_color = Vector3f( m_random->InRange( 0.2f, 1.0f ), m_random->InRange( 0.2f, 1.0f ), m_random->InRange( 0.2f, 1.0f ) );
        p_hexes[ i ]->Colorize( p_colors );
    }
    
    Colorize( p_colors, p_hexes );
}

void Planet::ColorizePlates( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes ) {
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        p_hexes[ i ]->m_color = p_hexes[ i ]->m_plate->m_color;
    }
    
    Colorize( p_colors, p_hexes );
}

void Planet::ColorizePlateTypes( std::vector<Vector3f> &p_colors, const std::vector<Hex*> &p_hexes ) {
    for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
        if ( p_hexes[ i ]->m_plate->m_plateType == PlateType::PLATE_LAND ) {
            p_hexes[ i ]->m_color = Vector3f( 0.20784f, 0.46666f, 0.19215f );
        } else if ( p_hexes[ i ]->m_plate->m_plateType == PlateType::PLATE_WATER ) {
            p_hexes[ i ]->m_color = Vector3f( 0.40392f, 0.61960f, 0.9823f );
        }
    }
    
    Colorize( p_colors, p_hexes );
}

void Planet::ColorizeStressVector( std::vector<Vector3f> &p_colors, const std::vector<Hex *> &p_hexes ) {
	for ( unsigned int i = 0; i < p_hexes.size(); i++ ) {
		if ( p_hexes[ i ]->m_stress.GetX() != 0 && p_hexes[ i ]->m_stress.GetY() != 0 && p_hexes[ i ]->m_stress.GetZ() != 0 ) {
			float x = p_hexes[ i ]->m_stress.GetX();
			float y = p_hexes[ i ]->m_stress.GetY();
			float z = p_hexes[ i ]->m_stress.GetZ();
	
			p_hexes[ i ]->m_color = Vector3f( Math3D::Scale( ( x + y + z ), 0.4f, 1.0, -3, 3 ), 0, 0 );
		}
	}
	
	Colorize( p_colors, p_hexes );
}

std::vector<Tri*> Planet::BFS( Tri* p_start, Tri* p_end, Tri* p_exclude ) {
    std::map<Tri*, bool> visited;
    std::map<Tri*, Tri*> previous;
    std::queue<Tri*> q;
    
    Tri* current = p_start;
    q.push( current );
    visited.insert( std::pair<Tri*, bool>( current, true ) );
    while ( !q.empty() ) {
        current = q.front();
        q.pop();
        
        if ( current == p_end ) {
            break;
        } else {
            std::vector<Tri*> nbrs = current->Neighbors( p_exclude );
            for ( std::vector<Tri*>::iterator it = nbrs.begin(); it != nbrs.end(); it++ ) {
                if ( !( visited.count( *it ) == 1 ) ) {
                    q.push( *it );
                    visited.insert( std::pair<Tri*, bool>( *it, true ) );
                    previous.insert( std::pair<Tri*, Tri*>( *it, current ) );
                }
            }
        }
    }
    
    if ( current != p_end ) {
        // Super bad if this ever happens
        std::cout << "No path";
    }
    
    std::vector<Tri*> direction;
    for ( Tri* t = p_end; previous.count( t ) == 1; t = previous[ t ] ) {
        direction.push_back( t );
    }
    direction.push_back( p_start );
    
    return direction;
}
