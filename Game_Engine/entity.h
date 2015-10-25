//
//  entity.h
//  Game_Engine
//
//  Created by Craig Milby on 10/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>

#include "math3d.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

class RenderableEntity {
    
private:
    Mesh *m_mesh;
    Transform *m_transform;
    Texture *m_texture;
    
public:
    RenderableEntity( const std::string &meshFile, const std::string &textureFile );
    virtual ~RenderableEntity();
    
    void Render( const Shader &shader ) const;
    Matrix4<float> GetModelMatrix() const;
    
    inline void SetPosition( const Vector3<float> &position ) {
        m_transform->SetPosition( position );
    }
};

#endif /* entity_h */
