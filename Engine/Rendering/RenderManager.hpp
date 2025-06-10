#pragma once

#include "RenderingAPI.hpp"

namespace UTE
{
	class RenderManager
	{

	public:

		template<class T>
		static void InitializeAPI()
		{
			T* NewAPI = new T();
			mRenderingAPI = NewAPI;
		}

		static UTENGINE_API RenderingAPI* GetRenderingAPI();

	private:

		static inline UTENGINE_API RenderingAPI* mRenderingAPI = nullptr;

	};
}