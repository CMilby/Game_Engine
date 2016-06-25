//
//  testMesh.h
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TEST_MESH_H__
#define __TEST_MESH_H__

#include "mesh.h"

class TestMesh : public Mesh {
	
private:
	
public:
	TestMesh( const std::string &pFilename, float pRadius, const float pScale, const Vector3<float> &pOffset );
};

#endif /* testMesh_h */
