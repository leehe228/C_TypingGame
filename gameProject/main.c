/*
*	건국대학교 SW활동장학 과제2
*
*	컴퓨터공학부 이호은 (202011353)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <string.h>
#include <process.h>

/* 콘솔 색 */
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 7;
const int GRAY = 8;
const int DARK_GRAY = 15;

/* 단어장 */
const char* korean[20] = { "미래를 만들어가는 것은 다름아닌 나 자신.", "당신은 소중한 사람이에요.", 
						   "먹구름들 사이 빛 한 줄기.", "그것이 너무 슬퍼서.", "사람의 마음속에는 은하수가 산다.", 
						   "사람은 존재자체 만으로도 존중받아 마땅하다.", "누군가에겐 당연한 것 누군가에겐 특별한 것.", 
						   "인생은 눈부시고도 무용할지어다.", "저 작은 별 하나에 지나지 않는다는 것.",
						   "정반대 같은 보색 이 세계를 색칠하고 싶어.", "상상한다면 계속 믿는다면 네가 있다는 걸.", 
						   "따스하게 불던 바람.", "황금빛 모래 여름 바다 위 뜨거운 태양.", 
						   "회색빛깔 도시 위로 푸르른 파도가 쏟아져.", "순간은 영원이 돼." 
						   "나 지금 이 순간이 너무 감사하고 행복해!", "당신이 따뜻해서 봄이 왔습니다.",
						   "신나는 인생, 행복한 오늘.", "두고두고 볼수록 아름다운 너라는 꽃.",
						   "꽃이 필 때까지 기다릴게요."};

const char* english[20] = {"Dream as if you live forever, Live as if you'll die today.", "You only live once.",
						   "All the universe conspires in helping you to achieve it.", "Love is, above all else, the gift of oneself.",
						   "Wheresoever you go, go with all your heart.", "Better late than never.",
						   "Stay hungry, stay foolish.", "The real effort never betrays me.",
						   "Mistakes make you smarter.", "There is more to life than increasing its speed.",
						   "People fail forward to success.", "To win without risk is to triumph without glory.",
						   "It is the moment of decisions that your destiny is shaped.", "Where there is a will, there is a way.",
						   "No pain, no gain.", "Always do what you are afraid to do.",
						   "Life is a journey, not guided tour.", "Greed has no limits.",
						   "A loaf of bread is better than song of many birds.", "Life is full of ups and downs."};


/* 헤더 */
void gotoXY(int, int);
void setting();
void printBox(int, int, int, int, int);
void drawInformation(int, int, int, int);
int mainMenu();
int playGame(char);


