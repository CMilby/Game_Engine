//
//  freeMoveComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FREE_MOVE_COMPONENT_H__
#define __FREE_MOVE_COMPONENT_H__

#include "inputComponent.h"
#include "math3d.h"

class FreeMoveComponent : public InputComponent {
	
private:
	
public:
	FreeMoveComponent( const Vector3<float> &pPositon = Vector3<float>() );
	virtual ~FreeMoveComponent();
	
	virtual void Input( float pDelta );
	
	void Move( const Vector3<float> &pDirection, float pAmount );
};

#endif /* freeMoveComponent_h */
