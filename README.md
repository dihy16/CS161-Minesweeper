# Minesweeper Console-based Clone

## 3. User Guide:

![Game Board](minesweeper/report-img/image1.png)

### GAME CONTROLS ON ALL SCREENS

- Use the arrow keys (up, down, left, right) to navigate.
- Press Enter to select.
- Press ESC to exit.
- Press A to open a cell, press D to place a flag.

---

### Main Screen

Includes the following function keys:
- **New game**: Start a new game.
- **Resume game**: Resume a saved game.
- **Highscore**: View the highscore table.
- **Quit**: Exit the game, or you can exit using the ESC key.

![Main Menu](minesweeper/report-img/image2.png)

---

### NEW GAME

Use the up and down arrows to navigate, press Enter to select. A difficulty level selection screen will appear with 3 levels.

![Difficulty Selection](minesweeper/report-img/image3.png)

---

### CUSTOM MODE TO CREATE A MAP

- Enter the height, width, and number of bombs for the map.

![Custom Map](minesweeper/report-img/image4.png)

- If unreasonable input is entered (more bombs than size, or negative numbers), an error message will appear and prompt for re-entry.

![Invalid Input](minesweeper/report-img/image5.png)

- ESC cannot be used on this screen; you can only exit when entering a valid map.

---

### GAME PLAY SCREEN

- Controls: use the arrow keys to navigate, press A to open a cell, press D to place a flag.
- Displays the map size, number of bombs, the time elapsed since the start, and the game status, which will show "PLAYING" if the game is ongoing.
- The pointer is purple, and the initial position of the pointer is at the top-left cell.
- The position will vary for each game.
- The number of bombs will be updated: the bomb count decreases by 1 with each flag placed. If more flags are placed than there are bombs, the bomb count will display a negative number instead of 0.

![Game Board](minesweeper/report-img/image6.png)

- Pressing the ESC key will show a menu to save the game, with a return option to exit.
- Use the arrow keys to navigate, press Enter to select.
- If you choose to save the game, a message will appear: "Your game has been saved."

![Save Game](minesweeper/report-img/image7.png)

---

### RESUME GAME

Continue playing a saved game, with the time starting from the saved time.

![Resume Game](minesweeper/report-img/image8.png)

---

### WIN SCREEN

- Displays "YOU WON."
- If you reach a new highscore, it will display "YOU REACHED NEW HIGHSCORE."

![Win Screen](minesweeper/report-img/image9.png)

---

### LOSE SCREEN

- Displays the location of all the bombs, the correct flag placements, and the incorrect flag placements.
- Displays "YOU LOST."
- A menu will appear with two options: **New game** (start a new game) and **Return**.

![Lose Screen](minesweeper/report-img/image10.png)

---

### HIGHSCORE

Displays the top 3 fastest times: first, second, third.

![Highscore Screen](minesweeper/report-img/image11.png)
