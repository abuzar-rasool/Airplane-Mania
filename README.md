# Airplane Mania 🛩️

A thrilling 2D action game built with C++ and SDL2 where you protect planes from flocks of birds using flare guns. Test your reflexes and aim in this fast-paced bird-dodging challenge!

## 🎮 Game Overview

Airplane Mania is an arcade-style game where birds continuously spawn and fly across the screen, threatening to collide with planes. Your mission is to shoot flare guns to scare away the birds and prevent collisions. The game features dynamic spawning, multiple bird types, score tracking, and a time-based challenge system.

**Click [here](https://www.youtube.com/watch?t=352&v=jriCK7UrAbY&feature=youtu.be) to watch gameplay video!**

## ✨ Features

- **Dynamic Spawning System**: Birds and planes spawn randomly every 5 seconds
- **Multiple Bird Types**: Three different bird species with unique behaviors and speeds
- **Flare Gun Mechanic**: Click to shoot flares and scare away birds
- **Collision Detection**: Realistic collision system between birds and planes
- **Score Tracking**: Earn points by protecting planes
- **Time Challenge**: 120-second gameplay sessions
- **Pause System**: Pause/resume gameplay anytime
- **Sound Effects**: Immersive audio including background music, bird sounds, and collision effects
- **Smooth Animations**: Sprite-based animations for all game objects

## 🎯 Game Controls

- **Left Mouse Click (bottom half of screen)**: Shoot flare gun
- **P Key**: Pause/Resume game
- **H Key**: Return to home menu (when paused)
- **Q Key**: Quit game (when paused)
- **Mouse Click on Menu**: Start or quit game from main menu

## 🛠️ Requirements

### Dependencies

- **SDL2**: Core multimedia library
- **SDL2_image**: Image loading library (PNG support)
- **SDL2_mixer**: Audio library for music and sound effects
- **SDL2_ttf**: TrueType font rendering library
- **C++ Compiler**: g++ or MinGW with C++11 support

## 📦 Installation

### Windows (MinGW)

1. **Install MinGW and SDL2 libraries**:
   - Download and install [MinGW](https://www.mingw-w64.org/)
   - Download SDL2 development libraries from [SDL website](https://www.libsdl.org/download-2.0.php)
   - Download SDL2_image, SDL2_mixer, and SDL2_ttf from their respective pages
   - Extract libraries to a directory (e.g., `C:\mingw_dev_lib`)

2. **Clone the repository**:
```bash
git clone https://github.com/abuzar-rasool/Airplane-Mania.git
cd Airplane-Mania
```

3. **Compile the game**:
```bash
g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o AirplaneMania
```

4. **Run the game**:
```bash
./AirplaneMania
```

### Linux

1. **Install SDL2 libraries**:
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

2. **Clone the repository**:
```bash
git clone https://github.com/abuzar-rasool/Airplane-Mania.git
cd Airplane-Mania
```

3. **Compile the game**:
```bash
g++ *.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o AirplaneMania
```

4. **Run the game**:
```bash
./AirplaneMania
```

## 📂 Project Structure

```
Airplane-Mania/
├── main.cpp              # Entry point of the application
├── game.cpp/hpp          # Core game logic and main game loop
├── bird.cpp/hpp          # Bird class with 3 bird type variants
├── plane.cpp/hpp         # Plane class and behavior
├── flare.cpp/hpp         # Flare gun projectile system
├── blast.cpp/hpp         # Explosion effects
├── flying_object.hpp     # Base class for all flying objects
├── unit.cpp/hpp          # Base unit class for game objects
├── menu.cpp/hpp          # Menu system
├── score.cpp/hpp         # Score tracking system
├── sound.cpp/hpp         # Sound manager
├── text.cpp/hpp          # Text rendering system
├── assets.png            # Sprite sheet with all game graphics
├── bg.jpg                # Background image
├── mainmenu.jpeg         # Main menu background
├── defaultFont.ttf       # Game font
└── *.wav                 # Sound effects and music files
```

## 🎲 Game Mechanics

### Scoring System
- Successfully protecting planes from birds increases your score
- Game tracks total birds spawned and your performance

### Bird Types
1. **Bird Type 1**: Medium speed, standard behavior
2. **Bird Type 2**: Faster movement, smaller size
3. **Bird Type 3**: Varied patterns, unique sprites

### Gameplay Flow
1. Game starts with a main menu
2. Click "Start Game" to begin
3. Birds and planes spawn every 5 seconds
4. Click on the bottom half of the screen to shoot flares
5. Flares scare away birds and prevent collisions
6. Game runs for 120 seconds
7. Final score is displayed at the end

## 🎨 Graphics

The game uses sprite-based animations with:
- 4-frame animation cycles for birds
- 4-frame animation cycles for planes
- 10-frame animation for flare effects
- Custom explosion animations for collisions

## 🔊 Audio

Sound effects include:
- Background music
- Bird spawning sounds
- Plane spawning sounds
- Flare gun shooting
- Bird collision screams
- Plane crash sounds
- Victory cheer
- Score notification

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests
- Improve documentation

## 📝 License

This project is open source and available for educational purposes.

## 👨‍💻 Author

Created by [Abuzar Rasool](https://github.com/abuzar-rasool)

---

**Enjoy the game and happy flying! ✈️🎮**
