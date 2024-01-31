# Ping Pong Game using ATmega32

https://github.com/Basem0/Atmega32/assets/126205898/d0895b03-c1a1-40e5-a5eb-8d4d32350a64

## Introduction
This project implements a simple ping pong game on an ATmega32 microcontroller. The game is displayed on a 4x20 LCD screen and utilizes two external buttons for user interaction. The game logic is handled using interrupts for efficient and responsive gameplay.

## Hardware Requirements
- ATmega32 microcontroller
- 4x20 LCD screen
- Two external buttons for player input
- Necessary resistors, capacitors, and other supporting components

## Software Requirements
- AVR-GCC compiler
- AVR Studio or Atmel Studio for development
- Appropriate drivers and libraries for ATmega32 microcontroller

## Game Description
The ping pong game involves two players controlling rockets (represented by graphical symbols) to hit a moving ball across the LCD screen. The ball moves vertically and horizontally, bouncing off the walls and rockets.

### Game Rules
- Each player controls one rocket using the external buttons.
- The ball moves automatically and bounces off the walls and rockets.
- If the ball hits the opponent's wall, the opposing player scores a point.
- The game ends when one player reaches a predefined score or time limit.

## Implementation Details
- The game logic is implemented in C programming language using AVR-GCC compiler.
- Interrupts are used to handle user input from the external buttons for responsive gameplay.
- The LCD screen displays the game environment, including the rockets, ball, and score.

## Setup and Configuration
1. Connect the ATmega32 microcontroller to the LCD screen and external buttons as per the hardware schematic.
2. Compile the C code using AVR-GCC compiler and flash the binary onto the ATmega32 microcontroller.
3. Power on the system and start playing the ping pong game using the external buttons.

## Future Improvements
- Implement additional game features such as power-ups, multiple levels, or multiplayer mode.
- Optimize the code for better performance and resource utilization.
- Add sound effects or music to enhance the gaming experience.

## Contributing
We welcome contributions! If you'd like to contribute to this project, please fork the repository and submit a pull request.

## Links
- [ALL DRIVERS](https://github.com/Basem0/Atmega32/tree/main/Drivers)

## Contributors
- [AHMED BASEM](https://github.com/Basem0/)
- [LinkedIn](https://www.linkedin.com/in/ahmed-basem-988529272/)
  
