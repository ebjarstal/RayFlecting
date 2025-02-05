#include "lightsources.h"

const double LightSource::GetRadius() const {
	return radius;
}
void LightSource::SetRadius(const double new_radius) {
	if (new_radius > 1) radius = new_radius;
}

void LightSource::SetColor(const Uint8 new_r, const Uint8 new_g, const Uint8 new_b, const Uint8 new_a) {
	r = new_r; g = new_g; b = new_b; a = new_a;
}

void LightSource::Render(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count, const LS_TYPE type) {
	if (type == LS_CIRCLE) this->RenderCircle(renderer, obstacles, count);
	if (type == LS_FILL) this->RenderFill(renderer, obstacles, count);
}

void LightSource::RenderPixelsBySymmetry(SDL_Renderer* renderer, const int x, const int i, const int y, const int j) {
	SDL_Rect pixel = { x + i, y + j, 1, 1 };
	SDL_RenderFillRect(renderer, &pixel);
	pixel = { x - i, y + j, 1, 1 };
	SDL_RenderFillRect(renderer, &pixel);
	pixel = { x - i, y - j, 1, 1 };
	SDL_RenderFillRect(renderer, &pixel);
	pixel = { x + i, y - j, 1, 1 };
	SDL_RenderFillRect(renderer, &pixel);
}

void LightSource::RenderCircle(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	for (int i = 0; i < radius; i++) {
		for (int j = 0; j < radius; j++) {
			if (std::sqrt(std::pow(i, 2) + std::pow(j, 2)) < radius + 1 &&
				std::sqrt(std::pow(i, 2) + std::pow(j, 2)) > radius - 1) {
				RenderPixelsBySymmetry(renderer, x, i, y, j);
			}
		}
	}
	RenderRays(renderer, obstacles, count);
}

void LightSource::RenderFill(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect pixel = { -1, -1, 1, 1 };
	for (int i = 0; i < radius; i++) {
		for (int j = 0; j < radius; j++) {
			if (std::sqrt(std::pow(i, 2) + std::pow(j, 2)) <= radius) {
				RenderPixelsBySymmetry(renderer, x, i, y, j);
			}
		}
	}
	RenderRays(renderer, obstacles, count);
}

void LightSource::RenderRays(SDL_Renderer* renderer, const SDL_Rect* obstacles, const int count) {
	rays.clear();
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	double angle_increment = (double)2 * M_PI / nb_rays;
	SDL_Point origin = { x, y };

	for (int i = 0; i < nb_rays; i++) {
		SDL_Point p1 = { x + radius * std::cos(i * angle_increment), y - radius * std::sin(i * angle_increment) };
		Ray ray(origin, p1);
		ray.SetColor(r, g, b, a);
		ray.Draw(renderer, obstacles, count);
		rays.push_back(ray);
	}

}

void LightSource::Move(const int new_x, const int new_y) {
	x = new_x; y = new_y;
}
