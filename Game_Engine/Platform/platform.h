//
//  platform.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef _WIN32
#define WINDOWS 1
#elif __APPLE__
#define MAC 2
#elif __linux__
#define LINUX 3
#else
#define UNKNWOWN 4
#endif

#endif /* platform_h */
