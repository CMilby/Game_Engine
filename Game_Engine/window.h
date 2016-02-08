//
//  window.h
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "math3d.h"

class Window {
    
private:
    SDL_Window *m_window;
	SDL_GLContext m_glContext;
    
    unsigned int m_width;
    unsigned int m_heigt;
    std::string m_title;
    
public:
    Window() {}
    Window( unsigned int width, unsigned int height, const std::string &title );
    virtual ~Window();
    
    void SwapBuffers();
    
    bool ShouldClose() const;
    void SetShouldClose( bool value );
    
    void SetMousePosition( const Vector2<int> &position ) const;
    Vector2<int> GetMousePosition() const;
    
    void SetFullscreen( bool value ) const;
    
    inline SDL_Window* GetWindow() const { return m_window; }
};

#endif /* window_h */
