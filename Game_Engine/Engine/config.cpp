//
//  config.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "config.h"

unsigned int Config::s_screenWidth = 800;
unsigned int Config::s_screenHeight = 600;

float Config::s_fieldOfView = 45.0f;
float Config::s_aspectRatio = 1.3f;
float Config::s_zNear = 0.1f;
float Config::s_zFar = 32768.0f;

bool Config::s_debug = false;