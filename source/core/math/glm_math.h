/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_GLM_MATH_H
#define CUBIX_GLM_MATH_H

#include <ostream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// clang-format off
template< typename T1, typename T2 >
glm::vec<2, T1, glm::defaultp > operator+( const glm::vec<2, T1, glm::defaultp >& v1, const glm::vec<2, T2, glm::defaultp >& v2 )
{
	return glm::vec<2, T1, glm::defaultp >{ v1.x + v2.x, v1.y + v2.y };
}

template< typename T1, typename T2 >
glm::vec<2, T1, glm::defaultp > operator-( const glm::vec<2, T1, glm::defaultp >& v1, const glm::vec<2, T2, glm::defaultp >& v2 )
{
	return glm::vec<2, T1, glm::defaultp >{ v1.x - v2.x, v1.y - v2.y };
}

template< typename T1, typename T2 >
glm::vec<2, T1, glm::defaultp > operator/( const glm::vec<2, T1, glm::defaultp >& v1, const glm::vec<2, T2, glm::defaultp >& v2 )
{
	return glm::vec<2, T1, glm::defaultp >{ v1.x / v2.x, v1.y / v2.y };
}

template< typename T1, typename T2 >
glm::vec<4, T1, glm::defaultp > operator+( const glm::vec<4, T1, glm::defaultp >& v1, const glm::vec<4, T2, glm::defaultp >& v2 )
{
	return glm::vec<4, T1, glm::defaultp >{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

template< typename T1, typename T2 >
glm::vec<4, T1, glm::defaultp > operator-( const glm::vec<4, T1, glm::defaultp >& v1, const glm::vec<4, T2, glm::defaultp >& v2 )
{
	return glm::vec<4, T1, glm::defaultp >{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

template< typename T1, typename T2 >
glm::vec<4, T1, glm::defaultp > operator/( const glm::vec<4, T1, glm::defaultp >& v1, const glm::vec<4, T2, glm::defaultp >& v2 )
{
	return glm::vec<4, T1, glm::defaultp >{ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w };
}
// clang-format on

template< typename T >
struct Vec2Functor
{
	bool operator()( const glm::vec< 3, T, glm::defaultp >& v1,
					 const glm::vec< 3, T, glm::defaultp >& v2 )
	{
		return v1.x < v2.x
			|| ( v1.x == v2.x && ( v1.y < v2.y || ( v1.y == v2.y && v1.z < v2.z ) ) );
	}
};

#endif // CUBIX_GLM_MATH_H
