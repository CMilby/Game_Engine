//
//  renderableComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERABLE_COMPONENT_H__
#define __RENDERABLE_COMPONENT_H__

#include "transformComponent.h"

#include "material.h"
#include "mesh.h"
#include "shaderType.h"

class RenderableComponent : public TransformComponent {
	
private:
	Material *m_material;
	Mesh *m_mesh;
	
	ShaderType m_shaderType;
	bool m_isVisible;
	
public:
	RenderableComponent();
	RenderableComponent( const std::string &pMesh, const std::string &pTexture );
	virtual ~RenderableComponent();
	
	virtual void Render();
};

#endif /* renderableComponent_h */
