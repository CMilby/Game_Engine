//
//  mesh.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include <vector>

#include <GL/glew.h>

#include "math3d.h"

class aiMesh;

struct MeshEntry {
    
    unsigned int m_numIndices;
    unsigned int m_baseVertex;
    unsigned int m_baseIndex;
    unsigned int m_materialIndex;
    
    MeshEntry() {
        m_numIndices = 0;
        m_baseVertex = 0;
        m_baseIndex = 0;
        m_materialIndex = 0xFFFFFFFF;
    }
};

class Mesh {
    
protected:
    enum {
        VERTEX_BUFFER,
        TEX_COORD_BUFFER,
        NORMAL_BUFFER,
        INDEX_BUFFER,
        WVP_MAT_BUFFER,
        WORLD_MAT_BUFFER,
        NUM_BUFFERS
    };
    
    std::string m_filename;
    
    GLuint m_buffers[ NUM_BUFFERS ];
    GLuint m_vao;
    
    std::vector<MeshEntry> m_entries;
    
    void InitMesh( const aiMesh *p_mesh, std::vector<unsigned int> &p_indices, std::vector<Vector3f> &p_vertices, std::vector<Vector2f> &p_UVs, std::vector<Vector3f> &p_normals );
    
protected:
    virtual void GenerateBuffers( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> p_UVs, const std::vector<Vector3f> p_normals, bool p_instance );
    
    void LoadOBJ( const std::string &p_filename, std::vector<unsigned int> &p_indices, std::vector<Vector3f> &p_vertices, std::vector<Vector2f> &p_UVs, std::vector<Vector3f> &p_normals );
    
public:
    Mesh();
    Mesh( const std::string &p_filename, bool p_instance = false );
    Mesh( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> &p_uvs, const std::vector<Vector3f> &p_normals );
    virtual ~Mesh();
    
    virtual void Render( int p_instances, const Matrix4f* p_WVPMats, const Matrix4f* p_worldMats );
    virtual void Render();
	
	virtual void Update( const std::vector<Vector3f> &p_position ) {}
	virtual void Update( const std::vector<Vector2f> &p_position ) {}
	virtual void Update( const std::vector<unsigned int> &p_position ) {}
	
    Mesh& operator=( const Mesh &p_mesh );
};

#endif /* mesh_h */
