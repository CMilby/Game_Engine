//
//  plane.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/5/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "plane.h"

Plane::Plane( float p_xOffset, float p_yOffset, float p_zOffset ) {
	std::vector<unsigned short> indices;
	std::vector<Vector3<float>> vertices;
	std::vector<Vector2<float>> uvs;
	std::vector<Vector3<float>> normals;
	
	LoadOBJ( "plane_subdivide_small.obj", indices, vertices, uvs, normals );
	/*for ( unsigned int i = 0; i < vertices.size(); i++ ) {
		vertices[ i ] += Vector3<float>( p_xOffset, p_yOffset, p_zOffset );
	}*/
	
	GenerateBuffers( indices, vertices, uvs, normals, false );
}

Plane::~Plane() {
	
}
