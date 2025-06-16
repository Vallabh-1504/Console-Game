# 🐍 Snake Game – Windows Console (UTF-8)

A classic Snake Game built using C++ for the Windows command line interface. This game features real-time input handling, collision detection, progressive difficulty, and a visually polished experience using Unicode characters.

---

## 🔧 Features

- Smooth real-time movement using `W`, `A`, `S`, `D` keys.  
- Collision detection with walls and the snake's own body.  
- Food consumption and automatic growth.  
- Speed increases as the score goes up.  
- Replay option with a clean game-over screen.  
- Unicode-based design (UTF-8 enabled).  

---

## 🖥️ How It Works

- The snake is represented using an array of `Point` structures.  
- The food is randomly generated at an empty location on the board.  
- The screen is refreshed using `gotoxy()` to update positions without flickering.  
- The game speed increases after every 2 points for added difficulty.  

---

## 🧱 Controls

| Key | Action        |
|-----|---------------|
| W   | Move Up       |
| A   | Move Left     |
| S   | Move Down     |
| D   | Move Right    |

---

## ▶️ Compile & Run

```bash
g++ snake.cpp -o snake
./snake
```

✅ Ensure your terminal supports UTF-8 and you're on a Windows environment (uses `<windows.h>` and `<conio.h>`).

---

## 📂 File Structure

```
├── snake.cpp      # Main source code
├── README.md      # Project documentation
```

---

## 📊 Sample Gameplay Output

```
╔═══════════════════════════════════╗
║          SNAKE GAME               ║
║═══════════════════════════════════║
║   Controls:                       ║
║   ▸ Use W A S D to move           ║
║   ▸ Eat food to grow              ║
║   ▸ Avoid walls and yourself      ║
║═══════════════════════════════════║
║  Press any key to start..         ║
╚═══════════════════════════════════╝

```

---

## 🧠 Concepts Used

- Console cursor control with `gotoxy()`  
- Real-time input via `_kbhit()` and `_getch()`  
- Arrays and object-oriented design  
- Game loop mechanics and frame rendering  
- ASCII/UTF-8 terminal graphics  
