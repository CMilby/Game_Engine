//
//  utility.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "utility.h"

std::string Utility::DirectoryPath() {

#ifdef __APPLE__
    return "/Users/Craig/Xcode/Game_Engine/Game_Engine/Resources/";
#endif
#ifdef _WIN32
    return "C:\\Users\\Craig";
#endif
    return "";
}