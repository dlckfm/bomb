#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <atomic>

class Timer {
public:
    Timer(int timeLimit, const std::string& question);
    void showTimer();
    void stopTimer();

private:
    int timeLimit;
    std::string question;
    std::atomic<bool> running;
    void printDigitalTime(int tensMinutes, int onesMinutes, int tensSeconds, int onesSeconds);
};

#endif
