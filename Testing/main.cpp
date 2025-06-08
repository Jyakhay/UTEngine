#include "Engine.hpp"

int main()
{
	if (!UTE::GEngine->Initialize())
	{
		return -1;
	}

	return 0;
}