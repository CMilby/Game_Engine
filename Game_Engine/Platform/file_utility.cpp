//
//  file_utility.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "file_utility.h"

#include "platform.h"

std::string FileUtility::FileDirectory() {
#ifdef WINDOWS
    return "C:\\Users\\Craig\\Development\\Game_Engine\\Game_Engine\\Assets\\";
#elif MAC
    return "/Users/Craig/Xcode/Game_Engine/Game_Engine/Assets/";
#endif
    return "";
}

std::string FileUtility::GetConfigDirectory() {
    std::string myDirect = FileUtility::FileDirectory();
    
#ifdef WINDOWS
    myDirect += "Config\\";
#elif MAC
    myDirect += "Config/";
#endif
    
    return myDirect;
}

std::string FileUtility::GetModelDirectory() {
    std::string myDirect = FileUtility::FileDirectory();
    
#ifdef WINDOWS
    myDirect += "Models\\";
#elif MAC
    myDirect += "Models/";
#endif
    
    return myDirect;
}

std::string FileUtility::GetTextureDirectory() {
    std::string myDirect = FileUtility::FileDirectory();
    
#ifdef WINDOWS
    myDirect += "Textures\\";
#elif MAC
    myDirect += "Textures/";
#endif
    
    return myDirect;
}

std::string FileUtility::GetShaderDirectory() {
    std::string myDirect = FileUtility::FileDirectory();
    
#ifdef WINDOWS
    myDirect += "Shaders\\";
#elif MAC
    myDirect += "Shaders/";
#endif
    // /Users/Craig/Xcode/Game_Engine/Game_Engine/Assets/Shaders
    return myDirect;
}
