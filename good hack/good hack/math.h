#include <Windows.h>
#include "vector.h"
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )


namespace g_math
{
	extern inline void sin_cos(float radians, float *sine, float *cosine);
	extern void angle_vectors_2d(Vector& vecAngles, Vector& vecForward);
	extern void vector_angles_2d(Vector& vecForward, Vector& vecAngles);
	extern void normalize_angles(Vector& vecAngles);
	extern void vector_angles(const Vector& forward, QAngle &angles);
	extern void angle_vectors(const QAngle& angles, Vector *forward);
	extern void angle_vectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up);
	extern QAngle calc_angle(Vector v1, Vector v2);
	extern float get_fov(const QAngle& viewAngle, const QAngle& aimAngle);
	extern float vector_distance(Vector v1, Vector v2);
	extern void vector_transform(Vector& in1, matrix3x4a_t& in2, Vector &out);
	extern void vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	extern float get_delta(float hspeed, float maxspeed, float airaccelerate);
	extern Vector extrapolate_tick(Vector p0, Vector v0);
	extern inline float random_float(float M, float N);
	extern Vector cubic_interpolate(const Vector& p1, const Vector& p2, const Vector& p3, const Vector& p4, float t);
}