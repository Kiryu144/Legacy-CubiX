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
	AxisAlignedBB( const glm::vec3& min, const glm::vec3& max );

	void offset(const glm::vec3& v);

	float calculateXOffset(const AxisAlignedBB& other, float _def) const;
	float calculateYOffset(const AxisAlignedBB& other, float _def) const;
	float calculateZOffset(const AxisAlignedBB& other, float _def) const;
};

}

#endif
