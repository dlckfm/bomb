#include "QuizGame.h"
#include <iostream>

int main() {
    int timeLimit = 10;
    QuizGame game(timeLimit);
    game.start();
    return 0;
}
