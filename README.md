# Chess Engine

A C++ chess engine and simple graphical interface built with SDL2. The engine uses a bitboard representation and supports move generation, validation, and basic AI search.

## Table of Contents
- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Overview
This project aims to provide a functional chess engine along with an SDL2-based user interface. Key features include:
- Bitboard-based board representation for efficient move generation.
- Move validation that prevents illegal moves and checks for checkmate/stalemate.
- Optional AI player to play against the engine.
- Unit tests built with GoogleTest to ensure engine correctness.

## Prerequisites
Ensure the following dependencies are installed:
- **g++** with C++20 support
- **SDL2** and **SDL2_ttf** libraries
- **make** build tool
- **GoogleTest** (libgtest) for running tests

On Debian/Ubuntu based systems you can install these with:
```bash
sudo apt-get update
sudo apt-get install -y g++ make libsdl2-dev libsdl2-ttf-dev libgtest-dev
```

## Installation
Clone the repository and build the binaries:
```bash
git clone <repository-url>
cd Chess
make
```
This will build both the main application (`chess_app`) and the test suite (`chess_test`).

## Usage
Run the chess application:
```bash
./chess_app
```

Run the unit tests:
```bash
# Some environments require XDG_RUNTIME_DIR to be set for SDL
export XDG_RUNTIME_DIR=/tmp
./chess_test
```

## Project Structure
```
/
├── src/            # Source code for the engine and UI
├── include/        # Header files
├── test/           # GoogleTest unit tests
├── piece_images/   # Image assets for the GUI
├── Makefile        # Build configuration
└── README.md       # Project documentation
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the [GNU GPL v3](LICENSE).
