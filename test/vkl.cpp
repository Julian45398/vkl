// vkl.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#define VKL_ENABLE_VALIDATION
#include "vkl.h"

#include <iostream>

int main()
{
	std::cout << "hello world!" << std::endl;
	if (vkl::createInstance(VK_VERSION_1_0, 0, nullptr, nullptr) == VK_NULL_HANDLE) {
		std::cout << "failed to create vulkan instance" << std::endl;
	}
	else {
		std::cout << "created vulkan instance" << std::endl;
	}
	return 0;
}
