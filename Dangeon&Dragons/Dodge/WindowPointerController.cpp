#include "WindowPointerController.h"

std::unordered_map<
	std::type_index, 
	std::unordered_map<
		std::string, std::unique_ptr<WindowPointerBase>
	>
> WindowPointerController::pointers;