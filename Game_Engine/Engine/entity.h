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
	virtual void Init() {}
	virtual void Input() {}
	virtual void Update() {}
	virtual void Render() {}
	
public:
	Entity();
	Entity( const Transform &transform );
	Entity( const Vector3<float> &position );
	virtual ~Entity();
	
	Entity* AddChild( Entity *child );
	
	void InitAll();
	void InputAll();
	void UpdateAll();
	void RenderAll();
	
	inline void SetPosition( const Vector3<float> &position ) { m_transform.SetPosition( position ); }
	inline void SetScale( const Vector3<float> &scale ) { m_transform.SetScale( scale ); }
	inline void SetRotation( const Quaternion &rotation ) { m_transform.SetRotation( rotation ); }
	
	inline Vector3<float> GetPosition() const { return m_transform.GetPosition(); }
	inline Vector3<float> GetScale() const { return m_transform.GetScale(); }
	inline Quaternion GetRotation() const { return m_transform.GetRotation(); }
};

#endif /* entity_h */
