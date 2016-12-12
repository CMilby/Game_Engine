//
//  input_framework.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_FRAMEWORK_H__
#define __INPUT_FRAMEWORK_H__

#include <vector>

#include "vector.h"

class InputFramework {
    
public:
    static const int NUM_KEYS = 512;
    static const int NUM_MOUSE_BUTTONS = 64;
    
    static void Init();
    static void Update();
    
    static bool IsKeyDown( int key );
    static bool IsKeyUp( int key );
    
    static void SetKey( int key, bool value );
    
    static bool IsButtonDown( int button );
    static bool IsButtonUp( int button );
    
    static void SetButton( int button, bool value );
    
    static void SetCursor( bool visible );
    static Vector2i GetCursorPosition();
    
    static std::vector<int> GetDownKeys();
    static std::vector<int> GetDownButtons();
    
    static bool IsWindowCloseRequested();
    
    static void SetDrawMode( int p_mode );
    
private:
    static bool s_inputs[ NUM_KEYS ];
    static bool s_mouse[ NUM_MOUSE_BUTTONS ];
    
    static int s_mouseX;
    static int s_mouseY;
    
    static std::vector<int> s_downKeys;
    static std::vector<int> s_downButtons;
    
    static bool s_isWindowCloseRequested;
    
    InputFramework();
    void operator=( const InputFramework &p_framework );
};

#endif /* input_framework_h */
