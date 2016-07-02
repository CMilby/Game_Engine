//
//  config.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "config.h"

#include "inputFramework.h"

int Config::s_majorVersion = 0;
int Config::s_minorVersion = 1;
int Config::s_subVersion = 1;

bool Config::s_error = false;
bool Config::s_warning = false;
bool Config::s_info = false;
bool Config::s_debug = false;
bool Config::s_crash = true;
bool Config::s_severe = false;

int Config::s_keyUp = Key::KEY_W;
int Config::s_keyLeft = Key::KEY_A;
int Config::s_keyDown = Key::KEY_S;
int Config::s_keyRight = Key::KEY_D;
int Config::s_keyNext = Key::KEY_E;
int Config::s_keyLast = Key::KEY_Q;
int Config::s_keyInventory = Key::KEY_R;
int Config::s_keySprint = Key::KEY_LEFT_SHIFT;

int Config::s_buttonUseLeft = MouseButton::MOUSE_BUTTON_RIGHT;
int Config::s_buttonUseRight = MouseButton::MOUSE_BUTTON_LEFT;

unsigned int Config::s_screenWidth = 800;
unsigned int Config::s_screenHeight = 600;
bool Config::s_fullscreen = false;

float Config::s_fieldOfView = 45.0f;
float Config::s_aspectRatio = 1.3f;
float Config::s_zNear = 0.1f;
float Config::s_zFar = 1024.0f;

