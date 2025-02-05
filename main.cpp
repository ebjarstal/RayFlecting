#include <iostream>
#include "lightsources.h"

// TODO: - Change LightSource size with mouse wheel -> DONE
//       - Collisions with other shapes: create an abstract Obstacle class ?
//       - Fix Ray distribution ? -> start calculating line from origin instead of p1 ? then only draw once > p1

static void EndProgram(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	if (SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &window, &renderer) == -1) {
		std::cout << "FAIL: error creating the window and renderer\n";
		EndProgram(window, renderer);
		return 1;
	}

	// LightSource ls1(100, 100, 100, 100, 0xfd, 0xa5, 0x5c, 0xff);
	Ray r1({ 300, 300 }, { 400, 300 }, 0xfd, 0xa5, 0x5c, 0xff);

	SDL_Rect obstacle1{ 150, 100, 250, 80 };
	SDL_Rect obstacle2{ 950, 200, 80, 300 };
	SDL_Rect obstacle3{ 300, 400, 300, 30 };
	SDL_Rect obstacles[3] = { obstacle1, obstacle2, obstacle3 };

	bool is_running = true;
	while (is_running) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				is_running = false;
			}
			if (event.type == SDL_MOUSEMOTION) {
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				// ls1.Move(mouse_x, mouse_y);
				if (event.button.button == 1) {
					r1.SetP1({ mouse_x, mouse_y });
				}
				if (event.button.button == 4) {
					r1.SetOrigin({ mouse_x, mouse_y });
				}
			}
			if (event.type == SDL_MOUSEWHEEL) {
				// ls1.SetRadius(ls1.GetRadius() + 3*event.wheel.y);
			}
		}

		// RENDER OBJECTS ON SCREEN
		// ls1.Render(renderer, obstacles, 3, LS_CIRCLE);
		r1.Draw(renderer, obstacles, 3);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRects(renderer, obstacles, 3);

		SDL_RenderPresent(renderer);
	}

	EndProgram(window, renderer);
	return 0;
}