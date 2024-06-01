# Cub3D

Welcome to **Cub3D**, an immersive 3D graphics project developed for the 42 school curriculum. This project brings the classic Wolfenstein 3D game to life using the power of raycasting. Prepare yourself for an exciting journey into the world of retro 3D graphics!

![Cub3D Gameplay](Cub3d.gif)

## Table of Contents
- [Cub3D](#cub3d)
	- [Table of Contents](#table-of-contents)
	- [Overview](#overview)
	- [Objectives](#objectives)
	- [Features](#features)
	- [Installation](#installation)
	- [Usage](#usage)
	- [Controls](#controls)
	- [Contributing](#contributing)
	- [License](#license)
	- [Acknowledgments](#acknowledgments)

## Overview

Cub3D is a raycasting project designed to create a simple yet effective 3D game environment. The game is inspired by the iconic Wolfenstein 3D, showcasing the fundamentals of 3D rendering from a 2D map. The project emphasizes low-level graphics programming, providing a deep dive into the mechanics of game engines and rendering techniques.

## Objectives

The main objectives of the Cub3D project are:
- To understand and implement the raycasting algorithm.
- To handle basic graphics rendering using the MinilibX library.
- To develop a simple game engine capable of rendering a 3D environment from a 2D map.
- To manage user inputs for interactive gameplay.
- To enhance problem-solving skills and proficiency in C programming.

## Features

Cub3D comes with a variety of features, including:
- **Raycasting**: Core algorithm for rendering 3D perspectives from 2D maps.
- **Textures**: Supports wall textures for a more immersive experience.
- **Basic Physics**: Collision detection to interact with the environment.
- **User Controls**: Smooth and responsive user interactions.

## Installation

To get started with Cub3D, follow these steps:

1. **Clone the repository**:
   ```sh
   git clone https://github.com/ebmarque/Cub3D.git
   cd cub3d

## Usage

After successful installation and building, you can run Cub3D with the following command:

2. **Inside the Cub3D directory run make**:
   ```sh
	make all
	
	"Run [make bonus] if you want to run the bonus version of this project."

3. **Run the executable with the map of you joice**:
	```sh
	./Cub3d [path to map]

	"Some examples of maps are provided inside the maps directory, ex.: maps/test.cub"
	
	"If you have compiled the bonus version the name of the executable will be [Cub3d_bonus]"

## Controls

- **W/A/S/D**: Move forward/left/backward/right.
- **Arrow Keys**: Look around.
- **E**: Interact with doors.
- **ENTER**: Display the mini-map.
- **LEFT MOUSE BUTTON**: Enable screen rotation with the mouse.
- **RIGHT MOUSE BUTTON**: Disable screen rotation with the mouse.
- **ESC**: Exit the game.

## Contributing

Contributions are welcome! If you have suggestions for improvements or want to report issues, feel free to open an issue or submit a pull request. Please ensure your contributions align with the project's objectives and coding standards.

## License

Cub3D is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for more details.


## Acknowledgments

- The 42 Network for providing this challenging and educational project.
- The developers of MinilibX for their essential graphics library.
- The pioneers of early 3D gaming, whose innovations continue to inspire us.

Embark on your journey into the world of Cub3D and experience the magic of 3D rendering from scratch. Happy coding!

