#include "WindowPointerController.h"

std::unique_ptr<std::unordered_map<
	std::type_index, 
	std::unordered_map<
		std::string, std::unique_ptr<WindowPointerBase>
	>
>> WindowPointerController::pointers = std::make_unique<std::unordered_map<
	std::type_index,
	std::unordered_map<
	std::string, std::unique_ptr<WindowPointerBase>
	>
>>();