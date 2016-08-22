//
//  renderableComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERABLE_COMPONENT_H__
#define __RENDERABLE_COMPONENT_H__

#include "component.h"

#include "material.h"
#include "mesh.h"
#include "shaderType.h"

class RenderableComponent : public Component {
	
private:
	Material *m_material;
	Mesh *m_mesh;
	
	ShaderType m_shaderType;
	bool m_isVisible;
	
public:
	RenderableComponent();
	RenderableComponent( Mesh *pMesh );
	RenderableComponent( const std::string &pMesh, const std::string &pTexture );
	virtual ~RenderableComponent();
	
	virtual void Render();
	
	inline void SetMaterial( Material *pMaterial ) { m_material = pMaterial; }
	inline void SetMesh( Mesh *pMesh ) { m_mesh = pMesh; }
	inline void SetShaderType( ShaderType pType ) { m_shaderType = pType; }
	inline void SetIsVisible( bool pVisible ) { m_isVisible = pVisible; }
};

#endif /* renderableComponent_h */
