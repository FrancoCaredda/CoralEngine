#ifndef TYPES_H
#define TYPES_H

#include "defines.h"

class CORAL_API CoralMonitor
{
public:
	CoralMonitor() = default;
	friend class AWindow;
	friend class Application;
private:
	GLFWmonitor* m_Monitor = nullptr;
};


#endif // !TYPES_H

