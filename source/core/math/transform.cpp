/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core
{

void Transform::MatrixTranslate( glm::mat4& mat, const glm::vec3& vec )
{
	mat[ 3 ] = mat[ 0 ] * vec[ 0 ] + mat[ 1 ] * vec[ 1 ] + mat[ 2 ] * vec[ 2 ] + mat[ 3 ];
}

void Transform::MatrixScale( glm::mat4& mat, const glm::vec3& vec )
{
	mat[ 0 ] = mat[ 0 ] * vec[ 0 ];
	mat[ 1 ] = mat[ 1 ] * vec[ 1 ];
	mat[ 2 ] = mat[ 2 ] * vec[ 2 ];
}

void Transform::MatrixRotateX( glm::mat4& mat, float angle )
{
	const float c	 = std::cos( angle );
	const float s	 = std::sin( angle );
	const float temp = ( 1.0f - c );

	glm::mat4 rotate( 0.0f );
	rotate[ 0 ][ 0 ] = c + temp;
	rotate[ 1 ][ 1 ] = c;
	rotate[ 1 ][ 2 ] = s;
	rotate[ 2 ][ 1 ] = -s;
	rotate[ 2 ][ 2 ] = c;

	glm::mat4 result;
	result[ 0 ]
		= mat[ 0 ] * rotate[ 0 ][ 0 ] + mat[ 1 ] * rotate[ 0 ][ 1 ] + mat[ 2 ] * rotate[ 0 ][ 2 ];
	result[ 1 ]
		= mat[ 0 ] * rotate[ 1 ][ 0 ] + mat[ 1 ] * rotate[ 1 ][ 1 ] + mat[ 2 ] * rotate[ 1 ][ 2 ];
	result[ 2 ]
		= mat[ 0 ] * rotate[ 2 ][ 0 ] + mat[ 1 ] * rotate[ 2 ][ 1 ] + mat[ 2 ] * rotate[ 2 ][ 2 ];
	result[ 3 ] = mat[ 3 ];
	mat			= result;
}

void Transform::MatrixRotateY( glm::mat4& mat, float angle )
{
	const float c	 = std::cos( angle );
	const float s	 = std::sin( angle );
	const float temp = ( 1.0f - c );

	glm::mat4 rotate( 0.0f );
	rotate[ 0 ][ 0 ] = c;
	rotate[ 0 ][ 2 ] = -s;
	rotate[ 1 ][ 1 ] = c + temp;
	rotate[ 2 ][ 0 ] = s;
	rotate[ 2 ][ 2 ] = c;

	glm::mat4 result;
	result[ 0 ]
		= mat[ 0 ] * rotate[ 0 ][ 0 ] + mat[ 1 ] * rotate[ 0 ][ 1 ] + mat[ 2 ] * rotate[ 0 ][ 2 ];
	result[ 1 ]
		= mat[ 0 ] * rotate[ 1 ][ 0 ] + mat[ 1 ] * rotate[ 1 ][ 1 ] + mat[ 2 ] * rotate[ 1 ][ 2 ];
	result[ 2 ]
		= mat[ 0 ] * rotate[ 2 ][ 0 ] + mat[ 1 ] * rotate[ 2 ][ 1 ] + mat[ 2 ] * rotate[ 2 ][ 2 ];
	result[ 3 ] = mat[ 3 ];
	mat			= result;
}

void Transform::MatrixRotateZ( glm::mat4& mat, float angle )
{
	const float c	 = std::cos( angle );
	const float s	 = std::sin( angle );
	const float temp = ( 1.0f - c );

	glm::mat4 rotate( 0.0f );
	rotate[ 0 ][ 0 ] = c;
	rotate[ 0 ][ 1 ] = s;
	rotate[ 1 ][ 0 ] = -s;
	rotate[ 1 ][ 1 ] = c;
	rotate[ 2 ][ 2 ] = c + temp;

	glm::mat4 result;
	result[ 0 ]
		= mat[ 0 ] * rotate[ 0 ][ 0 ] + mat[ 1 ] * rotate[ 0 ][ 1 ] + mat[ 2 ] * rotate[ 0 ][ 2 ];
	result[ 1 ]
		= mat[ 0 ] * rotate[ 1 ][ 0 ] + mat[ 1 ] * rotate[ 1 ][ 1 ] + mat[ 2 ] * rotate[ 1 ][ 2 ];
	result[ 2 ]
		= mat[ 0 ] * rotate[ 2 ][ 0 ] + mat[ 1 ] * rotate[ 2 ][ 1 ] + mat[ 2 ] * rotate[ 2 ][ 2 ];
	result[ 3 ] = mat[ 3 ];

	mat = result;
}

glm::mat4 Transform::CreateModelMatrix( const glm::vec3& position, const glm::vec3& scale )
{
	glm::mat4 matrix( 1.0f );
	MatrixTranslate( matrix, position );
	MatrixScale( matrix, scale );
	return matrix;
}

glm::mat4 Transform::CreateModelMatrix( const glm::vec3& position,
										const glm::vec3& scale,
										const glm::vec3& rotation )
{
	glm::mat4 matrix( 1.0f );
	MatrixTranslate( matrix, position );
	MatrixRotateX( matrix, rotation.x );
	MatrixRotateY( matrix, rotation.y );
	MatrixRotateZ( matrix, rotation.z );
	MatrixScale( matrix, scale );
	return matrix;
}

glm::mat4 Transform::CreateModelMatrix( const glm::vec3& position,
										const glm::vec3& scale,
										const glm::vec3& rotation,
										const glm::vec3& rotationOrigin )
{
	glm::mat4 matrix( 1.0f );
	MatrixTranslate( matrix, position + rotationOrigin );
	MatrixRotateX( matrix, rotation.x );
	MatrixRotateY( matrix, rotation.y );
	MatrixRotateZ( matrix, rotation.z );
	MatrixTranslate( matrix, -rotationOrigin );
	MatrixScale( matrix, scale );
	return matrix;
}

glm::mat4 Transform::CreatePerspectiveProjection(
	uint32_t width, uint32_t height, float scale, float fov, float near, float far )
{
	return glm::perspective(
		fov, ( static_cast< float >( width ) / static_cast< float >( height ) ), near, far );
}

glm::mat4 Transform::CreateOrthogonalProjection( uint32_t width, uint32_t height, float scale )
{
	return glm::ortho( 0.0f,
					   scale,
					   ( static_cast< float >( height ) / static_cast< float >( width ) ) * scale,
					   0.0f,
					   -1.0f,
					   1.0f );
}

glm::vec3 Transform::CreateDirection( const glm::vec3& rotation )
{
	glm::vec3 front;
	front.x = std::cos( glm::radians( rotation.x ) ) * std::cos( glm::radians( rotation.y ) );
	front.y = std::sin( glm::radians( rotation.x ) );
	front.z = std::cos( glm::radians( rotation.x ) ) * std::sin( glm::radians( rotation.y ) );
	return front;
}

glm::vec3& Transform::getPosition()
{
	m_needsUpdate = true;
	return m_position;
}

glm::vec3& Transform::getRotation()
{
	m_needsUpdate = true;
	return m_rotation;
}

glm::vec3& Transform::getScale()
{
	m_needsUpdate = true;
	return m_scale;
}

const glm::mat4& Transform::getMatrix()
{
	if( m_needsUpdate )
	{
		m_matrix	  = CreateModelMatrix( m_position, m_scale, m_rotation );
		m_needsUpdate = false;
	}
	return m_matrix;
}

const glm::vec3& Transform::getPosition() const
{
	return m_position;
}

const glm::vec3& Transform::getRotation() const
{
	return m_rotation;
}

const glm::vec3& Transform::getScale() const
{
	return m_scale;
}

} // namespace Core