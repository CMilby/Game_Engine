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
	
	static int s_drawMode;
	
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
    virtual void Update();
    
	bool IsKeyDown( int key ) const;
	bool IsKeyUp( int key ) const;
	
	bool IsMouseDown( int button ) const;
	bool IsMouseUp( int button ) const;
    
	void SetCursorPosition( const Vector2<int> &position );
    
	void SetDrawMode( int mode );
	int GetDrawMode();
};

#endif /* input_h */

