#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

SoundBuffer soundBuffer;
Sound sound;

const int width = 20;
const int height = 20;
const int tileSize = 30;
int x, y;
int fruitCordX, fruitCordY;
int playerScore;
int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
bool isGameOver;
int speed = 150;

enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir;

RenderWindow window(VideoMode(width * tileSize, height * tileSize), "Lets Play Snake Game");

void GameInit() {
	isGameOver = false;
	sDir = STOP;
	x = width / 2;
	y = height / 2;
	fruitCordX = rand() % width;
	fruitCordY = rand() % height;
	playerScore = 0;
	snakeTailLen = 0;
	window.display();
}

void GameRender() {
	window.clear();

	// Render Snake
	RectangleShape snakeSegment(Vector2f(tileSize, tileSize));
	snakeSegment.setFillColor(Color::Blue);
	snakeSegment.setPosition(x * tileSize, y * tileSize);
	window.draw(snakeSegment);

	// Render Food
	RectangleShape food(Vector2f(tileSize, tileSize));
	food.setFillColor(Color::Red);
	food.setPosition(fruitCordX * tileSize, fruitCordY * tileSize);
	window.draw(food);

	// Render Snake Tail
	for (int i = 0; i < snakeTailLen; i++) {
		snakeSegment.setPosition(snakeTailX[i] * tileSize, snakeTailY[i] * tileSize);
		window.draw(snakeSegment);
	}

	// Display Score
	Font font;
	font.loadFromFile("Capture_it.ttf");
	Text scoreText("Score: " + to_string(playerScore), font, 20);
	scoreText.setPosition(500, 0);
	window.draw(scoreText);

	window.display();
}

void UpdateGame() {
	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;

	for (int i = 1; i < snakeTailLen; i++) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (sDir) {
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
	}

	if (x >= width || x < 0 || y >= height || y < 0)
		isGameOver = true;

	for (int i = 0; i < snakeTailLen; i++) {
		if (snakeTailX[i] == x && snakeTailY[i] == y)
			isGameOver = true;
	}

	if (x == fruitCordX && y == fruitCordY) {
		sound.play();
		playerScore += 10;
		fruitCordX = rand() % width;
		fruitCordY = rand() % height;
		snakeTailLen++;
	}
}

void UserInput() {
	if (Keyboard::isKeyPressed(Keyboard::A)) sDir = LEFT;
	else if (Keyboard::isKeyPressed(Keyboard::D)) sDir = RIGHT;
	else if (Keyboard::isKeyPressed(Keyboard::W)) sDir = UP;
	else if (Keyboard::isKeyPressed(Keyboard::S)) sDir = DOWN;
	else if (Keyboard::isKeyPressed(Keyboard::X)) isGameOver = true;
}

void MainMenu() {
	Font font;
	font.loadFromFile("Capture_it.ttf");

	Text title("Snake Game", font, 50);
	title.setPosition(200, 150);
	title.setFillColor(Color::White);

	Text difficulty("Select Difficulty:", font, 30);
	difficulty.setPosition(200, 250);
	difficulty.setFillColor(Color::White);

	Text easy("1. Easy", font, 25);
	easy.setPosition(250, 300);
	easy.setFillColor(Color::White);

	Text medium("2. Medium", font, 25);
	medium.setPosition(250, 330);
	medium.setFillColor(Color::White);

	Text hard("3. Hard", font, 25);
	hard.setPosition(250, 360);
	hard.setFillColor(Color::White);

	window.clear();
	window.draw(title);
	window.draw(difficulty);
	window.draw(easy);
	window.draw(medium);
	window.draw(hard);
	window.display();

	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Num1) { speed = 150; return; }
				else if (event.key.code == Keyboard::Num2) { speed = 100; return; }
				else if (event.key.code == Keyboard::Num3) { speed = 50; return; }
			}
		}
	}
}

int main() {
	cout << "\nWhile playing use keys: A, W, D, S for movement and X to end game.\n";

	// Load sound once at start
	if (!soundBuffer.loadFromFile("eat.wav")) {
		cout << "❌ Error: Could not load 'eat.mp3'. Make sure the file is in the same folder.\n";
	} else {
		sound.setBuffer(soundBuffer);
		sound.setVolume(100);
	}

	MainMenu();
	GameInit();

	while (window.isOpen() && !isGameOver) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		UserInput();
		UpdateGame();
		GameRender();
		Sleep(speed);
	}

	while (window.isOpen() && isGameOver) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		Font gameOverFont;
		gameOverFont.loadFromFile("Capture_it.ttf");
		Text gameoverText("GAME OVER! ", gameOverFont, 50);
		gameoverText.setPosition(200, 200);
		window.draw(gameoverText);
		window.display();
		sleep(seconds(5));
		window.close();
	}
}
