# MiniProject
ECE 362 Mini Project Fall 201

Contributers: Daryl D'Abbreo, Grant Julian, and Wesley Rich

Link for video https://imgur.com/a/93UD75n

This is our implementation of Nintendo Entertainment System (NES) style Tetris using an STM32 microcontroller. The display is an LED matrix board, interfaced using GPIO. We used an original NES controller to control the game, which also just used GPIO. High scores were saved using an EEPROM, interfaced using I2C. The EEPROM was useful for storing high scores through power cycles. We played music for the game using digital-to-analog conversion, playing notes from a database of frequencies we created.

Our first step was to learn how to program the LED matrix board. We had challenges utilizing the clock, causing inconsisties in the display. We created functions allowing us to draw simple shapes, and built a library of pieces needed for the game. Next we had to program the core of the game, including gravity, collision, and rotation for the game pieces, in addition to player score and difficulty selection. We worked on the controller next, allowing us to further test those game mechanics. We implemented music for the game that speeds up as the player progresses to higher levels. Songs were programmed into memory, pulling notes from a database of frequencies we had created. With some extra time we had at the end, we were able to implement a high score system and a main menu.
