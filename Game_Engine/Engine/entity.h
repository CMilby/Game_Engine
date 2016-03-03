//
//  entity.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

#include "transform.h"

class Entity {
	
private:
	std::vector<Entity*> m_children;
	Transform m_transform;
	
protected:
	virtual void Input() {}
	virtual void Update() {}
	virtual void Render() {}
	
public:
	Entity();
	Entity( const Transform &transform );
	Entity( const Vector3<float> &position );
	virtual ~Entity();
	
	Entity* AddChild( Entity *child );
	
	void InputAll();
	void UpdateAll();
	void RenderAll();
};

#endif /* entity_h */
