//
//  inputComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "component.h"
#include "inputSystem.h"

class InputComponent : public Component {
	
private:
	
public:
	InputComponent();
	InputComponent( ComponentType pType );
	virtual ~InputComponent();
	
	virtual void Input( float pDelta ) {}
};

#endif /* inputComponent_h */
