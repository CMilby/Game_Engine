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
#include "window.h"

class Input : public System {
	
private:
	static Input *s_instance;
	static Window *s_window;
	static InputFramework *s_framework;
	
	static int s_drawMode;
	
	Input();
	
public:
	static Input *GetInstance() {
		if ( !s_instance ) {
			s_instance = new Input();
			s_framework = InputFramework::GetInstance();
		}
		return s_instance;
	}
	
	void SetWindow( Window *window );
	
	bool IsKeyDown( int key ) const;
	bool IsKeyUp( int key ) const;
	
	bool IsMouseDown( int button ) const;
	bool IsMouseUp( int button ) const;
    
	void SetCursorPosition( const Vector2<int> &position );
    
	void SetDrawMode( int mode );
	int GetDrawMode();
    
	virtual void Update();
};

#endif /* input_h */

