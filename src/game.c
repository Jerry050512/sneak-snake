#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "game.h"
#include "macros.h"
#include "utils.h"
#include "snake.h"
#include "stats.h"
#include "structs.h"

extern Config config;

void game_over(Map *map) {
    gotoxy(0, map->height+2);
    printf("Game Over! Your score is: %d\n", get_score_count());
    printf("AND Your STEP is: %d\n", get_step_count());
    press_space_to_continue();
}

int pause_and_exit(Map *map) {
	gotoxy(0, map->height+2);
    printf("Game paused, press 'q' again to quit.\n");
    printf("Press any key to resume.\n");
    while(!kbhit()) ;
    gotoxy(0, map->height+2);
    printf("                                     \n");
    printf("                        \n");
    if(getch() == 'q') return 1;
    return 0;
}

void playGame() {
    Snake snake;
    Point food;
    Map map;
    
    reset_score_count();
    reset_step_count();
    srand(time(NULL));
    initGame(&snake, &food, &map);

    while (1) {
        if (kbhit()) {
            if(updateDirection(&snake) && pause_and_exit(&map)) {
                game_over(&map);
                break;
            }
        }

        if (eatFood(&snake, &food, &map)) {
            increment_score_count();
        }
        moveSnake(&snake, &map);
        increment_step_count();
        if (checkCollision(&snake, &map)) {
            game_over(&map);
            break;
        }

        drawBoard(&snake, &food, &map);
        usleep(config.sleep_time); // 100 milliseconds
    }
}
