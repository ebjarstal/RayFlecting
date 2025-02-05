#include "rays.h"

// TODO:
//       - Define CalculateP1Prime

void Ray::SetOrigin(const SDL_Point new_origin) {
	origin = new_origin;
}
void Ray::SetP1(const SDL_Point new_p1) {
	p1 = new_p1;
}

SDL_Point Ray::CalculateCollisionPoint(
	const SDL_Point point_start, const double a, const SDL_Rect* obstacles, const int count) const {

	SDL_Point point_collision = { -1, -1 };
	int distance = 0;
	bool x_ok = false, y_ok = false, collides = false;
	while (x_ok == false && y_ok == false && collides == false) {
		point_collision.x = point_start.x + distance * std::cos(a);
		point_collision.y = point_start.y - distance * std::sin(a);
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
	angle = std::atan2(origin.y - p1.y, p1.x - origin.x);
	p2 = CalculateCollisionPoint(p1, angle, obstacles, count);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);

	DrawReflections(renderer, obstacles, count);
}

void Ray::DrawReflections(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count) {
	SDL_Point p1_copy = p1;
	SDL_Point p2_copy = p2;
	for (int i = 0; i < nb_reflections; i++) {
		double reflection_angle;
		SDL_Point p1_prime = CalculateReflection(p1_copy, &p2_copy, &reflection_angle);
		SDL_Point collision_point = CalculateCollisionPoint(p2_copy, reflection_angle, obstacles, count);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderDrawLine(renderer, p2_copy.x, p2_copy.y, collision_point.x, collision_point.y);
		p1_copy = p2_copy;
		p2_copy = collision_point;
	}
}

SDL_Point Ray::CalculateReflection(const SDL_Point start_point, SDL_Point* end_point, double* r_a) const {
	SDL_Point p1_prime = start_point;
	if (end_point->x <= 0) {
		p1_prime.x = -p1_prime.x;
		*r_a = std::atan2(p1_prime.y - end_point->y, end_point->x - p1_prime.x);
		end_point->x = 1;
	}
	else if (end_point->x >= W_WIDTH) {
		p1_prime.x += 2 * (W_WIDTH - p1_prime.x);
		*r_a = std::atan2(p1_prime.y - end_point->y, end_point->x - p1_prime.x);
		end_point->x = W_WIDTH - 1;
	}
	else if (end_point->y <= 0) {
		p1_prime.y = -p1_prime.y;
		*r_a = std::atan2(p1_prime.y - end_point->y, end_point->x - p1_prime.x);
		end_point->y = 1;
	}
	else if (end_point->y >= W_HEIGHT) {
		p1_prime.y += 2 * (W_HEIGHT - p1_prime.y);
		*r_a = std::atan2(p1_prime.y - end_point->y, end_point->x - p1_prime.x);
		end_point->y = W_HEIGHT - 1;
	}
	return p1_prime;
}