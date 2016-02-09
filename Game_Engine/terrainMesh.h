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
    std::vector<float> m_texture;
    
    Vector3<float> CalculateHeight( const Vector3<float> &position, const Vector3<float> &normal );
    std::vector<float> Texturize();
    
public:
    TerrainMesh( const std::string &file, float radus, float xOffset, float yOffset, float zOffset, float scale, bool generateBuffers, const std::string &position, float &lastX, float &lastY, float &lastZ, float direction );
    virtual ~TerrainMesh();
    
    virtual void Render() const;
    
    inline std::vector<float> GetTextureData() const { return m_texture; }
    
    inline std::vector<Vector3<float>> GetVertices() const { return m_vertices; }
    inline std::vector<Vector2<float>> GetUVs() const { return m_uvs; }
    inline std::vector<Vector3<float>> GetNormals() const { return m_normals; }
    inline std::vector<unsigned short> GetIndices() const { return m_indices; }
};

#endif /* terrainMesh_hpp */
