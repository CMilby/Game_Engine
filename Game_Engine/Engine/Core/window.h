//
//  window.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "window_framework.h"

class Window {
    
private:
    WindowFramework *m_window;
    
public:
    Window( const std::string &p_title );
    Window( const std::string &p_title, unsigned int p_width, unsigned int p_height );
    virtual ~Window();
    
    void Update();
    
    bool IsCloseRequested() const;
    void SetIsCloseRequested( bool p_value );
    
    void SetWindowFullscreen( bool p_fullscreen );
    
    void SetMousePositionInWindow( const Vector2i &p_position );
    Vector2i GetMousePositionInWindow() const;
};

#endif /* window_h */
