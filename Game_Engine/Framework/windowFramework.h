//
//  windowFramework.h
//  Game_Engine
//
//  Created by Craig Milby on 2/24/16.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __WINDOW_FRAMEWORK_H__
#define __WINDOW_FRAMEWORK_H__

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "math3d.h"

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
    
    void SetMousePositionInWindow( const Vector2<int> &position );
    Vector2<int> GetMousePositionInWindow() const;
};
    
#endif /* windowFramework_h */
