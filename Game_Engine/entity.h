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

#include "math3d.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

class Camera;

class Entity {
    
private:
    std::vector<Entity*> m_children;
    
protected:
    virtual void Input( float delta ) const {}
    virtual void Update( float delta ) const {}
    virtual void Render( const Shader &shader, const Camera &camera ) const {}

public:
    Entity();
    virtual ~Entity();
    
    void InputAll( float delta ) const;
    void UpdateAll( float delta ) const;
    void RenderAll( const Shader &shader, const Camera &camera ) const;
    
    Entity* AddChild( Entity *entity );
};

class RenderableEntity : public Entity {
    
private:
    Mesh *m_mesh;
    Transform *m_transform;
    Texture *m_texture;
    
    bool m_visible;
    
protected:
    virtual void Input( float delta ) const;
    virtual void Update( float delta ) const;
    virtual void Render( const Shader &shader, const Camera &camera ) const;
    
public:
    RenderableEntity();
    RenderableEntity( const std::string &meshFile, const std::string &textureFile );
    virtual ~RenderableEntity();
    
    Matrix4<float> GetModelMatrix() const;
    
    inline void SetPosition( const Vector3<float> &position ) { m_transform->SetPosition( position ); }
    
    inline void SetVisible( bool visible ) { m_visible = visible; }
    inline bool IsVisible() const { return m_visible; }
};

#endif /* entity_h */
