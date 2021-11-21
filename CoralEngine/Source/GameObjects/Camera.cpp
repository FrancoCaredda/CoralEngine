#include "Camera.h"

#include "Components/Transform.h"

Camera::Camera()
	: AGameObject("MainWindow")
{
	AddComponent<Transform>();
}
