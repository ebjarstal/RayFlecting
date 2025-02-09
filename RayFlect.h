#ifndef RAYFLECT_H
#define RAYFLECT_H

#include <SDL.h>
#include "lightsources.h"

class RayFlect {
public:
    RayFlect();
    ~RayFlect();

    bool Init();
    void Run();
    void Close();

private:
    SDL_Window* window;
    int width, height;
    SDL_Renderer* renderer;
    LightSource ls1;
    Ray r1;
    bool ls_or_r;
    SDL_Rect obstacles[3];
    bool is_running;

    void HandleEvents();
    void Render();
};

#endif // RAYFLECT_H