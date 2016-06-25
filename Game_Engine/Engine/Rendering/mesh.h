//
//  mesh.hpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
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
	
private:
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
	
	void InitMesh( const aiMesh *pMesh, std::vector<unsigned short> &pIndices, std::vector<Vector3<float>> &pVertices, std::vector<Vector2<float>> &pUVs, std::vector<Vector3<float>> &pNormals );
	
protected:
	virtual void GenerateBuffers( const std::vector<unsigned short> &pIndices, const std::vector<Vector3<float>> &pVertices, const std::vector<Vector2<float>> pUVs, const std::vector<Vector3<float>> pNormals, bool pInstance );
	
	void LoadOBJ( const std::string &filename, std::vector<unsigned short> &pIndices, std::vector<Vector3<float>> &pVertices, std::vector<Vector2<float>> &pUVs, std::vector<Vector3<float>> &pNormals );
	
public:
	Mesh();
	Mesh( const std::string &pFilename, bool pInstance = false );
	virtual ~Mesh();
	
	virtual void Render( int pInstances, const Matrix4<float>* pWVPMats, const Matrix4<float>* pWorldMats );
	virtual void Render();
};

#endif /* mesh_h */
