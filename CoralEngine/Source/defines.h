#ifndef DEFINES_H
#define DEFINES_H

#ifdef CORAL_ENGINE_EXPORT
#define CORAL_API __declspec(dllexport)
#else
#define CORAL_API __declspec(dllimport)
#endif // CORAL_ENGINE_EXPORT

#include "GL/glew.h"
#include "glfw3.h"

#define BUFFER_SIZE 256

#endif // !DEFINES_H
