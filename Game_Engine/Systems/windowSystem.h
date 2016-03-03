//
//  windowSystem.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __WINDOW_SYSTEM_H__
#define __WINDOW_SYSTEM_H__

#include <string>

#include "math3d.h"
#include "system.h"
#include "windowFramework.h"

class WindowSystem : public System {
    
private:
    WindowFramework *m_framework;
    
    unsigned int m_width;
    unsigned int m_heigt;
    std::string m_title;
	bool m_fullscreen;
    
    void HandleWindowCloseRequested( const std::vector<MessagePayload> &payload );
    void HandleUpdateMousePosition( const std::vector<MessagePayload> &payload );
    
public:
    WindowSystem();
    WindowSystem( unsigned int width, unsigned int height, const std::string &title );
    virtual ~WindowSystem();
    
    virtual void Init();
    virtual void Update();
    
    bool ShouldClose() const;
    void SetShouldClose( bool value );
    
    void SetMousePosition( const Vector2<int> &position ) const;
    Vector2<int> GetMousePosition() const;
    
    void SetFullscreen( bool value );
	inline bool IsFullscreen() const { return m_fullscreen; }
};

#endif /* windowSystem_h */
