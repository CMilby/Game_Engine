//
//  file_utility.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FILE_UTILITY_H__
#define __FILE_UTILITY_H__

#include <string>

namespace FileUtility {
    
    std::string FileDirectory();
    
    std::string GetConfigDirectory();
    std::string GetModelDirectory();
    std::string GetTextureDirectory();
    std::string GetShaderDirectory();
}

#endif /* file_utility_h */
