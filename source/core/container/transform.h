/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_TRANSFORM_H
#define CUBIX_TRANSFORM_H

#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>

namespace Core
{

class Transform
{
public:
	static void MatrixTranslate( glm::mat4& mat, const glm::vec3& vec );
	static void MatrixRotateX( glm::mat4& mat, float angle );
	static void MatrixRotateY( glm::mat4& mat, float angle );
	static void MatrixRotateZ( glm::mat4& mat, float angle );
	static void MatrixScale( glm::mat4& mat, const glm::vec3& vec );

	static glm::mat4 CreateModelMatrix( const glm::vec3& position, const glm::vec3& scale );
	static glm::mat4 CreateModelMatrix( const glm::vec3& position,
										const glm::vec3& scale,
										const glm::vec3& rotation );
	static glm::mat4 CreateModelMatrix( const glm::vec3& position,
										const glm::vec3& scale,
										const glm::vec3& rotation,
										const glm::vec3& rotationOrigin );

	static glm::mat4 CreatePerspectiveProjection( uint32_t width,
												  uint32_t height,
												  float scale,
												  float fov	 = 70.0f,
												  float near = 0.1f,
												  float far	 = 1000.0f );
	static glm::mat4 CreateOrthogonalProjection( uint32_t width, uint32_t height, float scale );

	static glm::vec3 CreateDirection( const glm::vec3& rotation );

private:
	glm::vec3 m_position{ 0.0f };
	glm::vec3 m_rotation{ 0.0f };
	glm::vec3 m_scale{ 1.0f };
	glm::mat4 m_matrix{ 1.0f };

	bool m_needsUpdate{ true };

public:
	glm::vec3& getPosition();
	glm::vec3& getRotation();
	glm::vec3& getScale();

	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const glm::vec3& getScale() const;
	const glm::mat4& getMatrix();
};

} // namespace Core

#endif
