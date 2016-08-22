//
//  handItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "handItem.h"

HandItem::HandItem( eHand pHand ) : Item( "Hand", pHand ) {
	m_handLeftOffset = Vector3<float>( -0.25f, 0.25f, 0.0f );
	m_handRightOffset = Vector3<float>( 0.25f, 0.25f, 0.0f );
	
	GetRenderer()->SetMesh( new Mesh( "player_plane.obj" ) );
	GetRenderer()->SetMaterial( new Material( new Texture( "hand.png" ) ) );
	GetRenderer()->SetShaderType( ShaderType::SHADER_BASIC );
	GetRenderer()->SetIsVisible( true );
	
	SetPosition();
	SetScale( Vector3<float>( 0.25f, 0.25f, 0.25f ) );
	
	SetUseTime( 10 );
	
	m_forward = new Entity( ( ( pHand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset ) + Vector3<float>( 0.0f, 0.75f, 0.0f ) );
	AddChild( m_forward );
}

HandItem::HandItem( const std::string &pItem, eHand pHand ) : Item( pItem, pHand ) {
	// Used for subclasses
}

HandItem::~HandItem() {
	if ( m_forward != 0 ) {
		delete m_forward;
		m_forward = 0;
	}
}

void HandItem::Update( float pDelta ) {
	if ( IsCoolingDown() ) {
		SetCurrentCooldown( GetCurrentCooldown() - 1 );
		if ( GetCurrentCooldown() == 0 ) {
			SetIsCoolingDown( false );
		}
		
		if ( GetTimeSinceUse() <= GetUseTime() ) {
			SetPosition( GetPosition().Lerp( m_forward->GetPosition(), ( ( float ) GetTimeSinceUse() / ( float ) GetUseTime() ) ) );
			
			SetTimeSinceUse( GetTimeSinceUse() + 1 );
		} else {
			SetPosition();
		}
	}
	
	// GetPhysicsBody()->SetPosition( GetModelMatrix().GetPosition().GetXY() );
	
	// float *myPointMat = new float[ 16 ];
	// Matrix4<float> myMat;
	// Math3D::InvertMatrix( GetModelMatrix().ToPointer(), myPointMat );
	// ( Math3D::Matrix4FromPointer<float>( myPointMat ) * GetParent()->GetModelMatrix() ).Print();
	
	// GetModelMatrix().Print();
	
	// ( GetParent()->GetPosition() + GetPosition() ).Print();
}

bool HandItem::Use() {
	if ( IsCoolingDown() ) {
		return false;
	}
	
	Logger::LogInfo( "Item - Use", GetItemName() );
	
	SetTimeSinceUse( 0 );
	SetIsCoolingDown( true );
	SetCurrentCooldown( GetCooldown() );
	return true;
}