//
//  input.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include "inputFramework.h"
#include "system.h"
#include "windowSystem.h"

class InputSystem : public System {
	
private:
    static InputSystem *s_instance;
	static InputFramework *s_framework;
	
	static DrawMode s_drawMode;
	
    InputSystem();
    
public:
	static InputSystem *GetInstance() {
		if ( !s_instance ) {
			s_instance = new InputSystem();
			s_framework = InputFramework::GetInstance();
		}
		return s_instance;
	}
	
    virtual void Init();
	virtual void Update( float pDelta );
	
	static bool IsKeyDown( int key );
	static bool IsKeyUp( int key );
	
	static bool IsMouseDown( int button );
	static bool IsMouseUp( int button );
    
	static void SetCursorPosition( const Vector2<int> &position );
	static Vector2<int> GetCursorPosition();
    
	static void SetDrawMode( const DrawMode &mode );
	static DrawMode GetDrawMode();
};

#endif /* input_h */

