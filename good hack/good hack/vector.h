#ifndef __SDK_VECTOR_H__
#define __SDK_VECTOR_H__

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include <math.h>
#include <limits>

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define FastSqrt(x)			(*sqrtf)(x)


#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define square( x ) ( x * x )
#define M_RADPI 57.295779513082f // (180 / pi)
#define SQUARE( a ) a*a
#define rad(a) a*(M_PI/180)
#define deg(a) a*(180/M_PI)
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

inline float sqrt2(float sqr)
{
	float root = 0;

	__asm
	{
		sqrtss xmm0, sqr
		movss root, xmm0
	}

	return root;
}

void inline SinCos(float radians, float sine, float cosine)
{
	sine = sin(radians);
	cosine = cos(radians);
}


	struct Vertex_t
	{
	public:

		float	x;
		float	y;

	private:

		float	tex_x = 0.f;
		float	tex_y = 0.f;
	};
	typedef float vec_t;
	class Vector
	{
	public:
		Vector(void)
		{
			Invalidate();
		}

		Vector(float X, float Y)
		{
			x = X;
			y = Y;
			z = 0;
		}

		Vector(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		Vector(const float* clr)
		{
			x = clr[0];
			y = clr[1];
			z = clr[2];
		}

		void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
		{
			x = ix; y = iy; z = iz;
		}
		bool IsValid() const
		{
			return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
		}
		void Invalidate()
		{
			x = y = z = std::numeric_limits<float>::infinity();
		}

		float& operator[](int i)
		{
			return ((float*)this)[i];
		}
		float operator[](int i) const
		{
			return ((float*)this)[i];
		}

		void Zero()
		{
			x = y = z = 0.0f;
		}
		Vector Normalize()
		{
			Vector vector;
			float length = this->Length();

			if (length != 0)
			{
				vector.x = x / length;
				vector.y = y / length;
				vector.z = z / length;
			}
			else
				vector.x = vector.y = 0.0f;
			vector.z = 1.0f;

			return vector;
		}
		bool operator==(const Vector& src) const
		{
			return (src.x == x) && (src.y == y) && (src.z == z);
		}
		bool operator!=(const Vector& src) const
		{
			return (src.x != x) || (src.y != y) || (src.z != z);
		}

		Vector& operator+=(const Vector& v)
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}
		Vector& operator-=(const Vector& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}
		Vector& operator*=(float fl)
		{
			x *= fl;
			y *= fl;
			z *= fl;
			return *this;
		}
		Vector& operator*=(const Vector& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		Vector& operator/=(const Vector& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		Vector& operator+=(float fl)
		{
			x += fl;
			y += fl;
			z += fl;
			return *this;
		}
		Vector& operator/=(float fl)
		{
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}
		Vector& operator-=(float fl)
		{
			x -= fl;
			y -= fl;
			z -= fl;
			return *this;
		}

		void NormalizeInPlace()
		{
			*this = Normalized();
		}
		Vector Normalized() const
		{
			Vector res = *this;
			float l = res.Length();
			if (l != 0.0f) {
				res /= l;
			}
			else {
				res.x = res.y = res.z = 0.0f;
			}
			return res;
		}

		float DistTo(const Vector &vOther) const
		{
			Vector delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;
			delta.z = z - vOther.z;

			return delta.Length();
		}
		float DistToSqr(const Vector &vOther) const
		{
			Vector delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;
			delta.z = z - vOther.z;

			return delta.LengthSqr();
		}
		float Dot(const Vector& vOther) const
		{
			return (x*vOther.x + y*vOther.y + z*vOther.z);
		}
		float Length() const
		{
			return sqrt(x*x + y*y + z*z);
		}
		float LengthSqr(void) const
		{
			return (x*x + y*y + z*z);
		}
		float Length2D() const
		{
			return sqrt(x*x + y*y);
		}
		inline vec_t Vector::Length2DSqr(void) const
		{
			return (x * x + y * y);
		}
		Vector& operator=(const Vector &vOther)
		{
			x = vOther.x; y = vOther.y; z = vOther.z;
			return *this;
		}

		Vector Vector::operator-(void) const
		{
			return Vector(-x, -y, -z);
		}
		Vector Vector::operator+(const Vector& v) const
		{
			return Vector(x + v.x, y + v.y, z + v.z);
		}
		Vector Vector::operator-(const Vector& v) const
		{
			return Vector(x - v.x, y - v.y, z - v.z);
		}
		Vector Vector::operator*(float fl) const
		{
			return Vector(x * fl, y * fl, z * fl);
		}
		Vector Vector::operator*(const Vector& v) const
		{
			return Vector(x * v.x, y * v.y, z * v.z);
		}
		Vector Vector::operator/(float fl) const
		{
			return Vector(x / fl, y / fl, z / fl);
		}
		Vector Vector::operator/(const Vector& v) const
		{
			return Vector(x / v.x, y / v.y, z / v.z);
		}

		float x, y, z;
	};

	inline Vector operator*(float lhs, const Vector& rhs)
	{
		return rhs * lhs;
	}
	inline Vector operator/(float lhs, const Vector& rhs)
	{
		return rhs / lhs;
	}

	//===============================================
	inline Vector CrossProduct(const Vector& a, const Vector& b)
	{
		return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}

	inline void CrossProduct2(const Vector& a, const Vector& b, Vector& result)
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}


	
	inline float VectorLength(const Vector& v)
	{
		CHECK_VALID(v);
		return (float)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}
	inline void VectorMultiply(const Vector& src, float fl, Vector& res)
	{
		Assert(IsFinite(fl));
		res.x = src.x * fl;
		res.y = src.y * fl;
		res.z = src.z * fl;
	}
	inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
	{
		dest[0] = start[0] + direction[0] * scale;
		dest[1] = start[1] + direction[1] * scale;
		dest[2] = start[2] + direction[2] * scale;
	}

	inline void VectorMAInline(const Vector& start, float scale, const Vector& direction, Vector& dest)
	{
		dest.x = start.x + direction.x*scale;
		dest.y = start.y + direction.y*scale;
		dest.z = start.z + direction.z*scale;
	}

	inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest)
	{
		VectorMAInline(start, scale, direction, dest);
	}

	inline void VectorMA(const float * start, float scale, const float *direction, float *dest)
	{
		VectorMAInline(start, scale, direction, dest);
	}

	inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
	{
		CHECK_VALID(a);
		CHECK_VALID(b);
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}

	inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
	{
		CHECK_VALID(a);
		CHECK_VALID(b);
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}

	
	class __declspec(align(16)) VectorAligned : public Vector
	{
	public:
		inline VectorAligned(void) {};
		inline VectorAligned(float X, float Y, float Z)
		{
			Init(X, Y, Z);
		}
	public:
		explicit VectorAligned(const Vector &vOther)
		{
			Init(vOther.x, vOther.y, vOther.z);
		}

		VectorAligned& operator=(const Vector &vOther)
		{
			Init(vOther.x, vOther.y, vOther.z);
			return *this;
		}

		float w;	// this space is used anyway
	};

	typedef Vector QAngle;

