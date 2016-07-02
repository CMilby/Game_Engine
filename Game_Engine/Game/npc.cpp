//
//  npc.cpp
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "npc.h"

#include "handItem.h"

NPC::NPC() {
	m_leftHand = new HandItem();
	m_rightHand = new HandItem();
}

NPC::NPC( const Vector2<float> &pPosition ) {
	SetPosition( Vector3<float>( pPosition.GetY(), pPosition.GetY(), 1.0f ) );
	
	m_leftHand = new HandItem();
	m_rightHand = new HandItem();
}

NPC::~NPC() {
	if ( m_leftHand != 0 ) {
		delete m_leftHand;
	}
	
	if ( m_rightHand != 0 ) {
		delete m_rightHand;
	}
}

void NPC::Update( float pDelta ) {
	m_leftHand->Update();
	m_rightHand->Update();
}