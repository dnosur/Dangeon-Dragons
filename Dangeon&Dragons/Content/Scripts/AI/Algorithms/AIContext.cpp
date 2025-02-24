#include "AIContext.h"

#include <iostream>
#include <typeindex>

AIContext::AIContext(std::unique_ptr<AIStrategy> strategy)
	: strategy(std::move(strategy))
{
}

void AIContext::SetStrategy(std::unique_ptr<AIStrategy> strategy)
{
	this->strategy = std::move(strategy);
}

bool AIContext::Invoke(Pawn* pawn, AIContext* sender)
{
	if (pawn && strategy)
	{
		//std::cout << "AIContext '" << typeid(*strategy).name() << "': invoke" << std::endl;
		return strategy->Invoke(pawn, sender);
	}

	//std::cout << "AIContext: invoke failed! No AI strategy" << std::endl;
	return false;
}
