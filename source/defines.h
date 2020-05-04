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

#define CUBIX_TICKS_PER_SECOND 20
#define CUBIX_MS_PER_TICK 1000/CUBIX_TICKS_PER_SECOND

#define CUBIX_CHUNK_SIZE 32

namespace Defines
{

// Version
const std::string s_version{ "v1.0.0-indev" };

} // namespace Defines

#endif // CUBIX_DEFINES_H
