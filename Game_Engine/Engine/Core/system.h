//
//  system.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define WINDOWS 1
#define MAC 2
#define LINUX 3
#define UNKNWOWN 4

#ifdef _WIN32
#define OS WINDOWS
#elif __APPLE__
#define OS MAC
#elif __linux__
#define OS LINUX
#else
#define OS UNKNWOWN
#endif