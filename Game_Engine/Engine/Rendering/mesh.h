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

class Mesh {
    
private:
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    GLuint m_normalBuffer;
    GLuint m_elementBuffer;
	
protected:
    std::vector<unsigned short> m_indices;
    std::vector<Vector3<float>> m_vertices;
    std::vector<Vector2<float>> m_uvs;
    std::vector<Vector3<float>> m_normals;
    
    void LoadOBJ( const std::string &filename );
    
public:
    Mesh();
    Mesh( const std::string &filename );
    virtual ~Mesh();
    
    virtual void Render() const;
    
    void GenerateBuffers();
};

#endif /* mesh_h */
