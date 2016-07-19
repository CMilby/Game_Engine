//
//  renderableEntity.hpp
//  Game_Engine
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERABLE_ENTITY_H__
#define __RENDERABLE_ENTITY_H__

#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "shaderType.h"

class RenderableEntity : public Entity {
	
private:
	Mesh *m_mesh;
	Material *m_material;
	
	ShaderType m_shaderType;
	bool m_isVisible;
	
protected:
	virtual void Render();
	
public:
	RenderableEntity( EntityType pType );
	RenderableEntity( Mesh *mesh, Material *material = new Material() );
	RenderableEntity( const std::string &mesh, const std::string &texture = "test.png" );
	virtual ~RenderableEntity();
	
	inline void SetMaterial( Material *pMaterial ) { m_material = pMaterial; }
	inline void SetMesh( Mesh *pMesh ) { m_mesh = pMesh; }
	
	inline Material* GetMaterial() const { return m_material; }
	
	inline void SetShaderType( const ShaderType &type ) { m_shaderType = type; }
	inline ShaderType GetShaderType() const { return m_shaderType; }
	
	inline void SetIsVisible( bool isVisible ) { m_isVisible = isVisible; }
	inline bool IsVisible() const { return m_isVisible; }
};

#endif /* renderableEntity_hpp */
