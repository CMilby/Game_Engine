//
//  testGame.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/4/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "testGame.h"

#include "aabbCollider.h"
#include "sphereCollider.h"
#include "renderableEntity.h"

TestGame::TestGame() {
	
}

void TestGame::LoadGame() {
	RenderableEntity *plane = new RenderableEntity( "plane.obj" );
	
	RenderableEntity *jeep = new RenderableEntity( "jeep.obj", "jeep_army.png" );
	jeep->SetScale( Vector3<float>( 0.01f, 0.01f, 0.01f ) );
	jeep->SetPosition( Vector3<float>( -4.0f, 0.0f, -5.0f ) );
	
	RenderableEntity *cube1 = new RenderableEntity( "cube.obj" );
	cube1->SetPosition( Vector3<float>( 1.0f, 2.0f, 1.0f ) );
	cube1->SetPhysicsBody( new PhysicsBody( new AABBCollider( cube1->GetPosition() - cube1->GetScale(), cube1->GetPosition() + cube1->GetScale() ), Vector3<float>( 0.0f, 0.0f, 0.0f ) ) );
	
	RenderableEntity *cube2 = new RenderableEntity( "cube.obj" );
	cube2->SetPosition( Vector3<float>( 5.0f, 6.5f, 6.5f ) );
	cube2->SetScale( Vector3<float>( 1.0f, 1.5f, 1.0f ) );
	cube2->SetPhysicsBody( new PhysicsBody( new AABBCollider( cube2->GetPosition() - cube2->GetScale(), cube2->GetPosition() + cube2->GetScale() ), Vector3<float>( -1.0f, 0.0f, 0.0f ) ) );
	
	RenderableEntity *sphere1 = new RenderableEntity( "sphere.obj" );
	sphere1->SetPosition( Vector3<float>( 0.0f, 5.0f, 5.0f ) );
	sphere1->SetPhysicsBody( new PhysicsBody( new SphereCollider( sphere1->GetPosition(), sphere1->GetScale().GetX() ), Vector3<float>( 0.0f, 0.0f, 0.0f ) ) );
	
	RenderableEntity *sphere2 = new RenderableEntity( "sphere.obj" );
	sphere2->SetPosition( Vector3<float>( 0.0f, 0.0f, 5.0f ) );
	sphere2->SetPhysicsBody( new PhysicsBody( new SphereCollider( sphere2->GetPosition(), sphere2->GetScale().GetX() ), Vector3<float>( 0.0f, 1.0f, 0.0f ) ) );
	
	AddToScene( plane );
	AddToScene( jeep );
	
	AddToScene( cube1 );
	AddToScene( cube2 );
	
	AddToScene( sphere1 );
	AddToScene( sphere2 );
}