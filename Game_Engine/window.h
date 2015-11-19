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
#include <GLFW/glfw3.h>

class Window {
    
private:
    GLFWwindow *m_window;
    
    unsigned int m_width;
    unsigned int m_heigt;
    std::string m_title;
    
public:
    Window() {}
    Window( unsigned int width, unsigned int height, const std::string &title );
    virtual ~Window();
    
    void SwapBuffers();
    void PollEvents();

    bool ShouldClose() const;
    
    inline GLFWwindow* GetWindow() const { return m_window; }
};

#endif /* window_h */
