//
//  colorized_mesh.hpp
//  Game_Engine_New
//
//  Created by Craig Milby on 11/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COLORIZED_MESH_H__
#define __COLORIZED_MESH_H__

#include "mesh.h"

class ColorizedMesh : public Mesh {
    
private:
    GLuint m_colorBuffer;
    
    std::vector<Vector3f> m_colors;
    
protected:
    virtual void GenerateBuffers( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> p_UVs, const std::vector<Vector3f> p_normals, bool p_instance );
    
public:
    ColorizedMesh( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector3f> &p_normals, const std::vector<Vector3f> &p_colors );
    virtual ~ColorizedMesh();
	
	virtual void Update( const std::vector<Vector3f> &p_position );
	
    virtual void Render();
};

#endif /* colorized_mesh_hpp */
