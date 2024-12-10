#include "Timer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

const char* TTT[11] = {
    " 000 \n"
    "0   0\n"
    "0   0\n"
    "     \n"
    "0   0\n"
    "0   0\n"
    " 000 \n", // 0
    "     \n"
    "    0\n"
    "    0\n"
    "     \n"
    "    0\n"
    "    0\n"
    "     \n", // 1
    " 000 \n"
    "    0\n"
    "    0\n"
    " 000 \n"
    "0    \n"
    "0    \n"
    " 000 \n", // 2
    " 000 \n"
    "    0\n"
    "    0\n"
    " 000 \n"
    "    0\n"
    "    0\n"
    " 000 \n", // 3
    "     \n"
    "0   0\n"
    "0   0\n"
    " 000 \n"
    "    0\n"
    "    0\n"
    "     \n", // 4
    " 000 \n"
    "0    \n"
    "0    \n"
    " 000 \n"
    "    0\n"
    "    0\n"
    " 000 \n", // 5
    " 000 \n"
    "0    \n"
    "0    \n"
    " 000 \n"
    "0   0\n"
    "0   0\n"
    " 000 \n", // 6
    " 000 \n"
    "0   0\n"
    "0   0\n"
    "     \n"
    "    0\n"
    "    0\n"
    "     \n", // 7
    " 000 \n"
    "0   0\n"
    "0   0\n"
    " 000 \n"
    "0   0\n"
    "0   0\n"
    " 000 \n", // 8
    " 000 \n"
    "0   0\n"
    "0   0\n"
    " 000 \n"
    "    0\n"
    "    0\n"
    " 000 \n", // 9
    "     \n"
    "  0  \n"
    "     \n"
    "     \n"
    "     \n"
    "  0  \n"
    "     \n"  // :
};

Timer::Timer(int timeLimit, const string& question) : timeLimit(timeLimit), question(question), running(true) {}

void Timer::printDigitalTime(int tensMinutes, int onesMinutes, int tensSeconds, int onesSeconds) {
    for (int row = 0; row < 7; ++row) {
        int numbers[] = { tensMinutes, onesMinutes, 10, tensSeconds, onesSeconds };
        for (int num = 0; num < 5; ++num) {
            const char* digit = TTT[numbers[num]];
            for (int col = 0; col < 5; ++col) {
                cout << digit[row * 6 + col];
            }
            if (num < 4) cout << "  ";
        }
        cout << endl;
    }
}

void Timer::showTimer() {
    for (int i = timeLimit; i >= 0; --i) {
        if (!running) break;
        int print_min = i / 60;
        int print_sec = i % 60;
        int print_10_min = print_min / 10;
        int print_1_min = print_min % 10;
        int print_10_sec = print_sec / 10;
        int print_1_sec = print_sec % 10;

        system("cls");
        cout << "남은 시간:\n";
        printDigitalTime(print_10_min, print_1_min, print_10_sec, print_1_sec);

        cout << "\n문제: " << question << endl;
        this_thread::sleep_for(chrono::seconds(1));

        if (i == 0) { // timeLimit이 아니라 i가 0이 되었을 때 실행
            cout << "\n시간이 초과하였습니다.\n";
            for (int i = 3; i > 0; i--) {
                cout << i << "초 후 폭탄이 폭발합니다. ";
                this_thread::sleep_for(chrono::seconds(1));
                cout << "\r";
            }

            for (int i = 0; i < 15; i++) {
                system("cls");
                this_thread::sleep_for(chrono::milliseconds(100));
                if (i % 2 == 1) {
                    for (int i = 0; i < 15; i++) {
                        cout << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                    }
                }
                else if (i % 2 == 0) {
                    cout << "";
                }

            }
            cout <<
                " 000   000  00   00 00000    000  0   0 00000 0000 \n"
                "0     0   0 0 0 0 0 0       0   0 0   0 0     0   0\n"
                "0     0   0 0  0  0 0       0   0 0   0 0     0   0\n"
                "0 000 0 0 0 0     0 00000   0   0 0   0 00000 0000 \n"
                "0   0 00 00 0     0 0       0   0  0 0  0     0 0  \n"
                "0   0 0   0 0     0 0       0   0  0 0  0     0  0 \n"
                " 000  0   0 0     0 00000    000    0   00000 0   0\n";
            return;
        }
    }
    running = false;
}


void Timer::stopTimer() {
    running = false;
}
