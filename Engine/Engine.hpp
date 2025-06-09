#pragma once

namespace UTE
{

	class GameEngine
	{

	public:

		bool UTENGINE_API Initialize();

		void UTENGINE_API Update();

	private:

	};

	extern UTENGINE_API GameEngine* GEngine;

}