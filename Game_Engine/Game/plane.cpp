//
//  plane.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/5/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "plane.h"

#include "simplexNoise.h"

Plane::Plane( float p_xOffset, float p_yOffset, float p_zOffset ) {
	std::vector<unsigned short> indices;
	std::vector<Vector3<float>> vertices;
	std::vector<Vector2<float>> uvs;
	std::vector<Vector3<float>> normals;
	
	static SimplexNoise *noise = new SimplexNoise( 1234 );
	static float const kOctaves = 4;
	static float const kPersistence = 0.4f;
	static float const kScale = 0.005f;
	
	LoadOBJ( "plane_subdivide_test.obj", indices, vertices, uvs, normals );
	for ( unsigned int i = 0; i < vertices.size(); i++ ) {
		float xPos = Math3D::Scale( vertices[ i ].GetX(), 0.0f, 15.0f, -0.5f, 0.5f );
		float zPos = Math3D::Scale( vertices[ i ].GetZ(), 0.0f, 15.0f, -0.5f, 0.5f );
		
		float n = noise->ScaledOctaveNoise2D( kOctaves, kPersistence, kScale, 0.0f, 5.0f, xPos + ( p_xOffset * 15 ), zPos + ( p_zOffset * 15 ) );
		vertices[ i ] += Vector3<float>( 0.0f, n, 0.0f );
	}
	
	GenerateBuffers( indices, vertices, uvs, normals, false );
}

Plane::~Plane() {
	
}
