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

#include "material.h"
#include "math3d.h"
#include "mesh.h"
#include "transform.h"

class Camera;
class Shader;

class Entity {
    
private:
    std::vector<Entity*> m_children;
    
    Transform *m_transform;

public:
    Entity();
    virtual ~Entity();
    
    void InitAll();
    
    virtual void InputAll( float delta );
    virtual void UpdateAll( float delta );
    virtual void RenderAll( const std::vector<Shader*> &shaders, const Camera &camera );
    
    virtual void Init() {}
    
    virtual void Input( float delta ) {}
    virtual void Update( float delta ) {}
    virtual void Render( const std::vector<Shader*> &shaders, const Camera &camera ) {}
    
    Entity* AddChild( Entity *entity );
    void ClearChildren();
    
    inline Transform* GetTransform() const { return m_transform; }
    inline void SetTransform( Transform *transform ) { m_transform = transform; }
};

class RenderableEntity : public Entity {
    
private:
    Mesh *m_mesh;
    Material *m_material;
    
    bool m_visible;
    
public:
    RenderableEntity();
    RenderableEntity( Mesh *mesh, Material *material = new Material() );
    virtual ~RenderableEntity();
    
    virtual void Init() {}
    
    virtual void Input( float delta );
    virtual void Update( float delta );
    virtual void Render( const std::vector<Shader*> &shaders, const Camera &camera );
    
    Matrix4<float> GetModelMatrix() const;
    
    inline void SetPosition( const Vector3<float> &position ) { GetTransform()->SetPosition( position ); }
    inline void SetScale( const Vector3<float> &scale ) { GetTransform()->SetScale( scale ); }
    inline void SetRotation( const Quaternion &rotation ) { GetTransform()->SetRotation( rotation ); }
    
    inline void SetVisible( bool visible ) { m_visible = visible; }
    inline bool IsVisible() const { return m_visible; }
    
    inline Mesh GetMesh() const { return *m_mesh; }
    inline Material GetMaterial() const { return *m_material; }
    
    inline void SetMesh( Mesh *mesh ) { m_mesh = mesh; }
    inline void SetMaterial( Material *material ) { m_material = material; }
};

#endif /* entity_h */
