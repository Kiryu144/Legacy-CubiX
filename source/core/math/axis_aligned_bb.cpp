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

void AxisAlignedBB::offset( const glm::vec3& v )
{
	m_min += v;
	m_max += v;
}

float AxisAlignedBB::calculateXOffset( const AxisAlignedBB& other, float _def ) const
{
	if( other.m_max.y > m_min.y && other.m_min.y < m_max.y && other.m_max.z > m_min.z
		&& other.m_min.z < m_max.z )
	{
		if( _def > 0.0D && other.m_max.x <= m_min.x )
		{
			float d1 = m_min.x - other.m_max.x;

			if( d1 < _def )
			{
				_def = d1;
			}
		}
		else if( _def < 0.0D && other.m_min.x >= m_max.x )
		{
			float d0 = m_max.x - other.m_min.x;

			if( d0 > _def )
			{
				_def = d0;
			}
		}

		return _def;
	}
	else
	{
		return _def;
	}
}

float AxisAlignedBB::calculateYOffset( const AxisAlignedBB& other, float _def ) const
{
	if( other.m_max.x > m_min.x && other.m_min.x < m_max.x && other.m_max.z > m_min.z
		&& other.m_min.z < m_max.z )
	{
		if( _def > 0.0D && other.m_max.y <= m_min.y )
		{
			float d1 = m_min.y - other.m_max.y;

			if( d1 < _def )
			{
				_def = d1;
			}
		}
		else if( _def < 0.0D && other.m_min.y >= m_max.y )
		{
			float d0 = m_max.y - other.m_min.y;

			if( d0 > _def )
			{
				_def = d0;
			}
		}

		return _def;
	}
	else
	{
		return _def;
	}
}

float AxisAlignedBB::calculateZOffset( const AxisAlignedBB& other, float _def ) const
{
	if( other.m_max.x > m_min.x && other.m_min.x < m_max.x && other.m_max.y > m_min.y
		&& other.m_min.y < m_max.y )
	{
		if( _def > 0.0D && other.m_max.z <= m_min.z )
		{
			float d1 = m_min.z - other.m_max.z;

			if( d1 < _def )
			{
				_def = d1;
			}
		}
		else if( _def < 0.0D && other.m_min.z >= m_max.z )
		{
			float d0 = m_max.z - other.m_min.z;

			if( d0 > _def )
			{
				_def = d0;
			}
		}

		return _def;
	}
	else
	{
		return _def;
	}
}

} // namespace Core