/* 콘솔에서 커서의 좌표를 (x, y)로 이동 */
void gotoXY(int x, int y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


/* 데이터베이스 (설정의 값들을 로드 및 저장) */
int database(char type[20], int data) {
	static int LIMIT_TIME = 15;
	static int GOAL_SCORE = 60;
	static int BEST_SCORE = 0;

	// 제한 시간을 반환하는 명령
	if (!strcmp(type, "returnTime")) {
		return LIMIT_TIME;
	}

	// 목표 점수를 반환하는 명령
	else if (!strcmp(type, "returnGoalScore")) {
		return GOAL_SCORE;
	}

	// 제한 시간을 저장하는 명령
	else if (!strcmp(type, "saveTime")) {
		LIMIT_TIME = data;
		return 0;
	}

	// 목표 점수를 저장하는 명령
	else if (!strcmp(type, "saveGoalScore")) {
		GOAL_SCORE = data;
		return 0;
	}

	// Unexpected Exception
	else return -1;
}


/* 설정 */
void setting() {
	char ch;
	int step = 0;
	int LIMIT_TIME = database("returnTime", 0), GOAL_SCORE = database("returnGoalScore", 0);

	system("cls");
	printBox(0, 0, 119, 29, WHITE);

	// 안내문 출력
	gotoXY(53, 5);
	printf("설          정");

	gotoXY(3, 28);
	puts("* 엔터키를 눌러 저장하고 메인화면으로 돌아갑니다.");
	gotoXY(66, 28);
	puts("* 방향키 ↑, ↓ 로 이동 / ←, → 로 값을 조정합니다.");

	// 제한 시간 출력
	printBox(47, 10, 61, 12, WHITE);
	gotoXY(49, 11); printf(" 제한 시간");

	printBox(62, 10, 72, 12, WHITE);
	gotoXY(66, 11); printf("%02dS", LIMIT_TIME);

	// 목표 점수 출력
	printBox(47, 14, 61, 16, WHITE);
	gotoXY(49, 15); printf(" 목표 점수");

	printBox(62, 14, 72, 16, WHITE);
	gotoXY(65, 15); printf("%03d점", GOAL_SCORE);

	gotoXY(44, 11); printf("▒");
	gotoXY(75, 11); printf("▒");

	while (1) {
		// 커서
		if (step == 0) {
			gotoXY(44, 11); printf("▒");
			gotoXY(75, 11); printf("▒");
			gotoXY(44, 15); printf("  ");
			gotoXY(75, 15); printf("  ");
		}
		else if (step == 1) {
			gotoXY(44, 11); printf("  ");
			gotoXY(75, 11); printf("  ");
			gotoXY(44, 15); printf("▒");
			gotoXY(75, 15); printf("▒");
		}

		// 방향키 & 엔터키 입력받음
		ch = _getch();
		// 엔터 누르면 메인화면으로
		if (ch == 13) return;
		// 방향키
		else if (ch == 0x00 || 0xE0) ch = _getch();
		if (ch == 75 || ch == 77 || ch == 72 || ch == 80) {
			switch (ch) {
				/* LEFT (-) */
				case 75: {
					if (step == 0) {
						if (LIMIT_TIME > 5) {
							LIMIT_TIME -= 5;
							database("saveTime", LIMIT_TIME);
							gotoXY(66, 11); printf("%02dS", LIMIT_TIME);
						}
					}
					else if (step == 1) {
						if (GOAL_SCORE > 50) {
							GOAL_SCORE -= 5;
							database("saveGoalScore", GOAL_SCORE);
							gotoXY(65, 15); printf("%03d점", GOAL_SCORE);
						}
					}
					break;
				}
				/* RIGHT (+) */
				case 77: {
					if (step == 0) {
						if (LIMIT_TIME < 20) {
							LIMIT_TIME += 5;
							database("saveTime", LIMIT_TIME);
							gotoXY(66, 11); printf("%02dS", LIMIT_TIME);
						}
					}
					else if (step == 1) {
						if (GOAL_SCORE < 500) {
							GOAL_SCORE += 10;
							database("saveGoalScore", GOAL_SCORE);
							gotoXY(65, 15); printf("%03d점", GOAL_SCORE);
						}
					}
					break;
				}
				/* UP & DOWN */
				case 72: case 80: {
					if (step == 0) step = 1;
					else if (step == 1) step = 0;
				}
			}
		}
	}
}


/* (x1, y1) ~ (x2, y2)에 박스를 그리는 함수 */
void printBox(int x1, int y1, int x2, int y2, int COLOR) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
	
	// 상단 라인 (┌───┐)
	gotoXY(x1, y1); printf("┌");
	for (int i = 1; i < (x2 - x1) - 1; i++) printf("─"); 
	printf("┐");

	// 중간 라인 (│   │)
	for (int i = 1; i < (y2 - y1); i++) {
		gotoXY(x1, y1 + i); printf("│");
		gotoXY(x2 - 1, y1 + i); printf("│");
	}

	// 하단 라인 (└───┘)
	gotoXY(x1, y2); printf("└");
	for (int i = 1; i < (x2 - x1) - 1; i++) printf("─");
	printf("┘");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}


/* 타자 연습 실행 중 상단에 정보를 표시하는 함수 */
void drawInformation(int wordType, int score, int leftTime, int goal) {
	
	// 단어장 종류
	gotoXY(7, 2);
	printf("단 어 장 : ");
	switch (wordType) {
		case 0: {
			printf("한글");
			break;
		}
		case 1: {
			printf("영어");
			break;
		}
		case 2: {
			printf("랜덤");
			break;
		}
	}

	// 점수, 제한시간, 목표 점수
	gotoXY(37, 2); printf("제 한 시 간 : %2dS", leftTime);
	gotoXY(66, 2); printf("점 수 : %3d점", score);
	gotoXY(96, 2); printf("목 표 점 수 : %3d점", goal);
}


/* 메인 화면에서 메뉴 출력 */
int mainMenu() {
	char c = 0, now = 0; 
	const int y[] = { 15, 17, 19, 22, 25 }; // 항목의 y좌표
	const int x1 = 51, x2 = 67; // 항목의 x좌표

	// 화면 출력
	printBox(0, 0, 119, 29, WHITE);
	gotoXY(53, 5); printf("타  자  연  습");
	
	// 하단 안내문 출력
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(3, 28); puts("* SW활동장학생 컴퓨터공학부 이호은");
	gotoXY(66, 28); puts("* 방향키로 이동, 엔터로 선택, ESC를 눌러 종료하세요.");

	while (1) {
		// 화살표 출력
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("▒");
		gotoXY(x2, y[now]); printf("▒");
		
		// 메뉴 출력 (선택된 항목은 WHITE, 미선택 항목은 GRAY)
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[0]); printf("한    글");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[1]); printf("영    어");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("랜    덤"); printBox(46, 14, 73, 20, WHITE);

		if (now == 3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[3]); printf("설    정"); printBox(46, 21, 73, 23, WHITE);

		if (now == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[4]); printf("종    료"); printBox(46, 24, 73, 26, WHITE); puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		// 사용자가 방향키를 입력하면 메뉴가 선택되도록 함
		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 4;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 4) now++;
					else if (now == 4) now = 0;
					break;
				}
			}
			continue;
		}
		// 선택 혹은 종료
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}


