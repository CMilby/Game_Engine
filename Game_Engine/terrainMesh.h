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

class TerrainMesh : public Mesh {
    
private:
    GLuint m_colorBuffer;
    std::vector<Vector3<float>> m_colors;
    
public:
    TerrainMesh( const std::string &file, float radus, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers );
    virtual ~TerrainMesh();
    
    virtual void Render() const;
    
    inline std::vector<Vector3<float>> GetVertices() const { return m_vertices; }
    inline std::vector<Vector2<float>> GetUVs() const { return m_uvs; }
    inline std::vector<Vector3<float>> GetNormals() const { return m_normals; }
    inline std::vector<unsigned short> GetIndices() const { return m_indices; }
};

#endif /* terrainMesh_hpp */
