#pragma once

#include "Vec2.h"
#include <string.h>

template <typename T>
class _Mat3
{
public:
	_Mat3& operator =(const _Mat3& rhs)
	{
		memcpy( elements,rhs.elements,sizeof(elements) );
		return *this;
	}
	_Mat3& operator *=(const T rhs)
	{
		for( T& e : elements )
		{
			e *= rhs;
		}
		return *this;
	}
	_Mat3 operator *(const T rhs) const
	{
		_Mat3 result = *this;
		return result *= rhs;
	}
	_Mat3 operator *(const _Mat3& rhs) const
	{
		_Mat3 result;
		for( int j = 0; j < 3; j++ )
		{
			for( int k = 0; k < 3; k++ )
			{
				T sum = (T)0.0;
				for( int i = 0; i < 3; i++ )
				{
					sum += elements[ j ][ i ] * rhs.elements[ i ][ k ];
				}
				result.elements[ j ][ k ] = sum;
			}
		}
		return result;
	}
	_Mat3& operator *=(const _Mat3& rhs)
	{
		return *this = *this * rhs;
	}
	_Vec2< T > operator *(const _Vec2<T> rhs) const
	{
		_Vec2< T > result;
		result.x = elements[ 0 ][ 0 ] * rhs.x + elements[ 0 ][ 1 ] * rhs.y + elements[ 0 ][ 2 ];
		result.y = elements[ 1 ][ 0 ] * rhs.x + elements[ 1 ][ 1 ] * rhs.y + elements[ 1 ][ 2 ];
		return result;
	}
	inline T ExtractScaleIsometric() const
	{
		return _Vec2<T>{ elements[0][0],elements[1][0] }.Len();
	}
	inline _Vec2<T> ExtractStretch() const
	{
		return {
			_Vec2<T>{ elements[0][0],elements[1][0] }.Len(),
			_Vec2<T>{ elements[0][1],elements[1][1] }.Len()
		};
	}
	class _Vec2<T> ExtractTranslation() const
	{
		return { elements[0][2],elements[1][2] };
	}
public:
	static _Mat3 Identity()
	{
		return { (T)1.0,(T)0.0,(T)0.0,(T)0.0,(T)1.0,(T)0.0,(T)0.0,(T)0.0,(T)1.0 };
	}
	static _Mat3 Rotation( const T theta )
	{
		const T cosTheta = cos( theta );
		const T sinTheta = sin( theta );
		return { cosTheta,-sinTheta,(T)0.0,sinTheta,cosTheta,(T)0.0,(T)0.0,(T)0.0,(T)1.0 };
	}
	static _Mat3 Scaling( const T factor )
	{
		return { factor,(T)0.0,(T)0.0,(T)0.0,factor,(T)0.0,(T)0.0,(T)0.0,(T)1.0 };
	}
	static _Mat3 Translation( const _Vec2<T> offset )
	{
		return { (T)1.0,(T)0.0,offset.x,(T)0.0,(T)1.0,offset.y,(T)0.0,(T)0.0,(T)1.0 };
	}
	static _Mat3 Stretch( const T x,const T y )
	{
		return { x,(T)0.0,(T)0.0,(T)0.0,y,(T)0.0,(T)0.0,(T)0.0,(T)1.0 };
	}
public:
	// [ row ][ col ]
	T elements[ 3 ][ 3 ];
};

typedef _Mat3< float > Mat3;