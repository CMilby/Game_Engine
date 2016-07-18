//
//  monster.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "monster.h"

Monster::Monster() {
	
}

Monster::Monster( const Vector2<float> &pPosition ) : NPC( pPosition ) {
	SetMoveSpeed( 2.5f );
	SetSprintSpeed( 2.5f );
	
	SetMaxHealth( 200 );
	SetMaxMana( 100 );
	SetMaxStamina( 100 );
	
	SetCurrentHealth( GetMaxHealth() );
	SetCurrentMana( GetMaxMana() );
	SetCurrentStamina( GetCurrentStamina() );
	
	SetMaterial( new Material( new Texture( "monster.png" ) ) );
}

Monster::~Monster() {
	
}

void Monster::Update( float pDelta ) {
	
}