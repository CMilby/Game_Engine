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
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 m_position;
    glm::vec2 m_uv;
    glm::vec3 m_normal;

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
    
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_uvs;
    std::vector<glm::vec3> m_normals;
    std::vector<unsigned short> m_indices;
    
    void LoadOBJ( const std::string &filename );
    void IndexVBO( std::vector<unsigned short> &outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals );
    bool GetSimilarVertexIndex( Vertex &vertex, std::map<Vertex, unsigned short> vertexToOut, unsigned short &result );
public:
    Mesh( const std::string &filename );
    virtual ~Mesh();
    
    void Render() const;
};

#endif /* mesh_h */
