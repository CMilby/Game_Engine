//
//  window.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "windowSystem.h"

#include "config.h"

WindowSystem::WindowSystem() : System( SYSTEM_WINDOW ) {
	m_width = Config::GetScreenWidth();
	m_height = Config::GetScreenHeight();
	m_title = "Craig!";
	m_fullscreen = Config::GetFullscreen();
	
	m_framework = new WindowFramework();
	m_framework->CreateWindow( m_width, m_height, m_title );
	m_framework->SetWindowFullscreen( m_fullscreen );
}

WindowSystem::WindowSystem( const std::string &pTitle ) : System( SYSTEM_WINDOW ) {
	m_width = Config::GetScreenWidth();
	m_height = Config::GetScreenHeight();
	m_title = pTitle;
	m_fullscreen = Config::GetFullscreen();
	
	m_framework = new WindowFramework();
	m_framework->CreateWindow( m_width, m_height, m_title );
	m_framework->SetWindowFullscreen( m_fullscreen );
	
}

WindowSystem::WindowSystem( unsigned int width, unsigned int height, const std::string &title ) : System( SYSTEM_WINDOW ) {
    m_width = width;
    m_height = height;
    m_title = title;
    m_fullscreen = false;
	
    m_framework = new WindowFramework();
    m_framework->CreateWindow( width, height, title );
    m_framework->SetWindowFullscreen( m_fullscreen );
}

WindowSystem::~WindowSystem() {
    if ( m_framework ) delete m_framework;
}

void WindowSystem::Init() {
    System::Init();
    
    m_callbacks[ MESSAGE_WINDOW_CLOSE_REQUESTED ] = std::bind( &WindowSystem::HandleWindowCloseRequested, this, std::placeholders::_1 );
    m_callbacks[ MESSAGE_UPDATE_MOUSE_POSITION ] = std::bind( &WindowSystem::HandleUpdateMousePosition, this, std::placeholders::_1 );
}

void WindowSystem::Update( float pDelta ) {
    m_framework->Update();
}

bool WindowSystem::ShouldClose() const {
    return m_framework->IsCloseRequested();
}

void WindowSystem::SetShouldClose( bool value ) {
    m_framework->SetIsCloseRequested( value );
}

void WindowSystem::SetMousePosition( const Vector2<int> &position ) const {
    m_framework->SetMousePositionInWindow( position );
}

void WindowSystem::SetFullscreen( bool value ) {
	m_fullscreen = value;
    m_framework->SetWindowFullscreen( value );
}

Vector2<int> WindowSystem::GetMousePosition() const {
    return m_framework->GetMousePositionInWindow();
}

void WindowSystem::HandleWindowCloseRequested( const std::vector<MessagePayload> &payload ) {
    SendMessage( SYSTEM_CORE_ENGINE, Message( SYSTEM_WINDOW, MESSAGE_CORE_ENGINE_STOP ) );
}

void WindowSystem::HandleUpdateMousePosition( const std::vector<MessagePayload> &payload ) {
    Vector2<int> pos( payload[ 0 ].GetPayloadInt(), payload[ 1 ].GetPayloadInt() );
    m_framework->SetMousePositionInWindow( pos );
}












