//
//  config_utility.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CONFIG_UTILITY_H__
#define __CONFIG_UTILITY_H__

#include <functional>
#include <map>
#include <string>

class ConfigUtility {
    
private:
    std::map<std::string, std::function<void( const std::string &pValue )>> m_callbacks;
    
    ConfigUtility() {
        PopulateCallbacks();
    }
    
    ConfigUtility( const ConfigUtility& ) = delete;
    void operator=( const ConfigUtility& ) = delete;
    
protected:
    void PopulateCallbacks();
    
    void VersionCallback( const std::string &pValue );
    
    void ErrorCallback( const std::string &pValue );
    void WarningCallback( const std::string &pValue );
    void InfoCallback( const std::string &pValue );
    void DebugCallback( const std::string &pValue );
    void CrashCallback( const std::string &pValue );
    void SevereCallback( const std::string &pValue );
    
    void KeyUpCallback( const std::string &pValue );
    void KeyLeftCallback( const std::string &pValue );
    void KeyDownCallback( const std::string &pValue );
    void KeyRightCallback( const std::string &pValue );
    void KeyNextCallback( const std::string &pValue );
    void KeyLastCallback( const std::string &pValue );
    void KeyInventoryCallback( const std::string &pValue );
    void KeySprintCallback( const std::string &pValue );
    
    void ButtonUseLeftCallback( const std::string &pValue );
    void ButtonUseRightCallback( const std::string &pValue );
    
    void ScreenWidthCallback( const std::string &pValue );
    void ScreenHeightCallback( const std::string &pValue );
    void FullscreenCallback( const std::string &pValue );
    
    void ZNearCallback( const std::string &pValue );
    void ZFarCallback( const std::string &pValue );
    void FOVCallback( const std::string &pValue );
    
public:
    static ConfigUtility& GetInstance() {
        static ConfigUtility instance;
        return instance;
    }
    
    void LoadConfigFile();
    void LoadConfigFile( const std::string &pFilepath );
};

#endif /* config_utility_h */
