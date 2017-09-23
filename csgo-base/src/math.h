#pragma once
#include "vector.h"
#include "sdk.h"
bool W2S(const Vector &v3D, Vector &v2D)
{
    return (g_pDebugOverlay->ScreenPosition(v3D, v2D) != 1);
}
/* 
void CalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); //delta.Length
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles.z = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
} */

#define M_RADPI 57.295779513082f
#undef M_PI
constexpr double M_PI = 3.14159265358979323846264338327950288419716939937510;
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

float GetFov(const Vector &viewAngle, const Vector &aimAngle)
{
	auto delta = viewAngle - aimAngle;
	delta.clamp();
	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}


void ayyCalcAngle(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D(); //delta.Length
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}

Vector CalcAngle( Vector const &Source, Vector const &Destination )
{
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

void AngleVectors(const Vector &angles, Vector *forward)
{
	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

void ClampAngles(Vector &angles)
{
	if (angles.x > 89.f)
		angles.x -= 360.f;
	else if (angles.x < -89.f)
		angles.x += 360.f;
	if (angles.y > 180.f)
		angles.y -= 360.f;
	else if (angles.y < -180.f)
		angles.y += 360.f;
 
	angles.z = 0;
}

void Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0){
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

float FovToPlayer(Vector ViewOffSet, Vector View, CEntity* pEntity, int bone = 8)
{
	const float MaxDegrees = 180.0f;
	Vector Angles = View;
	Vector Origin = ViewOffSet;
	Vector Delta(0, 0, 0);
	Vector Forward(0, 0, 0);
	AngleVectors(Angles, &Forward);
	Vector AimPos = pEntity->GetBonePosition(bone);
	VectorSubtract(AimPos, Origin, Delta);
	Normalize(Delta, Delta);
	float DotProduct = Forward.Dot(Delta);
	return (acos(DotProduct) * (MaxDegrees / PI));
}

