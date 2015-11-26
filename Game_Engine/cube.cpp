//
//  cube.cpp
//  Game_Engine
//
//  Created by Craig Milby on 11/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "cube.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "math3d.h"
#include "utility.h"

Cube::Cube( unsigned int segments, int size ) {
    GenerateCube( 1, 1, 1 );
}

void Cube::GenerateCube( float width, float height, float depth ) {
    std::vector<Vector3<float>> vertices;
    vertices.push_back( Vector3<float>( width, -height, -depth ) );
    vertices.push_back( Vector3<float>( width, -height, depth ) );
    vertices.push_back( Vector3<float>( -width, -height, depth ) );
    vertices.push_back( Vector3<float>( -width, -height, -depth ) );
    vertices.push_back( Vector3<float>( width, height, -depth ) );
    vertices.push_back( Vector3<float>( width, -height, depth ) );
    vertices.push_back( Vector3<float>( -width, height, depth ) );
    vertices.push_back( Vector3<float>( -width, height, -depth ) );
    
    std::vector<Vector2<float>> uvs;
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    uvs.push_back( Vector2<float>( 0, 0 ) );
    
    std::vector<Vector3<float>> normals;
    normals.push_back( Vector3<float>( 0, 0, -1 ) );
    normals.push_back( Vector3<float>( -1, 0, 0 ) );
    normals.push_back( Vector3<float>( 0, 0, 1 ) );
    normals.push_back( Vector3<float>( 0, 0, 1 ) );
    normals.push_back( Vector3<float>( 1, 0, 0 ) );
    normals.push_back( Vector3<float>( 1, 0, 0 ) );
    normals.push_back( Vector3<float>( 0, 1, 0 ) );
    normals.push_back( Vector3<float>( 0, -1, 0 ) );
}

