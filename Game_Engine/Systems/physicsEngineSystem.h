//
//  physicsEngineSystem.h
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PHYSICS_ENGINE_SYSTEM_H__
#define __PHYSICS_ENGINE_SYSTEM_H__

#include <vector>

#include "physicsBody2d.h"
#include "system.h"

class PhysicsEngineSystem : public System {
	
private:
	std::vector<PhysicsBody2D*> m_objects;
	
protected:
	void HandleSimulatePhysics( const std::vector<MessagePayload> &pPayload );
	void HandleHandleCollisions( const std::vector<MessagePayload> &pPayload );
	void HandleAddPhysicsBody( const std::vector<MessagePayload> &pPayload );
	
public:
	PhysicsEngineSystem();
	virtual ~PhysicsEngineSystem();
	
	virtual void Init();
	
	void AddObject( PhysicsBody2D *pBody );
};

#endif /* physicsEngineSystem_h */
