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
#include <vector>

#include "camera.h"
#include "math3d.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

class RenderableEntity {
    
private:
    std::vector<RenderableEntity*> m_children;
    
    Mesh *m_mesh;
    Transform *m_transform;
    Texture *m_texture;
    
    bool m_visible;
    
protected:
    void Input() const;
    void Update() const;
    void Render( const Shader &shader, const Camera &camera ) const;
    
public:
    RenderableEntity();
    RenderableEntity( const std::string &meshFile, const std::string &textureFile );
    virtual ~RenderableEntity();
    
    void InputAll() const;
    void UpdateAll() const;
    void RenderAll( const Shader &shader, const Camera &camera ) const;
    
    Matrix4<float> GetModelMatrix() const;
    
    RenderableEntity* AddEntity( RenderableEntity *entity );
    
    inline void SetPosition( const Vector3<float> &position ) {
        m_transform->SetPosition( position );
    }
    
    inline void SetVisible( bool visible ) { m_visible = visible; }
    inline bool IsVisible() const { return m_visible; }
};

#endif /* entity_h */
