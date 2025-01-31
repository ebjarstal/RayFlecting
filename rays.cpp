#include "rays.h"

SDL_Point Ray::CalculateCollisionPoint(const SDL_Point point_start, const SDL_Rect* obstacles, const int count) {
	SDL_Point point_collision = { -1, -1 };
	int distance = 0;
	bool x_ok = false, y_ok = false, collides = false;
	while (x_ok == false && y_ok == false && collides == false) {
		point_collision.x = p1.x + distance * std::cos(angle);
		point_collision.y = p1.y - distance * std::sin(angle);
		for (int i = 0; i < count; i++) {
			SDL_Rect pixel = { point_collision.x, point_collision.y, 1, 1 };
			if (SDL_HasIntersection(&obstacles[i], &pixel)) {
				collides = true;
			}
		}
		if (point_collision.x <= 0 || point_collision.x >= W_WIDTH) x_ok = true;
		if (point_collision.y <= 0 || point_collision.y >= W_HEIGHT) y_ok = true;
		distance++;
	}
	return point_collision;
}

void Ray::SetColor(const Uint8 new_r, const Uint8 new_g, const Uint8 new_b, const Uint8 new_a) {
	r = new_r; g = new_g; b = new_b; a = new_a;
}

void Ray::Draw(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count) {
	SDL_Point p2 = CalculateCollisionPoint(p1, obstacles, count);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}
