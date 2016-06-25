//
//  terrainMesh.hpp
//  Game_Engine
//
//  Created by Craig Milby on 1/25/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TERRAIN_MESH_H__
#define __TERRAIN_MESH_H__

#include <vector>

#include <GL/glew.h>

#include "math3d.h"
#include "mesh.h"
#include "terrainLocation.h"

class TerrainMesh : public Mesh {
    
private:
	Vector3<float> CalculateHeight( const Vector3<float> &position, const Vector3<float> &normal );
	
	void HandleTopLeft( float scale, float &lastX, float &lastY, float &lastZ, float direction, float xOffset, float yOffset, float zOffset );
	void HandleTopRight( float scale, float &lastX, float &lastY, float &lastZ, float direction, float xOffset, float yOffset, float zOffset );
	void HandleBottomLeft( float scale, float &lastX, float &lastY, float &lastZ, float direction, float xOffset, float yOffset, float zOffset );
	void HandleBottomRight( float scale, float &lastX, float &lastY, float &lastZ, float direction, float xOffset, float yOffset, float zOffset );
    
public:
	TerrainMesh( const std::string &file, float radus, const Vector3<float> &pOffset, float scale, const TerrainLocation &location, float &lastX, float &lastY, float &lastZ, float direction );
    
    /*inline std::vector<Vector3<float>> GetVertices() const { return m_vertices; }
    inline std::vector<Vector2<float>> GetUVs() const { return m_uvs; }
    inline std::vector<Vector3<float>> GetNormals() const { return m_normals; }
    inline std::vector<unsigned short> GetIndices() const { return m_indices; }*/
};

#endif /* terrainMesh_hpp */
