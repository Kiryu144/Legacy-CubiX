/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_AXIS_ALIGNED_BB_H
#define CUBIX_AXIS_ALIGNED_BB_H

#include <glm/vec3.hpp>

namespace Core
{

class AxisAlignedBB
{
protected:
	glm::vec3 m_min;
	glm::vec3 m_max;

public:
	AxisAlignedBB( const glm::vec3& min = glm::vec3{ 0.0f },
				   const glm::vec3& max = glm::vec3{ 1.0f } );

	static inline AxisAlignedBB FromPosition( const glm::vec3& pos,
											  const glm::vec3& size = glm::vec3( 1.0 ) )
	{
		return AxisAlignedBB( pos, pos + size );
	}

	void addCoord( const glm::vec3& coord );
	void offset( const glm::vec3& v );

	float calculateXOffset( const AxisAlignedBB& other, float def = 0.0f ) const;
	float calculateYOffset( const AxisAlignedBB& other, float def = 0.0f ) const;
	float calculateZOffset( const AxisAlignedBB& other, float def = 0.0f ) const;
	glm::vec3 calculateOffset( const AxisAlignedBB& alignedBb, const glm::vec3& def ) const;

	bool intersectsWith( const AxisAlignedBB& other ) const;
	bool intersectsWith( const glm::vec3& pos ) const;
};

} // namespace Core

#endif
