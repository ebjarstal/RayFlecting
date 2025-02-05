#pragma once

#include "constants.h"
#include "rays.h"

enum LS_TYPE {
	LS_CIRCLE,
	LS_FILL
};

class LightSource {
private:
	int x, y;
	double radius;
	Uint8 r, g, b, a;
	std::vector<Ray> rays;
	int nb_rays;
	void RenderPixelsBySymmetry(SDL_Renderer* renderer, const int x, const int i, const int y, const int j);
	void RenderCircle(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
	void RenderFill(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
	void RenderRays(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
public:
	LightSource(int x_init, int y_init, double rd_init, int n) :
		x(x_init), y(y_init), radius(rd_init), r(0xff), g(0xff), b(0xff), a(0xff), nb_rays(n) {
	}

	LightSource(int x_init, int y_init, double rd_init, int n, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
		x(x_init), y(y_init), radius(rd_init), r(red), g(green), b(blue), a(alpha), nb_rays(n) {
	}

	const double GetRadius() const;
	void SetRadius(const double new_radius);

	void SetColor(const Uint8 new_r, const Uint8 new_g, const Uint8 new_b, const Uint8 new_a);
	void Render(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count, const LS_TYPE type);
	void Move(const int new_x, const int new_y);
};
