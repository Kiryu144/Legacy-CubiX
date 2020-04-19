/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "axis_aligned_bb.h"

namespace Core
{

AxisAlignedBB::AxisAlignedBB( const glm::vec3& min, const glm::vec3& max )
	: m_min( min ), m_max( max )
{
}

void AxisAlignedBB::addCoord( const glm::vec3& coord )
{
	if( coord.x < 0 )
	{
		m_min.x += coord.x;
	}
	else if( coord.x > 0 )
	{
		m_max.x += coord.x;
	}

	if( coord.y < 0 )
	{
		m_min.y += coord.y;
	}
	else if( coord.y > 0 )
	{
		m_max.y += coord.y;
	}

	if( coord.z < 0 )
	{
		m_min.z += coord.z;
	}
	else if( coord.z > 0 )
	{
		m_max.z += coord.z;
	}
}

void AxisAlignedBB::offset( const glm::vec3& v )
{
	m_min += v;
	m_max += v;
}

float AxisAlignedBB::calculateXOffset( const AxisAlignedBB& other, float def ) const
{
	if( other.m_max.y > m_min.y && other.m_min.y < m_max.y && other.m_max.z > m_min.z
		&& other.m_min.z < m_max.z )
	{
		if( def > 0.0D && other.m_max.x <= m_min.x )
		{
			float d1 = m_min.x - other.m_max.x;

			if( d1 < def )
			{
				def = d1;
			}
		}
		else if( def < 0.0D && other.m_min.x >= m_max.x )
		{
			float d0 = m_max.x - other.m_min.x;

			if( d0 > def )
			{
				def = d0;
			}
		}
	}
	return def;
}

float AxisAlignedBB::calculateYOffset( const AxisAlignedBB& other, float def ) const
{
	if( other.m_max.x > m_min.x && other.m_min.x < m_max.x && other.m_max.z > m_min.z
		&& other.m_min.z < m_max.z )
	{
		if( def > 0.0D && other.m_max.y <= m_min.y )
		{
			float d1 = m_min.y - other.m_max.y;

			if( d1 < def )
			{
				def = d1;
			}
		}
		else if( def < 0.0D && other.m_min.y >= m_max.y )
		{
			float d0 = m_max.y - other.m_min.y;

			if( d0 > def )
			{
				def = d0;
			}
		}
	}
	return def;
}

float AxisAlignedBB::calculateZOffset( const AxisAlignedBB& other, float def ) const
{
	if( other.m_max.x > m_min.x && other.m_min.x < m_max.x && other.m_max.y > m_min.y
		&& other.m_min.y < m_max.y )
	{
		if( def > 0.0D && other.m_max.z <= m_min.z )
		{
			float d1 = m_min.z - other.m_max.z;

			if( d1 < def )
			{
				def = d1;
			}
		}
		else if( def < 0.0D && other.m_min.z >= m_max.z )
		{
			float d0 = m_max.z - other.m_min.z;

			if( d0 > def )
			{
				def = d0;
			}
		}
	}

	return def;
}

glm::vec3 AxisAlignedBB::calculateOffset( const AxisAlignedBB& alignedBb,
										  const glm::vec3& def ) const
{
	return { calculateXOffset( alignedBb, def.x ),
			 calculateYOffset( alignedBb, def.y ),
			 calculateZOffset( alignedBb, def.z ) };
}

bool AxisAlignedBB::intersectsWith( const AxisAlignedBB& other ) const
{
	return m_min.x < other.m_max.x && m_max.x > other.m_min.x && m_min.y < other.m_max.y
		&& m_max.y > other.m_min.y && m_min.z < other.m_max.z && m_max.z > other.m_min.z;
}

bool AxisAlignedBB::intersectsWith( const glm::vec3& pos ) const
{
	return ( pos.x > m_min.x && pos.x < m_max.x ) && ( pos.y > m_min.y && pos.y < m_max.y )
		&& ( pos.z > m_min.z && pos.z < m_max.z );
}

} // namespace Core