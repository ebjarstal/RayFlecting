#pragma once

#include <SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "constants.h"

class Ray {
private:
	SDL_Point origin, p1, p2;
	double angle;
	Uint8 r, g, b, a;
	SDL_Point CalculateCollisionPoint(
		const SDL_Point point_start, const double a, const SDL_Rect* obstacles, const int count) const;

	int nb_reflections;
	void CalculateReflection(
		const SDL_Point p1_start, SDL_Point* p2_end, double* r_a, SDL_Point* p1_prime,
		const SDL_Rect* obstacles, const int count) const;
public:
	Ray() : origin({0, 0}), p1({0, 0}), p2({0, 0}), angle(0), r(0), g(0), b(0), a(0), nb_reflections(0) {}

	Ray(SDL_Point o, SDL_Point p, int n) :
		origin(o), p1(p), p2({0, 0}),
		angle(std::atan2(o.y - p.y, p.x - o.x)),
		r(0xff), g(0xff), b(0xff), a(0xff),
		nb_reflections(n) {}

	Ray(SDL_Point o, SDL_Point p, int n, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
		origin(o), p1(p), p2({ 0, 0 }),
		angle(std::atan2(o.y - p.y, p.x - o.x)),
		r(red), g(green), b(blue), a(alpha),
		nb_reflections(n) {}

	void SetOrigin(const SDL_Point new_origin);
	void SetP1(const SDL_Point new_p1);
	void SetColor(const Uint8 new_r, const Uint8 new_g, const Uint8 new_b, const Uint8 new_a);
	void Draw(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
	void DrawReflections(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count);
	void AddReflection(const int n);
};