typedef float vec_t;
inline void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest)
{
	CHECK_VALID(src1);
	CHECK_VALID(src2);
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
}

inline Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t)
{
	Vector result;
	VectorLerp(src1, src2, t, result);
	return result;
}
#endif

struct cplane_t {
	Vector	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];

};

class matrix3x4_t
{
public:
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00; m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10; m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20; m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void SetOrigin(Vector const & p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				m_flMatVal[i][j] = std::numeric_limits<float>::infinity();;
			}
		}
	}

	Vector& at(int i) const { return *(Vector*)&m_flMatVal[i]; }

	float *operator[](int i) { return m_flMatVal[i]; }
	const float *operator[](int i) const { return m_flMatVal[i]; }
	float *Base() { return &m_flMatVal[0][0]; }
	const float *Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};
class matrix3x4a_t :public matrix3x4_t
{
public:
	/*
	matrix3x4a_t() { if (((size_t)Base()) % 16 != 0) { Error( "matrix3x4a_t missaligned" ); } }
	*/
	matrix3x4a_t& operator=(const matrix3x4_t& src) { memcpy(Base(), src.Base(), sizeof(float) * 3 * 4); return *this; };
};
class VMatrix {
public:

	VMatrix();
	VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	VMatrix(const Vector& forward, const Vector& left, const Vector& up);

