//
//  freeLookComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FREE_LOOK_COMPONENT_H__
#define __FREE_LOOK_COMPONENT_H__

#include "inputComponent.h"
#include "math3d.h"

class FreeLookComponent : public InputComponent {
	
private:
	
public:
	FreeLookComponent( const Quaternion &pRotation = Quaternion() );
	virtual ~FreeLookComponent();
	
	virtual void Input( float pDelta );
	
	void Rotate( const Quaternion &pQuat );
	void Rotate( const Vector3<float> &pAxis, float pAngle );
	
	inline void SetRotation( const Quaternion &pRotation ) { GetParent()->SetRotation( pRotation ); }
	inline Quaternion GetRotation() const { return GetParent()->GetRotation(); }
};

#endif /* freeLookComponent_h */
