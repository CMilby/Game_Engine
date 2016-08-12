//
//  component.h
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "componentTypes.h"

#include <vector>

class Entity;

class Component {
	
private:
	Entity *m_parent;
	ComponentType m_type;
	
public:
	Component( ComponentType pType );
	virtual ~Component();
	
	virtual void Init() {}
	virtual void Input( float pDelta ) {}
	virtual void Update( float pDelta ) {}
	virtual void Render() {}
	
	inline void SetParent( Entity *pParent ) { m_parent = pParent; }
	inline Entity* GetParent() const { return m_parent; }

	
	inline ComponentType GetType() const { return m_type; }
};

#endif /* component_h */