	// Construct from a 3x4 matrix
	VMatrix(const matrix3x4_t& matrix3x4);

	// Set the values in the matrix.
	void		Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);


	// Initialize from a 3x4
	void		Init(const matrix3x4_t& matrix3x4);

	// array access
	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float *Base() {
		return &m[0][0];
	}

	inline const float *Base() const {
		return &m[0][0];
	}

	void		SetLeft(const Vector &vLeft);
	void		SetUp(const Vector &vUp);
	void		SetForward(const Vector &vForward);

	void		GetBasisVectors(Vector &vForward, Vector &vLeft, Vector &vUp) const;
	void		SetBasisVectors(const Vector &vForward, const Vector &vLeft, const Vector &vUp);

	// Get/set the translation.
	Vector &	GetTranslation(Vector &vTrans) const;
	void		SetTranslation(const Vector &vTrans);

	void		PreTranslate(const Vector &vTrans);
	void		PostTranslate(const Vector &vTrans);

	matrix3x4_t& As3x4();
	const matrix3x4_t& As3x4() const;
	void		CopyFrom3x4(const matrix3x4_t &m3x4);
	void		Set3x4(matrix3x4_t& matrix3x4) const;

	bool		operator==(const VMatrix& src) const;
	bool		operator!=(const VMatrix& src) const { return !(*this == src); }

	// Access the basis Vectors.
	Vector		GetLeft() const;
	Vector		GetUp() const;
	Vector		GetForward() const;
	Vector		GetTranslation() const;


	// Matrix->Vector operations.
public:
	// Multiply by a 3D Vector (same as operator*).
	void		V3Mul(const Vector &vIn, Vector &vOut) const;

	// Multiply by a 4D Vector.
	//void		V4Mul( const Vector4D &vIn, Vector4D &vOut ) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	Vector		ApplyRotation(const Vector &vVec) const;

	// Multiply by a Vector (divides by w, assumes input w is 1).
	Vector		operator*(const Vector &vVec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	Vector		VMul3x3(const Vector &vVec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	Vector		VMul3x3Transpose(const Vector &vVec) const;

	// Multiply by the upper 3 rows.
	Vector		VMul4x3(const Vector &vVec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	Vector		VMul4x3Transpose(const Vector &vVec) const;


	// Matrix->plane operations.
	//public:
	// Transform the plane. The matrix can only contain translation and rotation.
	//void		TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

	// Just calls TransformPlane and returns the result.
	//VPlane		operator*(const VPlane &thePlane) const;

	// Matrix->matrix operations.
public:

	VMatrix&	operator=(const VMatrix &mOther);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const VMatrix &vm, VMatrix &out) const;

	// Add two matrices.
	const VMatrix& operator+=(const VMatrix &other);

	// Just calls MatrixMul and returns the result.	
	VMatrix		operator*(const VMatrix &mOther) const;

	// Add/Subtract two matrices.
	VMatrix		operator+(const VMatrix &other) const;
	VMatrix		operator-(const VMatrix &other) const;

	// Negation.
	VMatrix		operator-() const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	VMatrix		operator~() const;

	// Matrix operations.
public:
	// Set to identity.
	void		Identity();

	bool		IsIdentity() const;

	// Setup a matrix for origin and angles.
	void		SetupMatrixOrgAngles(const Vector &origin, const QAngle &vAngles);

	// General inverse. This may fail so check the return!
	bool		InverseGeneral(VMatrix &vInverse) const;

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		InverseTR(VMatrix &mRet) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit Vectors and they are all orthogonal.
	bool		IsRotationMatrix() const;

	// This calls the other InverseTR and returns the result.
	VMatrix		InverseTR() const;

	// Get the scale of the matrix's basis Vectors.
	Vector		GetScale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	VMatrix		Scale(const Vector &vScale);

	// Normalize the basis Vectors.
	VMatrix		NormalizeBasisVectors() const;

	// Transpose.
	VMatrix		Transpose() const;

	// Transpose upper-left 3x3.
	VMatrix		Transpose3x3() const;

public:
	// The matrix.
	vec_t		m[4][4];
};
struct mstudiobbox_t
{
	int					bone;
	int					group;				// intersection group
	Vector				bbmin;				// bounding box
	Vector				bbmax;
	int					szhitboxnameindex;	// offset to the name of the hitbox.
	int        m_iPad01[3];
	float        m_flRadius;
	int        m_iPad02[4];

	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((char*)this) + szhitboxnameindex;
	}

	mstudiobbox_t() {}

private:
	mstudiobbox_t(const mstudiobbox_t& vOther);
};
class quaternion
{
public:
	float x, y, z, w;
	float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
	float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
};

