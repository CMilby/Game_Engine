//
//  input_utility.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "input_utility.h"

#include "input.h"

// Lol - What a terrible method
int InputUtility::StringToKey( const std::string &pKey ) {
    if ( pKey == "A" ) {
        return Key::KEY_A;
    } else if ( pKey == "B" ) {
        return Key::KEY_B;
    } else if ( pKey == "C" ) {
        return Key::KEY_C;
    } else if ( pKey == "D" ) {
        return Key::KEY_D;
    } else if ( pKey == "E" ) {
        return Key::KEY_E;
    } else if ( pKey == "F" ) {
        return Key::KEY_F;
    } else if ( pKey == "G" ) {
        return Key::KEY_G;
    } else if ( pKey == "H" ) {
        return Key::KEY_H;
    } else if ( pKey == "I" ) {
        return Key::KEY_I;
    } else if ( pKey == "J" ) {
        return Key::KEY_J;
    } else if ( pKey == "K" ) {
        return Key::KEY_K;
    } else if ( pKey == "L" ) {
        return Key::KEY_L;
    } else if ( pKey == "M" ) {
        return Key::KEY_M;
    } else if ( pKey == "N" ) {
        return Key::KEY_N;
    } else if ( pKey == "O" ) {
        return Key::KEY_O;
    } else if ( pKey == "P" ) {
        return Key::KEY_P;
    } else if ( pKey == "Q" ) {
        return Key::KEY_Q;
    } else if ( pKey == "R" ) {
        return Key::KEY_R;
    } else if ( pKey == "S" ) {
        return Key::KEY_S;
    } else if ( pKey == "T" ) {
        return Key::KEY_T;
    } else if ( pKey == "U" ) {
        return Key::KEY_U;
    } else if ( pKey == "V" ) {
        return Key::KEY_V;
    } else if ( pKey == "W" ) {
        return Key::KEY_W;
    } else if ( pKey == "X" ) {
        return Key::KEY_X;
    } else if ( pKey == "Y" ) {
        return Key::KEY_Y;
    } else if ( pKey == "Z" ) {
        return Key::KEY_Z;
    } else if ( pKey == "0" ) {
        return Key::KEY_0;
    } else if ( pKey == "1" ) {
        return Key::KEY_1;
    } else if ( pKey == "2" ) {
        return Key::KEY_2;
    } else if ( pKey == "3" ) {
        return Key::KEY_3;
    } else if ( pKey == "4" ) {
        return Key::KEY_4;
    } else if ( pKey == "5" ) {
        return Key::KEY_5;
    } else if ( pKey == "6" ) {
        return Key::KEY_6;
    } else if ( pKey == "7" ) {
        return Key::KEY_7;
    } else if ( pKey == "8" ) {
        return Key::KEY_8;
    } else if ( pKey == "9" ) {
        return Key::KEY_9;
    } else if ( pKey == "RETURN" ) {
        return Key::KEY_RETURN;
    } else if ( pKey == "ESCAPE" ) {
        return Key::KEY_ESCAPE;
    } else if ( pKey == "BACKSPACE" ) {
        return Key::KEY_BACKSPACE;
    } else if ( pKey == "TAB" ) {
        return Key::KEY_TAB;
    } else if ( pKey == "SPACE" ) {
        return Key::KEY_SPACE;
    } else if ( pKey == "MINUS" ) {
        return Key::KEY_MINUS;
    } else if ( pKey == "EQUALS" ) {
        return Key::KEY_EQUALS;
    } else if ( pKey == "LEFT_BRACKET" ) {
        return Key::KEY_LEFT_BRACKET;
    } else if ( pKey == "RIGHT_BRACKET" ) {
        return Key::KEY_RIGHT_BRACKET;
    } else if ( pKey == "BACKSLASH" ) {
        return Key::KEY_BACKSLASH;
    } else if ( pKey == "NONUSHASH" ) {
        return Key::KEY_NONUSHASH;
    } else if ( pKey == "SEMICOLON" ) {
        return Key::KEY_SEMICOLON;
    } else if ( pKey == "APOSTROPHE" ) {
        return Key::KEY_APOSTROPHE;
    } else if ( pKey == "GRAVE" ) {
        return Key::KEY_GRAVE;
    } else if ( pKey == "COMMA" ) {
        return Key::KEY_COMMA;
    } else if ( pKey == "PERIOD" ) {
        return Key::KEY_PERIOD;
    } else if ( pKey == "SLASH" ) {
        return Key::KEY_SLASH;
    } else if ( pKey == "CAPSLOCK" ) {
        return Key::KEY_CAPSLOCK;
    } else if ( pKey == "F1" ) {
        return Key::KEY_F1;
    } else if ( pKey == "F2" ) {
        return Key::KEY_F2;
    } else if ( pKey == "F3" ) {
        return Key::KEY_F3;
    } else if ( pKey == "F4" ) {
        return Key::KEY_F4;
    } else if ( pKey == "F5" ) {
        return Key::KEY_F5;
    } else if ( pKey == "F6" ) {
        return Key::KEY_F6;
    } else if ( pKey == "F7" ) {
        return Key::KEY_F7;
    } else if ( pKey == "F8" ) {
        return Key::KEY_F8;
    } else if ( pKey == "F9" ) {
        return Key::KEY_F9;
    } else if ( pKey == "F10" ) {
        return Key::KEY_F10;
    } else if ( pKey == "F11" ) {
        return Key::KEY_F11;
    } else if ( pKey == "F12" ) {
        return Key::KEY_F12;
    } else if ( pKey == "HOME" ) {
        return Key::KEY_HOME;
    } else if ( pKey == "PAGE_UP" ) {
        return Key::KEY_PAGE_UP;
    } else if ( pKey == "DELETE" ) {
        return Key::KEY_DELETE;
    } else if ( pKey == "END" ) {
        return Key::KEY_END;
    } else if ( pKey == "PAGE_DOWN" ) {
        return Key::KEY_PAGE_DOWN;
    } else if ( pKey == "RIGHT_ARROW" ) {
        return Key::KEY_RIGHT_ARROW;
    } else if ( pKey == "LEFT_ARROW" ) {
        return Key::KEY_LEFT_ARROW;
    } else if ( pKey == "DOWN_ARROW" ) {
        return Key::KEY_DOWN_ARROW;
    } else if ( pKey == "UP_ARROW" ) {
        return Key::KEY_UP_ARROW;
    } else if ( pKey == "NUM_LOCK" ) {
        return Key::KEY_NUM_LOCK;
    } else if ( pKey == "KP_DIVIDE" ) {
        return Key::KEY_KP_DIVIDE;
    } else if ( pKey == "KP_MULTIPLY" ) {
        return Key::KEY_KP_MULTIPLY;
    } else if ( pKey == "KP_SUBTRACT" ) {
        return Key::KEY_KP_SUBTRACT;
    } else if ( pKey == "KP_ADD" ) {
        return Key::KEY_KP_ADD;
    } else if ( pKey == "KP_ENTER" ) {
        return Key::KEY_KP_ENTER;
    } else if ( pKey == "KP_0" ) {
        return Key::KEY_KP_0;
    } else if ( pKey == "KP_1" ) {
        return Key::KEY_KP_1;
    } else if ( pKey == "KP_2" ) {
        return Key::KEY_KP_2;
    } else if ( pKey == "KP_3" ) {
        return Key::KEY_KP_3;
    } else if ( pKey == "KP_4" ) {
        return Key::KEY_KP_4;
    } else if ( pKey == "KP_5" ) {
        return Key::KEY_KP_5;
    } else if ( pKey == "KP_6" ) {
        return Key::KEY_KP_6;
    } else if ( pKey == "KP_7" ) {
        return Key::KEY_KP_7;
    } else if ( pKey == "KP_8" ) {
        return Key::KEY_KP_8;
    } else if ( pKey == "KP_9" ) {
        return Key::KEY_KP_9;
    } else if ( pKey == "KP_PERIOD" ) {
        return Key::KEY_KP_PERIOD;
    } else if ( pKey == "APPLICATION" ) {
        return Key::KEY_APPLICATION;
    } else if ( pKey == "POWER" ) {
        return Key::KEY_POWER;
    } else if ( pKey == "KP_EQUALS" ) {
        return Key::KEY_KP_EQUALS;
    } else if ( pKey == "F13" ) {
        return Key::KEY_F13;
    } else if ( pKey == "F14" ) {
        return Key::KEY_F14;
    } else if ( pKey == "F15" ) {
        return Key::KEY_F15;
    } else if ( pKey == "F16" ) {
        return Key::KEY_F16;
    } else if ( pKey == "F17" ) {
        return Key::KEY_F17;
    } else if ( pKey == "F18" ) {
        return Key::KEY_F18;
    } else if ( pKey == "F19" ) {
        return Key::KEY_F19;
    } else if ( pKey == "F20" ) {
        return Key::KEY_F20;
    } else if ( pKey == "F21" ) {
        return Key::KEY_F21;
    } else if ( pKey == "F22" ) {
        return Key::KEY_F22;
    } else if ( pKey == "F23" ) {
        return Key::KEY_F23;
    } else if ( pKey == "F24" ) {
        return Key::KEY_F24;
    } else if ( pKey == "EXECUTE" ) {
        return Key::KEY_EXECUTE;
    } else if ( pKey == "HELP" ) {
        return Key::KEY_HELP;
    } else if ( pKey == "MENU" ) {
        return Key::KEY_MENU;
    } else if ( pKey == "SELECT" ) {
        return Key::KEY_SELECT;
    } else if ( pKey == "STOP" ) {
        return Key::KEY_STOP;
    } else if ( pKey == "AGAIN" ) {
        return Key::KEY_AGAIN;
    } else if ( pKey == "UNDO" ) {
        return Key::KEY_UNDO;
    } else if ( pKey == "CUT" ) {
        return Key::KEY_CUT;
    } else if ( pKey == "COPY" ) {
        return Key::KEY_COPY;
    } else if ( pKey == "PASTE" ) {
        return Key::KEY_PASTE;
    } else if ( pKey == "FIND" ) {
        return Key::KEY_FIND;
    } else if ( pKey == "MUTE" ) {
        return Key::KEY_MUTE;
    } else if ( pKey == "VOLUME_UP" ) {
        return Key::KEY_VOLUME_UP;
    } else if ( pKey == "VOLUME_DOWN" ) {
        return Key::KEY_VOLUME_DOWN;
    } else if ( pKey == "KP_COMMA" ) {
        return Key::KEY_KP_COMMA;
    } else if ( pKey == "LEFT_CTRL" ) {
        return Key::KEY_LEFT_CTRL;
    } else if ( pKey == "LEFT_SHIFT" ) {
        return Key::KEY_LEFT_SHIFT;
    } else if ( pKey == "LEFT_ALT" ) {
        return Key::KEY_LEFT_ALT;
    } else if ( pKey == "LEFT_GUI" ) {
        return Key::KEY_LEFT_GUI;
    } else if ( pKey == "RIGHT_CTRL" ) {
        return Key::KEY_RIGHT_CTRL;
    } else if ( pKey == "RIGHT_SHIFT" ) {
        return Key::KEY_RIGHT_SHIFT;
    } else if ( pKey == "RIGHT_ALT" ) {
        return Key::KEY_RIGHT_ALT;
    } else if ( pKey == "RIGHT_GUI" ) {
        return Key::KEY_RIGHT_GUI;
    } else if ( pKey == "MODE" ) {
        return Key::KEY_MODE;
    } else if ( pKey == "AUDIO_NEXT" ) {
        return Key::KEY_AUDIO_NEXT;
    } else if ( pKey == "AUDIO_PREV" ) {
        return Key::KEY_AUDIO_PREV;
    } else if ( pKey == "AUDIO_STOP" ) {
        return Key::KEY_AUDIO_STOP;
    } else if ( pKey == "AUDIO_PLAY" ) {
        return Key::KEY_AUDIO_PLAY;
    } else if ( pKey == "AUDIO_MUTE" ) {
        return Key::KEY_AUDIO_MUTE;
    } else if ( pKey == "MEDIA_SELECT" ) {
        return Key::KEY_MEDIA_SELECT;
    } else if ( pKey == "BRIGHTNESS_DOWN" ) {
        return Key::KEY_BRIGHTNESS_DOWN;
    } else if ( pKey == "BRIGHTNESS_UP" ) {
        return Key::KEY_BRIGHTNESS_UP;
    } else if ( pKey == "DISPLAY_SWITCH" ) {
        return Key::KEY_DISPLAY_SWITCH;
    } else if ( pKey == "EJECT" ) {
        return Key::KEY_EJECT;
    } else if ( pKey == "SLEEP" ) {
        return Key::KEY_SLEEP;
    }
    
    return -1;
}

int InputUtility::StringToButton( const std::string &pButton ) {
    if (  pButton == "MOUSE_LEFT" ) {
        return MouseButton::MOUSE_BUTTON_LEFT;
    } else if ( pButton == "MOUSE_RIGHT" ) {
        return MouseButton::MOUSE_BUTTON_RIGHT;
    } else if ( pButton == "MOUSE_MIDDLE" ) {
        return MouseButton::MOUSE_BUTTON_MIDDLE;
    } else if ( pButton == "MOUSE_WHEEL_UP" ) {
        return MouseButton::MOUSE_WHEEL_UP;
    } else if ( pButton == "MOUSE_WHEEL_DOWN" ) {
        return MouseButton::MOUSE_WHEEL_DOWN;
    }
    
    return -1;
}

std::string InputUtility::KeyToString( int pKey ) {
    return "Not Implemeted";
}

std::string InputUtility::ButtonToString( int pButton ) {
    return "Not Implemeted";
}
