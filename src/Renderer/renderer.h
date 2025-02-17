#pragma once

#include "render_data.h"
#include "../mth.h"

#include <SDL3/SDL.h>
#include <string>

namespace Renderer {

	void Initialize();
	void ClearRenderQueue();
	void SubmitRenderData(RenderData data);
	void RenderFrame();
	void CleanUp();
	SDL_Renderer* GetRendererPointer();
	void BlitText(std::string text, int size, mth::vec2 loaction, SDL_Color color, bool backgroud);
	void DrawLine(float x1, float y1, float x2, float y2);

}