class radian_euler
{
public:
	float x, y, z;
};
struct mstudiobone_t
{
	int					sznameindex;
	inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
	int		 			parent;		// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

											// default values
	Vector				pos;
	quaternion			quat;
	radian_euler			rot;
	// compression scale
	Vector				posscale;
	Vector				rotscale;

	matrix3x4_t			poseToBone;
	quaternion			qAlignment;
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
	inline int			GetSurfaceProp(void) const { return surfacepropLookup; }

	int					contents;		// See BSPFlags.h for the contents flags
	int					surfacepropLookup;	// this index must be cached by the loader, not saved in the file
	int					unused[7];		// remove as appropriate

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t& vOther);
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
};

class mstudioanimdesc_t {
};
class mstudioseqdesc_t {
};

struct studiohdr_t
{
	int					id;
	int					version;
	long				checksum;		// this has to be the same in the phy and vtx files to load!
	inline const char *	pszName(void) const { return name; }
	char				name[64];
	int					length;

	Vector				eyeposition;	// ideal eye position
	Vector				illumposition;	// illumination center
	Vector				hull_min;		// ideal movement hull size
	Vector				hull_max;
	Vector				view_bbmin;		// clipping bounding box
	Vector				view_bbmax;

	int					flags;
	int					numbones;			// bones
	int					boneindex;
	inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };
	int					RemapSeqBone(int iSequence, int iLocalBone) const;	// maps local sequence bone to global bone
	int					RemapAnimBone(int iAnim, int iLocalBone) const;		// maps local animations bone to global bone

	int					numbonecontrollers;		// bone controllers
	int					bonecontrollerindex;
	inline void *pBonecontroller(int i) const { return  (((byte *)this) + bonecontrollerindex) + i; };

	int					numhitboxsets;
	int					hitboxsetindex;

	// Look up hitbox set by index
	mstudiohitboxset_t	*pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t *)(((byte *)this) + hitboxsetindex) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t *pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const *s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	// Calls through to set to get hitbox count for set
	inline int			iHitboxCount(int set) const
	{
		mstudiohitboxset_t const *s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};

	// file local animations? and sequences
	//private:
	int					numlocalanim;			// animations/poses
	int					localanimindex;		// animation descriptions
	inline mstudioanimdesc_t *pLocalAnimdesc(int i) const { if (i < 0 || i >= numlocalanim) i = 0; return (mstudioanimdesc_t *)(((byte *)this) + localanimindex) + i; };

	int					numlocalseq;				// sequences
	int					localseqindex;
	inline mstudioseqdesc_t *pLocalSeqdesc(int i) const { if (i < 0 || i >= numlocalseq) i = 0; return (mstudioseqdesc_t *)(((byte *)this) + localseqindex) + i; };

	//public:
	bool				SequencesAvailable() const
	{

	}

	int					GetNumSeq() const;
	mstudioanimdesc_t	&pAnimdesc(int i) const;
	mstudioseqdesc_t	&pSeqdesc(int i) const;
	int					iRelativeAnim(int baseseq, int relanim) const;	// maps seq local anim reference to global anim index
	int					iRelativeSeq(int baseseq, int relseq) const;		// maps seq local seq reference to global seq index

																			//private:
	mutable int			activitylistversion;	// initialization flag - have the sequences been indexed?
	mutable int			eventsindexed;
	//public:
	int					GetSequenceActivity(int iSequence);
	void				SetSequenceActivity(int iSequence, int iActivity);
	int					GetActivityListVersion(void);
	void				SetActivityListVersion(int version) const;
	int					GetEventListVersion(void);
	void				SetEventListVersion(int version);

	// raw textures
	int					numtextures;
	int					textureindex;

	studiohdr_t() {}

private:
	// No copy constructors allowed
	studiohdr_t(const studiohdr_t& vOther);

	friend struct virtualmodel_t;
};