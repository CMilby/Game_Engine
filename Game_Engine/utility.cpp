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
#endif

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
    return "";
}