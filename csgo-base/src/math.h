#pragma once
#include "vector.h"
#include "sdk.h"
bool W2S(const Vector &v3D, Vector &v2D)
{
    return (g_pDebugOverlay->ScreenPosition(v3D, v2D) != 1);
}

void CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); //delta.Length
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles.z = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}

#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))
void MakeVector( Vector angle, Vector& vector )
{
	float pitch = float( angle[ 0 ] * M_PI / 180 );
	float yaw = float( angle[ 1 ] * M_PI / 180 );
	float tmp = float( cos( pitch ) );
	vector[ 0 ] = float( -tmp * -cos( yaw ) );
	vector[ 1 ] = float( sin( yaw )*tmp );
	vector[ 2 ] = float( -sin( pitch ) );
}
float Dot( const Vector &v1, Vector &v2 )
{
	return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}

Vector CalcAngle( Vector const &Source, Vector const &Destination )
{
	//#pragma warning(disable : 4244)
	Vector angles;
	Vector delta;
	delta.x = (Source.x - Destination.x);
	delta.y = (Source.y - Destination.y);
	delta.z = (Source.z - Destination.z);

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angles.x = (float)(atanf(delta.z / hyp) * 57.295779513082f);
	angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);

	angles.z = 0.0f;
	if (delta.x >= 0.0) { angles.y += 180.0f; }
	return angles;
}

float GetFov( Vector angle, Vector src, Vector dst )
{
	Vector ang, aim;
	ang = CalcAngle( src, dst);
	MakeVector( angle, aim);
	MakeVector( ang, ang);

	float mag = sqrt( pow( aim.x, 2 ) + pow( aim.y, 2 ) + pow( aim.z, 2 ) );
	float u_dot_v = Dot( aim, ang );

	return RAD2DEG( acos( u_dot_v / ( pow( mag, 2 ) ) ) );
}
