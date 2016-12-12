//
//  string_utility.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __STRING_UTILITY_H__
#define __STRING_UTILITY_H__

#include <string>
#include <vector>

namespace StringUtility {
    
    bool EndsWith( const std::string &pStr, const std::string &pEnding );
    int LastIndexOf( const std::string &pStr, char pDelim );
    
    std::string ToUpper( const std::string &pStr );
    std::vector<std::string> Split( const std::string &pStr, char pDelim );
    std::vector<std::string> Split( const std::string &pStr, char pDelim, std::vector<std::string> &pElems );
    
    void Trim( std::string &pStr );
    void LTrim( std::string &pStr );
    void RTrim( std::string &pStr) ;
}

#endif /* string_utility_h */
