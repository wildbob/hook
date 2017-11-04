#include "math.h"
#include "interfaces.h"

void inline g_math::sin_cos(float radians, float *sine, float *cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void g_math::vector_angles(const Vector& forward, QAngle &angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}

	angles[2] = 0.0f;
}

void g_math::angle_vectors(const QAngle &angles, Vector *forward)
{
	float sp, sy, cp, cy;

	sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
	sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void g_math::angle_vectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;

	sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
	sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);
	sin_cos(DEG2RAD(angles[ROLL]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

float g_math::get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	Vector ang, aim;

	angle_vectors(viewAngle, &aim);
	angle_vectors(aimAngle, &ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

QAngle g_math::calc_angle(Vector src, Vector dst)
{
	QAngle angles;
	Vector delta = src - dst;
	vector_angles(delta, angles);
	delta.Normalized();
	return angles;
}

float g_math::vector_distance(Vector v1, Vector v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

void g_math::angle_vectors_2d(Vector& vecAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	sin_cos(static_cast<float>(vecAngles[1] * (M_PI / 180.f)), &sy, &cy);
	sin_cos(static_cast<float>(vecAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp * cy;
	vecForward[1] = cp * sy;
	vecForward[2] = -sp;
}

void g_math::vector_angles_2d(Vector& vecForward, Vector& vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}

void g_math::normalize_angles(Vector& vecAngles)
{
	for (auto i = 0; i < 3; ++i)
	{
		while (vecAngles[i] > 180.f)
			vecAngles[i] -= 360.f;

		while (vecAngles[i] < -180.f)
			vecAngles[i] += 360.f;
	}

	vecAngles[2] = 0.f;
}

void g_math::vector_transform(Vector& in1, matrix3x4a_t& in2, Vector &out)
{
	out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

void g_math::vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
	out[0] = in1.Dot(in2[0]) + in2[0][3];
	out[1] = in1.Dot(in2[1]) + in2[1][3];
	out[2] = in1.Dot(in2[2]) + in2[2][3];
}

Vector g_math::cubic_interpolate(const Vector& p1, const Vector& p2, const Vector& p3, const Vector& p4, float t)
{
	return p1 * (1 - t) * (1 - t) * (1 - t) +
		p2 * 3 * t * (1 - t) * (1 - t) +
		p3 * 3 * t * t * (1 - t) +
		p4 * t * t * t;
}

float g_math::get_delta(float hspeed, float maxspeed, float airaccelerate)
{
	auto term = (30.0 - (airaccelerate * maxspeed / 66.0)) / hspeed;

	if (term < 1.0f && term > -1.0f) {
		return acos(term);
	}

	return 0.f;
}

inline float g_math::random_float(float M, float N)
{
	return (float)(M + (rand() / (RAND_MAX / (N - M))));
}
