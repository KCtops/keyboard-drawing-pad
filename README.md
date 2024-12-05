# Keyboard Drawing Pad

A simple drawing pad application built using SDL2. It allows users to draw on a 100x100 grid using a keyboard. You can move the pen around using the arrow keys and diagonally with `Q`, `E`, `Z`, and `C`, and change the brush size and color using the designated keys.

## Features

- **Keyboard Drawing**: Draw on a 100x100 grid using the keyboard.
- **Customizable Brush Size**: Change the size of the drawing brush.
- **Color Selection**: Choose from multiple colors for drawing.
- **Grid-Based Movement**: The pen moves based on the current brush size, allowing for precise control.

## Controls

- **W, A, S, D**: Move the cursor up, left, down, and right respectively.
- **Q, E, Z, C**: Diagonal movement (up-left, up-right, down-left, down-right).
- **Space**: Start drawing.
- **R**: Increase the brush size.
- **F**: Decrease the brush size.
- **1-8**: Select a drawing color.
  - `1`: Black
  - `2`: Blue
  - `3`: Green
  - `4`: Cyan
  - `5`: Red
  - `6`: Magenta
  - `7`: Yellow
  - `8`: White
- **X**: Clear the canvas (reset to white).
- **Escape**: Exit the application.

## Requirements

- **SDL2**: The application uses the SDL2 library for graphics and input handling.

## Building

### Prerequisites
Make sure you have the SDL2 library installed on your system. You can install it using the following commands:

#### On Ubuntu/Debian:
````sudo apt-get install libsdl2-dev````
#### On macOS (using Homebrew):
````brew install sdl2````
#### On Windows:
You can download the SDL2 development libraries from SDL2's official website and follow the installation instructions for Windows.

#### Compilation
Clone the repository and build the project using gcc or another C compiler:

````git clone https://github.com/KCtops/keyboard-drawing-pad.git````

````cd keyboard-drawing-pad````

````gcc -o drawing_pad main.c -lSDL2````
#### Running
Once compiled, you can run the application using:

````./drawing_pad````
## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements
This project uses the SDL2 library for graphics and event handling.
A big thanks to the SDL2 community for creating and maintaining such an amazing library.

## Contributing
Feel free to fork this project and submit issues or pull requests. Contributions are always welcome!

## Notes:
1. Replace `KCtops` with your actual GitHub username.
2. The instructions for installation and compilation may need to be updated depending on your platform or build setup.
3. You can modify the README further to fit additional requirements, such as specific dependencies or features added in future versions.

This README should provide a comprehensive overview for anyone visiting your project on GitHub. Let me know if you'd like any adjustments!
