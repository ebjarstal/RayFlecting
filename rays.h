#pragma once

#include <SDL.h>
#include <cmath>
#include <vector>
#include "constants.h"

class Ray {
private:
	SDL_Point origin, p1;
	double angle;
	Uint8 r, g, b, a;
	SDL_Point CalculateCollisionPoint(
		const SDL_Point point_start, const double a, const SDL_Rect* obstacles, const int count);
public:
	Ray(SDL_Point o, SDL_Point p) :
		origin(o), p1(p), angle(std::atan2(o.y - p.y, p.x - o.x)), r(0xff), g(0xff), b(0xff), a(0xff) {
	}

	Ray(SDL_Point o, SDL_Point p, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
		origin(o), p1(p), angle(std::atan2(o.y - p.y, p.x - o.x)), r(red), g(green), b(blue), a(alpha) {}

	void SetOrigin(const SDL_Point new_origin);
	void SetP1(const SDL_Point new_p1);
	void SetColor(const Uint8 new_r, const Uint8 new_g, const Uint8 new_b, const Uint8 new_a);
	void Draw(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
};
