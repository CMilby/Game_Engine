//
//  inputFramework.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_FRAMEWORK_H__
#define __INPUT_FRAMEWORK_H__

#include <vector>

#include "drawMode.h"
#include "math3d.h"

namespace MouseButton {
	
	enum {
		MOUSE_BUTTON_LEFT = 1,
		MOUSE_BUTTON_MIDDLE = 2,
		MOUSE_BUTTON_RIGHT = 3,
		MOUSE_WHEEL_UP = 4,
		MOUSE_WHEEL_DOWN = 5
	};
};

namespace Key{
	
	enum {
		KEY_UNKNOWN = 0,
		
		KEY_A = 4,
		KEY_B = 5,
		KEY_C = 6,
		KEY_D = 7,
		KEY_E = 8,
		KEY_F = 9,
		KEY_G = 10,
		KEY_H = 11,
		KEY_I = 12,
		KEY_J = 13,
		KEY_K = 14,
		KEY_L = 15,
		KEY_M = 16,
		KEY_N = 17,
		KEY_O = 18,
		KEY_P = 19,
		KEY_Q = 20,
		KEY_R = 21,
		KEY_S = 22,
		KEY_T = 23,
		KEY_U = 24,
		KEY_V = 25,
		KEY_W = 26,
		KEY_X = 27,
		KEY_Y = 28,
		KEY_Z = 29,
		
		KEY_0 = 30,
		KEY_1 = 31,
		KEY_2 = 32,
		KEY_3 = 33,
		KEY_4 = 34,
		KEY_5 = 35,
		KEY_6 = 36,
		KEY_7 = 37,
		KEY_8 = 38,
		KEY_9 = 39,
		
		KEY_RETURN = 40,
		KEY_ESCAPE = 41,
		KEY_BACKSPACE = 42,
		KEY_TAB = 43,
		KEY_SPACE = 44,
		
		KEY_MINUS = 45,
		KEY_EQUALS = 46,
		KEY_LEFT_BRACKET = 47,
		KEY_RIGHT_BRACKET = 48,
		KEY_BACKSLASH = 49,
		
		KEY_NONUSHASH = 50,
		KEY_SEMICOLON = 51,
		KEY_APOSTROPHE = 52,
		KEY_GRAVE = 53,
		
		KEY_COMMA = 54,
		KEY_PERIOD = 55,
		KEY_SLASH = 56,
		KEY_CAPSLOCK = 57,
		
		KEY_F1 = 58,
		KEY_F2 = 59,
		KEY_F3 = 60,
		KEY_F4 = 61,
		KEY_F5 = 62,
		KEY_F6 = 63,
		KEY_F7 = 64,
		KEY_F8 = 65,
		KEY_F9 = 66,
		KEY_F10 = 67,
		KEY_F11 = 68,
		KEY_F12 = 69,
		
		KEY_HOME = 74,
		KEY_PAGE_UP = 75,
		KEY_DELETE = 76,
		KEY_END = 77,
		KEY_PAGE_DOWN = 78,
		KEY_RIGHT_ARROW = 79,
		KEY_LEFT_ARROW = 80,
		KEY_DOWN_ARROW = 81,
		KEY_UP_ARROW = 82,
		
		KEY_NUM_LOCK = 83,
		
		KEY_KP_DIVIDE = 84,
		KEY_KP_MULTIPLY = 85,
		KEY_KP_SUBTRACT = 86,
		KEY_KP_ADD = 87,
		KEY_KP_ENTER = 88,
		
		KEY_KP_0 = 89,
		KEY_KP_1 = 90,
		KEY_KP_2 = 91,
		KEY_KP_3 = 92,
		KEY_KP_4 = 93,
		KEY_KP_5 = 94,
		KEY_KP_6 = 95,
		KEY_KP_7 = 96,
		KEY_KP_8 = 97,
		KEY_KP_9 = 98,
		KEY_KP_PERIOD = 99,
		
		KEY_APPLICATION = 101,
		KEY_POWER = 102,
		
		KEY_KP_EQUALS = 103,
		KEY_F13 = 103,
		KEY_F14 = 104,
		KEY_F15 = 105,
		KEY_F16 = 106,
		KEY_F17 = 108,
		KEY_F18 = 109,
		KEY_F19 = 110,
		KEY_F20 = 111,
		KEY_F21 = 112,
		KEY_F22 = 113,
		KEY_F23 = 114,
		KEY_F24 = 115,
		
		KEY_EXECUTE = 116,
		KEY_HELP = 117,
		KEY_MENU = 118,
		KEY_SELECT = 119,
		KEY_STOP = 120,
		KEY_AGAIN = 121,
		KEY_UNDO = 122,
		KEY_CUT = 123,
		KEY_COPY = 124,
		KEY_PASTE = 125,
		KEY_FIND = 126,
		KEY_MUTE = 127,
		KEY_VOLUME_UP = 128,
		KEY_VOLUME_DOWN = 129,
		
		KEY_KP_COMMA = 133,
		
		KEY_LEFT_CTRL = 224,
		KEY_LEFT_SHIFT = 225,
		KEY_LEFT_ALT = 226,
		KEY_LEFT_GUI = 227,
		KEY_RIGHT_CTRL = 228,
		KEY_RIGHT_SHIFT = 229,
		KEY_RIGHT_ALT = 230,
		KEY_RIGHT_GUI = 231,
		
		KEY_MODE = 257,
		
		KEY_AUDIO_NEXT = 258,
		KEY_AUDIO_PREV = 259,
		KEY_AUDIO_STOP = 260,
		KEY_AUDIO_PLAY = 261,
		KEY_AUDIO_MUTE = 262,
		KEY_MEDIA_SELECT = 263,
		
		KEY_BRIGHTNESS_DOWN = 275,
		KEY_BRIGHTNESS_UP = 276,
		KEY_DISPLAY_SWITCH = 277,
		KEY_EJECT = 281,
		KEY_SLEEP = 282
	};
};
	
class InputFramework {
	
public:
	static InputFramework* GetInstance() {
		if ( !s_instance ) {
			s_instance = new InputFramework();
		}
		return s_instance;
	}
	
	static const int NUM_KEYS = 512;
	static const int NUM_MOUSE_BUTTONS = 64;
	
	void Update();
	
	static bool IsKeyDown( int key );
	static bool IsKeyUp( int key );
	
	static void SetKey( int key, bool value );
	
	static bool IsButtonDown( int button );
	static bool IsButtonUp( int button );
	
	static void SetButton( int button, bool value );
	
	static void SetCursor( bool visible );
	static Vector2<int> GetCursorPosition();
    
    static std::vector<int> GetDownKeys();
    static std::vector<int> GetDownButtons();
    
    static bool IsWindowCloseRequested();
	
	static void SetDrawMode( const DrawMode &mode );
	
private:
	static InputFramework *s_instance;
	
	static bool s_inputs[ NUM_KEYS ];
	static bool s_mouse[ NUM_MOUSE_BUTTONS ];
	
	static int s_mouseX;
	static int s_mouseY;
    
    static std::vector<int> s_downKeys;
    static std::vector<int> s_downButtons;
    
    static bool s_isWindowCloseRequested;

	InputFramework();
};

#endif /* inputFramework_h */
