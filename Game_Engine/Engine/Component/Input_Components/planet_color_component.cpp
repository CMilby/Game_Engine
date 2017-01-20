//
//  planet_color_component.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planet_color_component.h"

#include "entity.h"
#include "input.h"
#include "planet.h"

#include "render_component.h"

PlanetColorComponent::PlanetColorComponent( Planet* p_planet ) : m_planet( p_planet ) {
	m_lastPressed = -1;
}

PlanetColorComponent::~PlanetColorComponent() {
	
}

void PlanetColorComponent::Execute( float p_delta ) {
	if ( Input::IsKeyDown( Key::KEY_1 ) ) {
		if ( m_lastPressed != Key::KEY_1 ) {
			RenderComponent* render = ( RenderComponent* ) GetParent()->GetComponent( ComponentType::RENDER_COMPONENT );
			render->UpdateColors( m_planet->ColorizeRandom() );
		}
		m_lastPressed = Key::KEY_1;
	}
	
	if ( Input::IsKeyDown( Key::KEY_2 ) ) {
		if ( m_lastPressed != Key::KEY_2 ) {
			RenderComponent* render = ( RenderComponent* ) GetParent()->GetComponent( ComponentType::RENDER_COMPONENT );
			render->UpdateColors( m_planet->ColorizePlates() );
		}
		m_lastPressed = Key::KEY_2;
	}
	
	if ( Input::IsKeyDown( Key::KEY_3 ) ) {
		if ( m_lastPressed != Key::KEY_3 ) {
			RenderComponent* render = ( RenderComponent* ) GetParent()->GetComponent( ComponentType::RENDER_COMPONENT );
			render->UpdateColors( m_planet->ColorizePlateTypes() );
		}
		m_lastPressed = Key::KEY_3;
	}
	
	if ( Input::IsKeyDown( Key::KEY_4 ) ) {
		if ( m_lastPressed != Key::KEY_4 ) {
			RenderComponent* render = ( RenderComponent* ) GetParent()->GetComponent( ComponentType::RENDER_COMPONENT );
			render->UpdateColors( m_planet->ColorizeStressVector() );
		}
		m_lastPressed = Key::KEY_4;
	}
	
	if ( Input::IsKeyDown( Key::KEY_5 ) ) {
		if ( m_lastPressed != Key::KEY_5 ) {
			RenderComponent* render = ( RenderComponent* ) GetParent()->GetComponent( ComponentType::RENDER_COMPONENT );
			render->UpdateColors( m_planet->ColorizeHeight() );
		}
	}
}
