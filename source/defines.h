/*
 * Copyright (c) 2020 David Klostermann.
 */

#include <string>

#ifndef CUBIX_DEFINES_H
#define CUBIX_DEFINES_H

// Macros
#define CUBIX_ENABLE_ASSERT 1	  // enable cubix_assert()
#define CUBIX_GL_ERROR_CALLBACK 1 // enable opengl error callbacks
#define CUBIX_IMGUI 1			  // enable imgui

namespace Defines
{

// Version
const std::string s_version{ "v1.0.0-indev" };

} // namespace Defines

#endif // CUBIX_DEFINES_H
