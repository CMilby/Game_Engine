//
//  time.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "time.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

float Timing::GetTime() {
    return ( float ) glfwGetTime();
}