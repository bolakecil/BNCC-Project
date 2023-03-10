# Game Documentation

## Requirements
1. General:
   - Mini Game
2. Include:
   - Looping
   - Selection
   - Function
   - File I/O
   - Struct
3. Deadline:
   - 15 Maret 2023


## Description
- **Name**: Catch The Fruit!
- **Features:**
    - Main
      - *Basket*: Movable to left and right through left and right arrow key, upgradable up to 3 levels (where each upgrade increases basket base width by 1 block) to collect fruits which is considered claimed once hitting the basket base, initial level is given level 1
      - *Fruit*: Randomly spawned on top of the screen, falling from top-bottom screen, consisting of 3 kinds of fruits (Apple, Orange, Mango) with each possessing different attributes (weight, quality, ...), stored in struct
    - Additional
      - *Player Database*: Stores player's username, highscore, and basket level
      - *Game Guide*: Explains game mechanism, feature, and scoring system
      - Splash Screen / Loading Screen (?)
- **Mechanism**:
    - Player will be opted to choose:
      - Start a new game (inputting username, registering it into database, creating new account)
      - Load existing game (inputting username, validating it in database, loading account if existed)
      - View highscore (display username and highscore list)
      - Read game guide (viewing game guide on how to play)
      - Quit game (quit game)
- Each game will last with a 45 second countdown timer, and the score is recorded after the game ends.
- The game will also end when player has reached basket's maximum weight capacity.

## Contributors:
  - Jessica L
  - Axel N
