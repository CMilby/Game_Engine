//
//  logging.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "logging.h"

std::string Logging::GetLogLevel( LogLevel level ) {
    switch ( level ) {
        case LOGGING_INFO:
            return "Info";
        case LOGGING_WARNING:
            return "Warning";
        case LOGGING_ERROR:
            return "Error";
    }
    return "";
}










