#pragma once

#include "render_data.h"
#include "../vec2.h"

#include <SDL3/SDL.h>
#include <string>

namespace Renderer {

	void Initialize();
	void ClearRenderQueue();
	void SubmitRenderData(RenderData data);
	void RenderFrame();
	void CleanUp();
	SDL_Renderer* GetRendererPointer();

	void BlitText(std::string text, int size, vec2 loaction, SDL_Color color, bool backgroud);

	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(vec2 p1, vec2 p2);

	void DrawRect(float x, float y, float w, float h, bool fill);
	void DrawRect(SDL_FRect rect, bool fill);
	
	void DrawPoint(float x, float y);
	void DrawPoint(vec2 point);

}