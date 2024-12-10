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
        {"조이 E스킬의 정확한 이름은? \n1.비틀비틀쿨쿨방울\n2.비틀비틀드르렁방울\n3.헤롱헤롱쿨쿨방울\n4.헤롱헤롱드르렁방울"  , "3"},
        {"2023년 더 게임 어워드 올해의 게임상의 주인은? \n1.앨런 웨이크 \n2.발더스 게이트 3 \n3.슈퍼 마리오브라더스 원더 \n4.Marvel's Spider-Man 2", "2"},
        {"포켓몬스터 포켓몬스터DP 디아루가·펄기아는 몇세대 인가?", "4"},
        {"육개장 사발면은 뚜껑에 몇분 기다리라고 적혀 있나요 ? ", "3"},
        {"키노피오의 머리에 빨간 점은 몇개 인가요?", "5"},
        {"슈퍼마리오에서 쿠파의 손가락 개수는? ", "4"},
        {"발로란트에서  요원과 국적이 일치하는 것은? \n1.스카이-호주 \n2.하버-프랑스 \n3.체임버-인도 \n4.사이퍼-모로코", "1"},
        {"오버워치에서 가족 관계인 영웅은 총 몇 쌍인가?? \n1.겐지-한조 \n2.아나-파라 \n3.브리기테-토르비욘", "3"},
        {"현재 T1에 소속되어 있는 페이커 선수의 월즈 첫 승과 100번째 승을 함께 한 챔피언은? \n1.오리아나 \n2.르블랑 \n3.아리 \n4.아지르", "3"},
        {"오버워치에서 우리나라 국적을 가진 영웅은 누구인가?", "Dva"},
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
                cout << "\n정답입니다!\n";
                this_thread::sleep_for(chrono::seconds(1));
            }
            else {
                cout << "\n틀렸습니다. 정답은 " << answer << "입니다.\n";
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
                    " 000  0   0 0     0 00000    000    0   00000 0   0\n"
                    ;
                return;
            }
        }
        else {
            cout << "\n시간 초과 또는 입력 취소되었습니다. 정답은 " << answer << "입니다.\n";
            return;
        }

        currentProblem++;
    }

    cout << "\n모든 문제를 해결하셨습니다! 폭탄 해체 완료!!\n";
}
