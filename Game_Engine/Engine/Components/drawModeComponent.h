//
//  drawModeComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __DRAW_MODE_COMPONENT_H__
#define __DRAW_MODE_COMPONENT_H__

#include "inputComponent.h"

class DrawModeComponent : public InputComponent {
	
private:
	
public:
	DrawModeComponent();
	virtual ~DrawModeComponent();
	
	virtual void Input( float pDelta );
};

#endif /* drawModeComponent_h */
