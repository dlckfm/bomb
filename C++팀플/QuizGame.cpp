#include "QuizGame.h"
#include "Timer.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

QuizGame::QuizGame(int timeLimit) : timeLimit(timeLimit), currentProblem(0) {
    srand(time(0));
    problems = {
        {"���� E��ų�� ��Ȯ�� �̸���? \n1.��Ʋ��Ʋ������\n2.��Ʋ��Ʋ�帣�����\n3.������������\n4.�����յ帣�����"  , "3"},
        {"2023�� �� ���� ����� ������ ���ӻ��� ������? \n1.�ٷ� ����ũ \n2.�ߴ��� ����Ʈ 3 \n3.���� ������������ ���� \n4.Marvel's Spider-Man 2", "2"},
        {"���ϸ��� ���ϸ���DP ��Ʒ簡���ޱ�ƴ� ��� �ΰ�?", "4"},
        {"������ ��߸��� �Ѳ��� ��� ��ٸ���� ���� �ֳ��� ? ", "3"},
        {"Ű���ǿ��� �Ӹ��� ���� ���� � �ΰ���?", "5"},
        {"���۸��������� ������ �հ��� ������? ", "4"},
        {"�߷ζ�Ʈ����  ����� ������ ��ġ�ϴ� ����? \n1.��ī��-ȣ�� \n2.�Ϲ�-������ \n3.ü�ӹ�-�ε� \n4.������-�����", "1"},
        {"������ġ���� ���� ������ ������ �� �� ���ΰ�?? \n1.����-���� \n2.�Ƴ�-�Ķ� \n3.�긮����-�丣���", "3"},
        {"���� T1�� �ҼӵǾ� �ִ� ����Ŀ ������ ���� ù �°� 100��° ���� �Բ� �� è�Ǿ���? \n1.�����Ƴ� \n2.����� \n3.�Ƹ� \n4.������", "3"},
        {"������ġ���� �츮���� ������ ���� ������ �����ΰ�?", "Dva"},
    };
}

bool QuizGame::getInputWithinTime(string& userInput, const string& question) {
    Timer timer(timeLimit, question);
    thread timerThread(&Timer::showTimer, &timer);

    userInput.clear();
    char ch;
    while (timerThread.joinable()) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == '\r') {
                timer.stopTimer();
                break;
            }
            else if (ch == '\b') {
                if (!userInput.empty()) {
                    userInput.pop_back();
                    cout << "\b \b";
                }
            }
            else if (isprint(ch)) {
                userInput += ch;
                cout << ch;
            }
        }
    }

    timerThread.join();
    return !userInput.empty();
}

void QuizGame::start() {
    string userInput;
    while (currentProblem < problems.size()) {
        string question = problems[currentProblem].first;
        string answer = problems[currentProblem].second;

        if (getInputWithinTime(userInput, question)) {
            if (userInput == answer) {
                cout << "\n�����Դϴ�!\n";
                this_thread::sleep_for(chrono::seconds(1));
            }
            else {
                cout << "\nƲ�Ƚ��ϴ�. ������ " << answer << "�Դϴ�.\n";
                for (int i = 3; i > 0; i--) {
                    cout << i << "�� �� ��ź�� �����մϴ�. ";
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
                    " 000  0   0 0     0 00000    000    0   00000 0   0\n"
                    ;
                return;
            }
        }
        else {
            cout << "\n�ð� �ʰ� �Ǵ� �Է� ��ҵǾ����ϴ�. ������ " << answer << "�Դϴ�.\n";
            return;
        }

        currentProblem++;
    }

    cout << "\n��� ������ �ذ��ϼ̽��ϴ�! ��ź ��ü �Ϸ�!!\n";
}
