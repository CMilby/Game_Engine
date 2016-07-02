//
//  configLoader.h
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CONFIG_LOADER_H__
#define __CONFIG_LOADER_H__

#include <functional>
#include <map>
#include <string>

class ConfigLoader {
	
private:
	std::map<std::string, std::function<void( const std::string &pValue )>> m_callbacks;
	
	ConfigLoader() {
		PopulateCallbacks();
	}
	
	ConfigLoader( const ConfigLoader& ) = delete;
	void operator=( const ConfigLoader& ) = delete;
	
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
	static ConfigLoader& GetInstance() {
		static ConfigLoader instance;
		return instance;
	}

	void LoadConfigFile();
	void LoadConfigFile( const std::string &pFilepath );
};

#endif