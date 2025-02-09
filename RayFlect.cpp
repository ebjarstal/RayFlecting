#include "RayFlect.h"

RayFlect::RayFlect() : window(nullptr), width(0), height(0), renderer(nullptr), ls1(100, 100, 100, 200, 0xfd, 0xa5, 0x5c, 0xff),
r1({ 300, 300 }, { 400, 300 }, 2, 0xfd, 0xa5, 0x5c, 0xff), ls_or_r(0), is_running(true) {
    obstacles[0] = { 150, 100, 250, 80 };
    obstacles[1] = { 950, 200, 80, 300 };
    obstacles[2] = { 300, 400, 300, 30 };
}

RayFlect::~RayFlect() {
    Close();
}

// Allocate memory for window and renderer attributes, and set window title.
bool RayFlect::Init() {
    if (SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &window, &renderer) == -1) {
        std::cout << "FAIL: error creating the window and renderer\n";
        return false;
    }
    SDL_SetWindowTitle(window, "RayFlect (v0.1) - Press 'h' to show commands");
    return true;
}

// Run the application loop where events are handled and objects are rendered.
void RayFlect::Run() {

    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_INFORMATION,
        "How to use RayFlect",
        "Press '1' to display a lightsource, and '2' to display a single ray.\n\n"
        "Lightsource:\n"
        "   -Use left click to move it around\n"
        "   -Use mouse wheel to change its radius.\n\n"
        "Ray:\n"
        "   -Use left click to move the point at which it starts getting drawn.\n"
        "   -Use right click to move its origin.\n"
        "   -Use mouse wheel to change the amount of reflections.\n\n"
        "When RayFlect is running, press 'h' to show this message box again. Enjoy",
        window
    );

    while (is_running) {
        HandleEvents();
        Render();
    }
}

// Free allocated memory.
void RayFlect::Close() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

// Handle user inputs.
void RayFlect::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
        if (event.type == SDL_MOUSEMOTION) {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if (event.button.button == 1) {
                if (ls_or_r == 0) ls1.Move(mouse_x, mouse_y);
                else r1.SetP1({ mouse_x, mouse_y });
            }
            if (event.button.button == 4) {
                if (ls_or_r == 1) r1.SetOrigin({ mouse_x, mouse_y });
            }
        }
        if (event.type == SDL_MOUSEWHEEL) {
            if (ls_or_r == 0) ls1.SetRadius(ls1.GetRadius() + 3 * event.wheel.y);
            else r1.AddReflection(event.wheel.y);
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_1) {
                ls_or_r = 0;
            }
            if (event.key.keysym.sym == SDLK_2) {
                ls_or_r = 1;
            }
            if (event.key.keysym.sym == SDLK_h) {
                SDL_ShowSimpleMessageBox(
                    SDL_MESSAGEBOX_INFORMATION,
                    "How to use RayFlect",
                    "Press '1' to display a lightsource, and '2' to display a single ray.\n\n"
                    "Lightsource:\n"
                    "   -Use left click to move it around\n"
                    "   -Use mouse wheel to change its radius.\n\n"
                    "Ray:\n"
                    "   -Use left click to move the point at which it starts getting drawn.\n"
                    "   -Use right click to move its origin.\n"
                    "   -Use mouse wheel to change the amount of reflections.\n\n"
                    "When RayFlect is running, press 'h' to show this message box again. Enjoy",
                    window
                );
            }
        }
    }
}

// Render current state of objects to window.
void RayFlect::Render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    if (ls_or_r == 0) ls1.Render(renderer, obstacles, 3, LS_CIRCLE);
    else r1.Draw(renderer, obstacles, 3);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRects(renderer, obstacles, 3);

    SDL_RenderPresent(renderer);
}