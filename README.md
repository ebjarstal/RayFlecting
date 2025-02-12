# RayFlect

<p align="center">
  <img src="https://github.com/user-attachments/assets/deca477a-5e87-4b97-8ad8-050cc6406f0a" width="300">
  <img src="https://github.com/user-attachments/assets/b10f746b-006d-43c6-ae2a-0399fb51908d" width="300">
</p>

RayFlect is a graphical application that uses the SDL (Simple DirectMedia Layer) library to render and interact with light sources and rays. The application allows users to manipulate these objects through mouse and keyboard inputs.

## Features

- Display a light source or a single ray based on user input.
- Move the light source or ray using mouse clicks.
- Adjust the radius of the light source or the number of reflections of the ray using the mouse wheel.
- Handle various SDL events to manage user interactions.
- Render the current state of objects (light source, ray, and obstacles) to the window.

## Getting Started

### Prerequisites

- SDL2 library
- C++14 compatible compiler
- Visual Studio 2022 (or any other compatible IDE)

### Building the Project

1. Clone the repository:
```
  git clone https://github.com/ebjarstal/RayFlecting.git
```
2. Open the project in Visual Studio 2022.

3. Ensure that the SDL2 library is correctly set up in your project settings.

4. Build the project.

### Running the Application

1. Run the built executable.

2. A window titled "RayFlect (v0.1) - Press 'h' to show commands" will appear.

3. Follow the on-screen instructions to interact with the light source and ray.

## Usage

- Press `1` to display a light source.
- Press `2` to display a single ray.
- Use the left mouse button to move the light source or the starting point of the ray.
- Use the right mouse button to move the origin of the ray.
- Use the mouse wheel to change the radius of the light source or the number of reflections of the ray.
- Press `h` to show the help message box again.

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/ebjarstal/RayFlecting/blob/master/LICENSE.txt) file for details.

## Acknowledgments

- SDL2 library for providing the necessary tools to create this application.
- Visual Studio 2022 for the development environment.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
