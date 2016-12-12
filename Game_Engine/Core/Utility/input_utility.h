//
//  input_utility.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_UTILITY_H__
#define __INPUT_UTILITY_H__

#include <string>

namespace InputUtility {
    
    int StringToKey( const std::string &pKey );
    int StringToButton( const std::string &pButton );
    
    std::string KeyToString( int pKey );
    std::string ButtonToString( int pButton );
}

#endif /* input_utility_h */
