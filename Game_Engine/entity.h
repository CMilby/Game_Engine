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
    virtual void Init() {}
    
    virtual void Input( float delta ) {}
    virtual void Update( float delta ) {}
    virtual void Render( const Shader &shader, const Camera &camera ) {}

public:
    Entity();
    virtual ~Entity();
    
    void InitAll();
    
    void InputAll( float delta );
    void UpdateAll( float delta );
    void RenderAll( const Shader &shader, const Camera &camera );
    
    Entity* AddChild( Entity *entity );
};

class RenderableEntity : public Entity {
    
private:
    Mesh *m_mesh;
    Transform *m_transform;
    Texture *m_texture;
    
    bool m_visible;
    
protected:
    virtual void Input( float delta );
    virtual void Update( float delta );
    virtual void Render( const Shader &shader, const Camera &camera );
    
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
