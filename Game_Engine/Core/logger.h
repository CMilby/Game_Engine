//
//  logger.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

namespace Logger {
    
    void Log( const std::string &pLevel, const std::string &pOrigin, const std::string &pMessage, const std::string &pContext );
    
    void LogError( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
    void LogWarning( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
    void LogInfo( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
    void LogDebug( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
    void LogCrash( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
    void LogSevere( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext = "" );
};

#endif /* logger_h */