/* 타자 연습 진행 함수 */
int playGame(char type) {
	char input[100], answer[100]; // 입력하는 문자열, 정답 문자열
	int count = 0, randomV, len, KoOrEn; // 글자 수 count, 난수, 정답 문자열 길이

	int score = 0; // 사용자의 점수(음절 수만큼 +)
	char ch, FLAG = 0; // 조건 플래그

	int START_TIME, LIMIT_TIME = database("returnTime", 0); // 제한 시간
	int goal = database("returnGoalScore", 0); // 목표 점수

	// 난수 생성
	srand((unsigned)time(NULL));
	randomV = rand() % 15;

	// 화면에 문자열 출력
	if (type == 0) {
		len = strlen(korean[randomV]);
		gotoXY(60 - len / 2, 15);
		printf("%s", korean[randomV]);
		strcpy(answer, korean[randomV]);
	}
	else if (type == 1) {
		len = strlen(english[randomV]);
		gotoXY(60 - len / 2, 15);
		printf("%s", english[randomV]);
		strcpy(answer, english[randomV]);
	}
	else if (type == 2) {
		KoOrEn = rand() % 2;
		if (KoOrEn == 0) {
			len = strlen(korean[randomV]);
			gotoXY(60 - len / 2, 15);
			printf("%s", korean[randomV]);
			strcpy(answer, korean[randomV]);
		}
		else {
			len = strlen(english[randomV]);
			gotoXY(60 - len / 2, 15);
			printf("%s", english[randomV]);
			strcpy(answer, english[randomV]);
		}
	}
	
	// 입력 박스 만들기
	printBox(3, 26, 116, 28, WHITE);
	gotoXY(5, 27);
	printf("E N T E R : %50c", ' ');

	// 상단 인포메이션용 박스 출력
	printBox(3, 1, 116, 3, WHITE);
	drawInformation(type, score, LIMIT_TIME, goal);
	gotoXY(17, 27);

	// 입력값 담을 배열 비워주기
	for (int i = 0; i < 100; i++) input[i] = NULL;

	// 시간 측정 시작
	START_TIME = (int)time(0);

	// 무한 반복 시작
	while (1) {

		// 시간 체크
		if ((int)time(0) == START_TIME + LIMIT_TIME) {
			FLAG = -1;
		}

		// 키보드 입력 받으면
		if (_kbhit()) {
			ch = _getch();

			// 백스페이스 처리
			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					// 이전 입력값이 스페이스면 한 칸 지움
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					// 영어면 한 칸 지움
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					// 한글이면 두 칸 지움
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					// 사용자에게 상태 알려줌
					// 잘 치고 있으면 흰색
					// 틀리게 치고 있으면 빨강
					// 완전히 맞으면 초록
					if (!strcmp(input, answer)) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
					}
					if (strstr(answer, input) == NULL) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					}

					// 문자열 출력 문제 해결 위해 지우고 문자열 자체 출력
					gotoXY(17, 27); printf("%60c", ' ');
					gotoXY(17, 27); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// 엔터 처리
			else if (ch == 13) {
				// 일치하면 정답처리
				if (!strcmp(input, answer)) {
					FLAG = 1;
				}
				// 일치하지 않으면 안내
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					gotoXY(48, 18);
					puts("* 잘못 입력하셨습니다 *");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					gotoXY(5, 27);
					printf("E N T E R : %98c", ' ');

					score -= 10;

					// 입력받을 배열 초기화
					for (int i = 0; i < 100; i++) input[i] = NULL;

					// 입력한 값이 없으므로 count 변수 초기화
					count = 0;

					gotoXY(17, 27);
				}
			}

			// 문자 입력 처리
			else {
				// 한글은 2Byte이므로 두 칸에 저장한다. (영어의 경우도 각각 한 칸에 저장된다.)
				input[count++] = ch;
				if (_kbhit()) {
					ch = _getch();
					input[count++] = ch;
					// 한글의 경우 두 바이트를 함께 출력해야 한다.
					printf("%c", input[count - 2]);
				}
				printf("%c\b ", input[count - 1]);

				// 사용자에게 상태 알려줌
				// 잘 치고 있으면 흰색
				// 틀리게 치고 있으면 빨강
				// 완전히 맞으면 초록
				if (!strcmp(input, answer)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				}
				if (strstr(answer, input) == NULL) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				}

				// 문자열 출력 문제 해결 위해 지우고 문자열 자체 출력
				gotoXY(17, 27); printf("%60c", ' ');
				gotoXY(17, 27); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
		}

		// FLAG가 -1인 경우 게임 종료 (시간 초과)
		if (FLAG == -1) {
			char temp;
			system("cls");
			printBox(0, 0, 119, 29, WHITE);
			gotoXY(40, 3);
			puts("제한 시간 내 문장을 입력하지 못했습니다.");
			gotoXY(38, 5);
			puts("다시 시도하시겠습니까? (예 : Y / 아니오 : N)");
			
			while (1) {
				temp = _getch();
				if (temp == 'Y' || temp == 'y') {
					system("cls");
					return 1;
				}
				else if (temp == 'N' || temp == 'n') {
					system("cls");
					return 0;
				}
			}
		}
		// FLAG가 1인 경우 정답을 맞춘 것이므로 상태 초기화
		else if (FLAG == 1) {
			// 입력 박스 만들기
			printBox(3, 26, 116, 28, WHITE);
			gotoXY(5, 27);
			printf("E N T E R : %98c", ' ');

			if (FLAG == 1) {
				// 문자 길이만큼 점수를 부여(영어는 그래도, 한글은 2byte이므로 1/2만큼)
				if (('Z' >= input[0] && input[0] >= 'A') || ('z' >= input[0] && input[0] >= 'a')) {
					score += strlen(input);
				}
				else {
					score += strlen(input) / 2;
				}
			}
			else if (FLAG == -2) {
				score -= 10;
			}
			
			gotoXY(1, 15);
			printf("%115c", ' ');

			gotoXY(1, 18);
			printf("%115c", ' ');

			// 난수 생성
			randomV = rand() % 15;

			// 화면에 문자열 출력
			if (type == 0) {
				len = strlen(korean[randomV]);
				gotoXY(60 - len / 2, 15);
				printf("%s", korean[randomV]);
				strcpy(answer, korean[randomV]);
			}
			else if (type == 1) {
				len = strlen(english[randomV]);
				gotoXY(60 - len / 2, 15);
				printf("%s", english[randomV]);
				strcpy(answer, english[randomV]);
			}
			else if (type == 2) {
				KoOrEn = rand() % 2;
				if (KoOrEn == 0) {
					len = strlen(korean[randomV]);
					gotoXY(60 - len / 2, 15);
					printf("%s", korean[randomV]);
					strcpy(answer, korean[randomV]);
				}
				else {
					len = strlen(english[randomV]);
					gotoXY(60 - len / 2, 15);
					printf("%s", english[randomV]);
					strcpy(answer, english[randomV]);
				}
			}

			// 입력받을 배열 초기화
			for (int i = 0; i < 100; i++) input[i] = NULL;

			// 입력한 값이 없으므로 count 변수 초기화
			count = 0;

			// 업데이트된 정보로 상단 정보 출력
			drawInformation(type, score, LIMIT_TIME, goal);
			printBox(0, 0, 119, 29, WHITE);
			gotoXY(17, 27);

			// FLAG 0으로 초기화
			FLAG = 0;

			// 시간 측정 시작
			START_TIME = (int)time(0);

			// 목표 점수 넘으면 종료(승리)
			if (goal <= score) {
				char temp;
				system("cls");
				printBox(0, 0, 119, 29, WHITE);
				gotoXY(40, 3);
				printf("축하합니다! 목표 점수 %3d점을 달성했습니다!", goal);
				gotoXY(38, 5);
				puts("다시 시도하시겠습니까? (예 : Y / 아니오 : N)");

				while (1) {
					temp = _getch();
					if (temp == 'Y' || temp == 'y') {
						system("cls");
						return 1;
					}
					else if (temp == 'N' || temp == 'n') {
						system("cls");
						return 0;
					}
				}
			}
		}
	}
}


/* 메인 함수 */
int main(int argc, char* argv[]) {
	char selectedMenu;
	char keep;

	// UI
	system("title 타자 연습");
	system("mode con cols=120 lines=30");

	// 무한 반복
	while (1) {
		system("cls");
		printBox(0, 0, 119, 29, WHITE);

		// 항목 선택
		selectedMenu = mainMenu();

		system("cls");
		printBox(0, 0, 119, 29, WHITE);

		switch (selectedMenu) {
			// 프로그램 종료
			case -1: {
				system("cls");
				gotoXY(50, 3);
				puts("프로그램을 종료합니다\n\n\n\n\n\n\n\n");
				return 0;
			}
			// 타자 연습 실행
			case 0: case 1: case 2: {
				while (1) {
					keep = playGame(selectedMenu);
					if (keep != 1) break;
				}
				break;
			}
			// 단어장 출력
			case 3: {
				setting();
				break;
			}
			// 설정
			case 4: {
				system("cls");
				gotoXY(50, 3);
				puts("프로그램을 종료합니다\n\n\n\n\n\n\n\n");
				return 0;
			}
		}
	}
}
