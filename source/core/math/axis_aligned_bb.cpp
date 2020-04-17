/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "axis_aligned_bb.h"

namespace Core
{

AxisAlignedBB::AxisAlignedBB( const glm::vec3& min, const glm::vec3& max )
	: m_min( min ), m_max( max ), m_size( m_min - m_max ), m_center( m_size / glm::vec3( 2.0 ) )
{
}

glm::vec3 AxisAlignedBB::getOverlapping( const AxisAlignedBB& other ) const
{
	glm::vec3 overlappingAxis;
	if( ( std::abs( m_min.x - other.m_min.x ) * 2 > ( m_size.x + other.m_size.x ) )
		|| ( std::abs( m_min.y - other.m_min.y ) * 2 > ( m_size.y + other.m_size.y ) )
		|| ( std::abs( m_min.z - other.m_min.z ) * 2 > ( m_size.z + other.m_size.z ) ) )
	{
		return overlappingAxis; // No collision occured
	}

	overlappingAxis.x = sign( m_center.x - other.m_center.x )
		* ( ( other.m_size.x / 2 + m_size.x / 2 ) - std::abs( m_center.x - other.m_center.x ) );
	overlappingAxis.y = sign( m_center.y - other.m_center.y )
		* ( ( other.m_size.y / 2 + m_size.y / 2 ) - std::abs( m_center.y - other.m_center.y ) );
	overlappingAxis.z = sign( m_center.z - other.m_center.z )
		* ( ( other.m_size.z / 2 + m_size.z / 2 ) - std::abs( m_center.z - other.m_center.z ) );

	for( int i = 0; i < 3; i++ )
	{ // Add a bit of an offset so that it actually moves out of the collision
		overlappingAxis[ i ] += sign( overlappingAxis[ i ] ) * 0.0005;
	}

	return overlappingAxis;
}

void AxisAlignedBB::translate( const glm::vec3& v )
{
	m_min += v;
	m_max += v;
	m_center += v;
}

} // namespace Core