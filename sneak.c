#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
// Размеры игрового поля
#define WIDTH 80
#define HEIGHT 25
// Направления движения змейки
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
// Структура для координат
typedef struct {
    int x;
    int y;
} Point;

Point snake[100];       // Массив координат змейки
int length = 1;         // Длина змейки
int direction = RIGHT;  // Направление движения
Point food;             // Координаты еды
int score = 0;          // Счет

void init() {
    initscr();          
    clear();            
    noecho();           
    cbreak();           
    timeout(200);       // Задержка 
    curs_set(0);
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void draw() {
    clear();    

    for (int i = 0; i < WIDTH + 2; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT + 1, i, "#");
    }
    for (int i = 0; i < HEIGHT + 2; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH + 1, "#");
    }
    
    for (int i = 0; i < length; i++) {
        mvprintw(snake[i].y, snake[i].x, "o");
    }
    
    mvprintw(food.y, food.x, "*");
    mvprintw(HEIGHT + 3, 0, "Score: %d", score);
    refresh();
}

void input() {
    switch (getch()) {
        case 'w':
            if (direction != DOWN) {
                direction = UP;
            }
            break;
        case 's':
            if (direction != UP) {
                direction = DOWN;
            }
            break;
        case 'a':
            if (direction != RIGHT) {
                direction = LEFT;
            }
            break;
        case 'd':
            if (direction != LEFT) {
                direction = RIGHT;
            }
            break;
        case 'q':
            endwin();   
            exit(0);    
            break;
    }
}

void update() {
    for (int i = length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case UP:
            snake[0].y--;
            break;
        case DOWN:
            snake[0].y++;
            break;
        case LEFT:
            snake[0].x--;
            break;
        case RIGHT:
            snake[0].x++;
            break;
    }

    if (snake[0].x < 1 || snake[0].x > WIDTH || snake[0].y < 1 || snake[0].y > HEIGHT) {
        endwin();
        printf("Game Over! Score: %d\n", score);
        exit(0);
    }

    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            endwin();
            printf("Game Over! Score: %d\n", score);
            exit(0);
        }
    }

    if (snake[0].x == food.x && snake[0].y == food.y) {
        length++;
        score++;
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    }
}

void gameLoop() {
    while (true) {
        draw();     
        input();    
        update();   
    }
}
int main() {
    init();         
    gameLoop();     
    return 0;
}