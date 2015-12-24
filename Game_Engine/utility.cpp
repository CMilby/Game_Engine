//
//  utility.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "utility.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

#include "config.h"

#define __PATH_MAX__ 256

void Utility::PrintCurrentPath() {
    
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL( mainBundle );
    
    char path[ __PATH_MAX__ ];
    if ( !CFURLGetFileSystemRepresentation( resourceURL, true, ( UInt8* ) path, __PATH_MAX__ ) ) {
        // Uh ohhhh
    }
    
    CFRelease( resourceURL );
    chdir( path );
    printf( "Current Path: %s", path );
#endif
    
}

std::string Utility::DirectoryPath() {
    
#ifdef __APPLE__
    return "/Users/Craig/Xcode/Game_Engine/Game_Engine/resources/";
#endif
#ifdef _WIN32
    return "C:\\Users\\Craig";
#endif
    return "";
}

unsigned int Utility::GetMonitorWidth() {
#ifdef __APPLE__
    CGRect mainMonitor = CGDisplayBounds( CGMainDisplayID() );
    return ( unsigned int ) CGRectGetWidth( mainMonitor );
#endif
#ifdef _WIN32
    return ( unsigned int ) GetSystemMetrics( SM_CWSCREEN );
#endif
    return -1;
}

unsigned int Utility::GetMonitorHeight() {
#ifdef __APPLE__
    CGRect mainMonitor = CGDisplayBounds( CGMainDisplayID() );
    return ( unsigned int ) CGRectGetHeight( mainMonitor );
#endif
#ifdef _WIN32
    return ( unsigned int ) GetSystemMetrics( SM_CYSCREEN );
#endif
}

unsigned int Utility::ScreenHalfWidth() {
    return Config::GetScreenWidth() / 2;
}

unsigned int Utility::ScreenHalfHeight() {
    return Config::GetScreenHeight() / 2;
}










