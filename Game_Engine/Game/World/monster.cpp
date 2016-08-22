//
//  monster.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "monster.h"

#include "circleCollider.h"
#include "physicsBody.h"
#include "renderableComponent.h"

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
	
	// SetPhysicsBody( new PhysicsBody( new CircleCollider( GetPosition().GetXY(), 0.875f ) ) );
	
	( ( RenderableComponent* ) GetComponent( ComponentType::RENDERABLE_COMPONENT ) )->SetMaterial( new Material( "monster.png" ) );
}

Monster::~Monster() {
	
}

void Monster::Update( float pDelta ) {
	NPC::Update( pDelta );
}



