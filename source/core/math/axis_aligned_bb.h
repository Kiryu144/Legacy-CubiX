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
private:
	template< typename T >
	int sign( T val ) const
	{
		return ( T( 0 ) < val ) - ( val < T( 0 ) );
	}

protected:
	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec3 m_size;
	glm::vec3 m_center;

public:
	AxisAlignedBB( const glm::vec3& min, const glm::vec3& max );

	glm::vec3 getOverlapping( const AxisAlignedBB& other ) const;
};

} // namespace Core

#endif
