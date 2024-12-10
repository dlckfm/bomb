#ifndef QUIZGAME_H
#define QUIZGAME_H

#include <string>
#include <vector>

class QuizGame {
public:
    QuizGame(int timeLimit);
    void start();

private:
    bool getInputWithinTime(std::string& userInput, const std::string& question);

    int timeLimit;
    int currentProblem;
    std::vector<std::pair<std::string, std::string>> problems;
};

#endif
