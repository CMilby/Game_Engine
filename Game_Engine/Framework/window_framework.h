//
//  window_framework.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __WINDOW_FRAMEWORK_H__
#define __WINDOW_FRAMEWORK_H__

#include <string>

#include <SDL2/SDL.h>

#include "vector.h"

class WindowFramework {
    
private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    
    bool m_isCloseRequested;
    
public:
    WindowFramework();
    virtual ~WindowFramework();
    
    void CreateWindow( unsigned int width, unsigned int height, const std::string &title );
    
    void Update();
    
    bool IsCloseRequested() const;
    void SetIsCloseRequested( bool value );
    
    void SetWindowFullscreen( bool fullscreen );
    
    void SetMousePositionInWindow( const Vector2i &position );
    Vector2i GetMousePositionInWindow() const;
};

#endif /* window_framework_h */
