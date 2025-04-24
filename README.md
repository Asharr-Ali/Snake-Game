# Snake Game 🐍

This project is a classic **Snake Game** built using **C++**, developed as part of my Programming Fundamentals coursework. The game features real-time user interaction, keyboard controls, and basic game mechanics like food spawning, score tracking, and snake movement.

## 🎮 Game Controls

- Use **arrow keys** to move the snake (A, W, S, D).
- Eat the food to grow the snake and increase your score.
- Avoid crashing into the walls or yourself — or it's game over!

## 🛠️ How to Run

Make sure you have a C++ compiler installed. Then:

1. Clone the repository:

   ```bash
   git clone https://github.com/Asharr-Ali/Snake-Game.git

2. Run Following Commands to Link SFML Files

   ```bash
   g++ -c Snake_Game.cpp -I"C:\Users\Administrator\Desktop\Snake_Game\SFML\include"
   g++ Snake_Game.o -o Snake_Game -L"C:\Users\Administrator\Desktop\Snake_Game\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

3. Run Game

   ```bash
   .\Snake_Game
   
## 🤝 Contributions

We welcome contributions from the open-source community to improve and enhance the Snake Game!

## 📄 License

Snake Game is open-source software released under the MIT License.
