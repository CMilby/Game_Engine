//
//  window.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "window.h"

#include "config.h"

Window::Window( const std::string &p_title ) {
    m_window = new WindowFramework();
    m_window->CreateWindow( Config::GetScreenWidth(), Config::GetScreenHeight(), p_title );
}

Window::Window( const std::string &p_title, unsigned int p_width, unsigned int p_height ) {
    m_window = new WindowFramework();
    m_window->CreateWindow( p_width, p_height, p_title );
}

Window::~Window() {
    if ( m_window != 0 ) {
        delete m_window;
        m_window = 0;
    }
}

void Window::Update() {
    m_window->Update();
}

bool Window::IsCloseRequested() const {
    return m_window->IsCloseRequested();
}

void Window::SetIsCloseRequested( bool p_value ) {
    m_window->SetIsCloseRequested( p_value );
}

void Window::SetWindowFullscreen( bool p_fullscreen ) {
    m_window->SetWindowFullscreen( p_fullscreen );
}

void Window::SetMousePositionInWindow( const Vector2i &p_position ) {
    m_window->SetMousePositionInWindow( p_position );
}

Vector2i Window::GetMousePositionInWindow() const {
    return m_window->GetMousePositionInWindow();
}







