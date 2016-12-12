//
//  input_system.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "input_system.h"

#include "input_framework.h"

InputSystem* InputSystem::s_instance = 0;

void InputSystem::Init() {
    InputFramework::Init();
}

void InputSystem::Execute( float p_delta ) {
    InputFramework::Update();
    System::Execute( p_delta );
}
