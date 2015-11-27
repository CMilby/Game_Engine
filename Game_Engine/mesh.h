//
//  mesh.hpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __MESH_H__
#define __MESH_H__

#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "math3d.h"

struct Vertex {
    Vector3<float> m_position;
    Vector2<float> m_uv;
    Vector3<float> m_normal;

    inline bool operator<( const Vertex &vertex ) const {
        return memcmp( ( void* ) this, ( void* ) &vertex, sizeof( Vertex ) ) > 0;
    }
};

class Mesh {
    
private:
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    GLuint m_normalBuffer;
    GLuint m_elementBuffer;
    
    std::vector<unsigned short> m_indices;
    std::vector<Vector3<float>> m_vertices;
    std::vector<Vector2<float>> m_uvs;
    std::vector<Vector3<float>> m_normals;
    
    void LoadOBJ( const std::string &filename );

    void IndexVBO( std::vector<unsigned short> &outIndices, std::vector<Vector3<float>> &outVertices, std::vector<Vector2<float>> &outUVs, std::vector<Vector3<float>> &outNormals );
    bool GetSimilarVertexIndex( Vertex &vertex, std::map<Vertex, unsigned short> vertexToOut, unsigned short &result );
    
public:
    Mesh( const std::string &filename );
    virtual ~Mesh();
    
    void Render() const;
};

#endif /* mesh_h */
