//
//  input.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include <vector>

#include "buttons.h"
#include "keys.h"
#include "vector.h"

class Input {
    
private:
    Input();
    void operator=( const Input &p_input );
    
public:
    static bool IsKeyDown( int p_key );
    static bool IsKeyUp( int p_key );
    
    static void SetKey( int p_key, bool p_value );
    
    static bool IsButtonDown( int p_button );
    static bool IsButtonUp( int p_button );
    
    static void SetButton( int p_button, bool p_value );
    
    static void SetCursor( bool p_visible );
    static Vector2i GetCursorPosition();
    
    static std::vector<int> GetDownKeys();
    static std::vector<int> GetDownButtons();
    
    static bool IsWindowCloseRequested();
    
    static void SetDrawMode( int p_mode );
};

#endif /* input_h */
