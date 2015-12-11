#version 120
                                                                        
varying vec2 TexCoord0;
varying vec3 Normal0;
varying vec3 WorldPos0;

varying vec3 WorldPosOut;
varying vec3 DiffuseOut;
varying vec3 NormalOut;
varying vec3 TexCoordOut;
										
uniform sampler2D gColorMap;                
											
void main()									
{											
	WorldPosOut     = WorldPos0;					
	DiffuseOut      = texture2D(gColorMap, TexCoord0).xyz;
	NormalOut       = normalize(Normal0);					
	TexCoordOut     = vec3(TexCoord0, 0.0);				
}
