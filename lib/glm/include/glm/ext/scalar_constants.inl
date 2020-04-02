#include <limits>

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType epsilon()
	{
		
		return std::numeric_limits<genType>::epsilon();
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType pi()
	{
		
		return static_cast<genType>(3.14159265358979323846264338327950288);
	}
} //namespace glm
