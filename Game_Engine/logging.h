//
//  logging.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <string>

class Logging {
    
public:
    enum LogLevel {
        LOGGING_INFO = 0,
        LOGGING_WARNING = 1,
        LOGGING_ERROR = 2
    };
    
    void Log( LogLevel level, const std::string &function, const std::string &message, const std::string &errors );
    void LogInfo( const std::string &function, const std::string &message, const std::string &errors );
    void LogWarning( const std::string &function, const std::string &message, const std::string &errors );
    void LogError( const std::string &function, const std::string &message, const std::string &errors );
    
private:
    Logging() {}
    
    std::string GetLogLevel( LogLevel level );
};

#endif /* logging_h */
