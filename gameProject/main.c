/*
*	�Ǳ����б� SWȰ������ ����2
*
*	��ǻ�Ͱ��к� ��ȣ�� (202011353)
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

/* �ܼ� �� */
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 7;
const int GRAY = 8;
const int DARK_GRAY = 15;

/* �ܾ��� */
const char* korean[20] = { "�̷��� ������ ���� �ٸ��ƴ� �� �ڽ�.", "����� ������ ����̿���.", 
						   "�Ա����� ���� �� �� �ٱ�.", "�װ��� �ʹ� ���ۼ�.", "����� �����ӿ��� ���ϼ��� ���.", 
						   "����� ������ü �����ε� ���߹޾� �����ϴ�.", "���������� �翬�� �� ���������� Ư���� ��.", 
						   "�λ��� ���νð� �����������.", "�� ���� �� �ϳ��� ������ �ʴ´ٴ� ��.",
						   "���ݴ� ���� ���� �� ���踦 ��ĥ�ϰ� �;�.", "����Ѵٸ� ��� �ϴ´ٸ� �װ� �ִٴ� ��.", 
						   "�����ϰ� �Ҵ� �ٶ�.", "Ȳ�ݺ� �� ���� �ٴ� �� �߰ſ� �¾�.", 
						   "ȸ������ ���� ���� Ǫ���� �ĵ��� �����.", "������ ������ ��." 
						   "�� ���� �� ������ �ʹ� �����ϰ� �ູ��!", "����� �����ؼ� ���� �Խ��ϴ�.",
						   "�ų��� �λ�, �ູ�� ����.", "�ΰ�ΰ� ������ �Ƹ��ٿ� �ʶ�� ��.",
						   "���� �� ������ ��ٸ��Կ�."};

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


/* ��� */
void gotoXY(int, int);
void setting();
void printBox(int, int, int, int, int);
void drawInformation(int, int, int, int);
int mainMenu();
int playGame(char);


/* �ֿܼ��� Ŀ���� ��ǥ�� (x, y)�� �̵� */
void gotoXY(int x, int y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


/* �����ͺ��̽� (������ ������ �ε� �� ����) */
int database(char type[20], int data) {
	static int LIMIT_TIME = 15;
	static int GOAL_SCORE = 60;
	static int BEST_SCORE = 0;

	// ���� �ð��� ��ȯ�ϴ� ���
	if (!strcmp(type, "returnTime")) {
		return LIMIT_TIME;
	}

	// ��ǥ ������ ��ȯ�ϴ� ���
	else if (!strcmp(type, "returnGoalScore")) {
		return GOAL_SCORE;
	}

	// ���� �ð��� �����ϴ� ���
	else if (!strcmp(type, "saveTime")) {
		LIMIT_TIME = data;
		return 0;
	}

	// ��ǥ ������ �����ϴ� ���
	else if (!strcmp(type, "saveGoalScore")) {
		GOAL_SCORE = data;
		return 0;
	}

	// Unexpected Exception
	else return -1;
}


/* ���� */
void setting() {
	char ch;
	int step = 0;
	int LIMIT_TIME = database("returnTime", 0), GOAL_SCORE = database("returnGoalScore", 0);

	system("cls");
	printBox(0, 0, 119, 29, WHITE);

	// �ȳ��� ���
	gotoXY(53, 5);
	printf("��          ��");

	gotoXY(3, 28);
	puts("* ����Ű�� ���� �����ϰ� ����ȭ������ ���ư��ϴ�.");
	gotoXY(66, 28);
	puts("* ����Ű ��, �� �� �̵� / ��, �� �� ���� �����մϴ�.");

	// ���� �ð� ���
	printBox(47, 10, 61, 12, WHITE);
	gotoXY(49, 11); printf(" ���� �ð�");

	printBox(62, 10, 72, 12, WHITE);
	gotoXY(66, 11); printf("%02dS", LIMIT_TIME);

	// ��ǥ ���� ���
	printBox(47, 14, 61, 16, WHITE);
	gotoXY(49, 15); printf(" ��ǥ ����");

	printBox(62, 14, 72, 16, WHITE);
	gotoXY(65, 15); printf("%03d��", GOAL_SCORE);

	gotoXY(44, 11); printf("��");
	gotoXY(75, 11); printf("��");

	while (1) {
		// Ŀ��
		if (step == 0) {
			gotoXY(44, 11); printf("��");
			gotoXY(75, 11); printf("��");
			gotoXY(44, 15); printf("  ");
			gotoXY(75, 15); printf("  ");
		}
		else if (step == 1) {
			gotoXY(44, 11); printf("  ");
			gotoXY(75, 11); printf("  ");
			gotoXY(44, 15); printf("��");
			gotoXY(75, 15); printf("��");
		}

		// ����Ű & ����Ű �Է¹���
		ch = _getch();
		// ���� ������ ����ȭ������
		if (ch == 13) return;
		// ����Ű
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
							gotoXY(65, 15); printf("%03d��", GOAL_SCORE);
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
							gotoXY(65, 15); printf("%03d��", GOAL_SCORE);
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


/* (x1, y1) ~ (x2, y2)�� �ڽ��� �׸��� �Լ� */
void printBox(int x1, int y1, int x2, int y2, int COLOR) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
	
	// ��� ���� (����������)
	gotoXY(x1, y1); printf("��");
	for (int i = 1; i < (x2 - x1) - 1; i++) printf("��"); 
	printf("��");

	// �߰� ���� (��   ��)
	for (int i = 1; i < (y2 - y1); i++) {
		gotoXY(x1, y1 + i); printf("��");
		gotoXY(x2 - 1, y1 + i); printf("��");
	}

	// �ϴ� ���� (����������)
	gotoXY(x1, y2); printf("��");
	for (int i = 1; i < (x2 - x1) - 1; i++) printf("��");
	printf("��");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}


/* Ÿ�� ���� ���� �� ��ܿ� ������ ǥ���ϴ� �Լ� */
void drawInformation(int wordType, int score, int leftTime, int goal) {
	
	// �ܾ��� ����
	gotoXY(7, 2);
	printf("�� �� �� : ");
	switch (wordType) {
		case 0: {
			printf("�ѱ�");
			break;
		}
		case 1: {
			printf("����");
			break;
		}
		case 2: {
			printf("����");
			break;
		}
	}

	// ����, ���ѽð�, ��ǥ ����
	gotoXY(37, 2); printf("�� �� �� �� : %2dS", leftTime);
	gotoXY(66, 2); printf("�� �� : %3d��", score);
	gotoXY(96, 2); printf("�� ǥ �� �� : %3d��", goal);
}


/* ���� ȭ�鿡�� �޴� ��� */
int mainMenu() {
	char c = 0, now = 0; 
	const int y[] = { 15, 17, 19, 22, 25 }; // �׸��� y��ǥ
	const int x1 = 51, x2 = 67; // �׸��� x��ǥ

	// ȭ�� ���
	printBox(0, 0, 119, 29, WHITE);
	gotoXY(53, 5); printf("Ÿ  ��  ��  ��");
	
	// �ϴ� �ȳ��� ���
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(3, 28); puts("* SWȰ�����л� ��ǻ�Ͱ��к� ��ȣ��");
	gotoXY(66, 28); puts("* ����Ű�� �̵�, ���ͷ� ����, ESC�� ���� �����ϼ���.");

	while (1) {
		// ȭ��ǥ ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		// �޴� ��� (���õ� �׸��� WHITE, �̼��� �׸��� GRAY)
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[0]); printf("��    ��");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[1]); printf("��    ��");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("��    ��"); printBox(46, 14, 73, 20, WHITE);

		if (now == 3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[3]); printf("��    ��"); printBox(46, 21, 73, 23, WHITE);

		if (now == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[4]); printf("��    ��"); printBox(46, 24, 73, 26, WHITE); puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		// ����ڰ� ����Ű�� �Է��ϸ� �޴��� ���õǵ��� ��
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
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}


/* Ÿ�� ���� ���� �Լ� */
int playGame(char type) {
	char input[100], answer[100]; // �Է��ϴ� ���ڿ�, ���� ���ڿ�
	int count = 0, randomV, len, KoOrEn; // ���� �� count, ����, ���� ���ڿ� ����

	int score = 0; // ������� ����(���� ����ŭ +)
	char ch, FLAG = 0; // ���� �÷���

	int START_TIME, LIMIT_TIME = database("returnTime", 0); // ���� �ð�
	int goal = database("returnGoalScore", 0); // ��ǥ ����

	// ���� ����
	srand((unsigned)time(NULL));
	randomV = rand() % 15;

	// ȭ�鿡 ���ڿ� ���
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
	
	// �Է� �ڽ� �����
	printBox(3, 26, 116, 28, WHITE);
	gotoXY(5, 27);
	printf("E N T E R : %50c", ' ');

	// ��� �������̼ǿ� �ڽ� ���
	printBox(3, 1, 116, 3, WHITE);
	drawInformation(type, score, LIMIT_TIME, goal);
	gotoXY(17, 27);

	// �Է°� ���� �迭 ����ֱ�
	for (int i = 0; i < 100; i++) input[i] = NULL;

	// �ð� ���� ����
	START_TIME = (int)time(0);

	// ���� �ݺ� ����
	while (1) {

		// �ð� üũ
		if ((int)time(0) == START_TIME + LIMIT_TIME) {
			FLAG = -1;
		}

		// Ű���� �Է� ������
		if (_kbhit()) {
			ch = _getch();

			// �齺���̽� ó��
			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					// ���� �Է°��� �����̽��� �� ĭ ����
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					// ����� �� ĭ ����
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					// �ѱ��̸� �� ĭ ����
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					// ����ڿ��� ���� �˷���
					// �� ġ�� ������ ���
					// Ʋ���� ġ�� ������ ����
					// ������ ������ �ʷ�
					if (!strcmp(input, answer)) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
					}
					if (strstr(answer, input) == NULL) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					}

					// ���ڿ� ��� ���� �ذ� ���� ����� ���ڿ� ��ü ���
					gotoXY(17, 27); printf("%60c", ' ');
					gotoXY(17, 27); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ���� ó��
			else if (ch == 13) {
				// ��ġ�ϸ� ����ó��
				if (!strcmp(input, answer)) {
					FLAG = 1;
				}
				// ��ġ���� ������ �ȳ�
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					gotoXY(48, 18);
					puts("* �߸� �Է��ϼ̽��ϴ� *");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					gotoXY(5, 27);
					printf("E N T E R : %98c", ' ');

					score -= 10;

					// �Է¹��� �迭 �ʱ�ȭ
					for (int i = 0; i < 100; i++) input[i] = NULL;

					// �Է��� ���� �����Ƿ� count ���� �ʱ�ȭ
					count = 0;

					gotoXY(17, 27);
				}
			}

			// ���� �Է� ó��
			else {
				// �ѱ��� 2Byte�̹Ƿ� �� ĭ�� �����Ѵ�. (������ ��쵵 ���� �� ĭ�� ����ȴ�.)
				input[count++] = ch;
				if (_kbhit()) {
					ch = _getch();
					input[count++] = ch;
					// �ѱ��� ��� �� ����Ʈ�� �Բ� ����ؾ� �Ѵ�.
					printf("%c", input[count - 2]);
				}
				printf("%c\b ", input[count - 1]);

				// ����ڿ��� ���� �˷���
				// �� ġ�� ������ ���
				// Ʋ���� ġ�� ������ ����
				// ������ ������ �ʷ�
				if (!strcmp(input, answer)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				}
				if (strstr(answer, input) == NULL) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				}

				// ���ڿ� ��� ���� �ذ� ���� ����� ���ڿ� ��ü ���
				gotoXY(17, 27); printf("%60c", ' ');
				gotoXY(17, 27); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
		}

		// FLAG�� -1�� ��� ���� ���� (�ð� �ʰ�)
		if (FLAG == -1) {
			char temp;
			system("cls");
			printBox(0, 0, 119, 29, WHITE);
			gotoXY(40, 3);
			puts("���� �ð� �� ������ �Է����� ���߽��ϴ�.");
			gotoXY(38, 5);
			puts("�ٽ� �õ��Ͻðڽ��ϱ�? (�� : Y / �ƴϿ� : N)");
			
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
		// FLAG�� 1�� ��� ������ ���� ���̹Ƿ� ���� �ʱ�ȭ
		else if (FLAG == 1) {
			// �Է� �ڽ� �����
			printBox(3, 26, 116, 28, WHITE);
			gotoXY(5, 27);
			printf("E N T E R : %98c", ' ');

			if (FLAG == 1) {
				// ���� ���̸�ŭ ������ �ο�(����� �׷���, �ѱ��� 2byte�̹Ƿ� 1/2��ŭ)
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

			// ���� ����
			randomV = rand() % 15;

			// ȭ�鿡 ���ڿ� ���
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

			// �Է¹��� �迭 �ʱ�ȭ
			for (int i = 0; i < 100; i++) input[i] = NULL;

			// �Է��� ���� �����Ƿ� count ���� �ʱ�ȭ
			count = 0;

			// ������Ʈ�� ������ ��� ���� ���
			drawInformation(type, score, LIMIT_TIME, goal);
			printBox(0, 0, 119, 29, WHITE);
			gotoXY(17, 27);

			// FLAG 0���� �ʱ�ȭ
			FLAG = 0;

			// �ð� ���� ����
			START_TIME = (int)time(0);

			// ��ǥ ���� ������ ����(�¸�)
			if (goal <= score) {
				char temp;
				system("cls");
				printBox(0, 0, 119, 29, WHITE);
				gotoXY(40, 3);
				printf("�����մϴ�! ��ǥ ���� %3d���� �޼��߽��ϴ�!", goal);
				gotoXY(38, 5);
				puts("�ٽ� �õ��Ͻðڽ��ϱ�? (�� : Y / �ƴϿ� : N)");

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


/* ���� �Լ� */
int main(int argc, char* argv[]) {
	char selectedMenu;
	char keep;

	// UI
	system("title Ÿ�� ����");
	system("mode con cols=120 lines=30");

	// ���� �ݺ�
	while (1) {
		system("cls");
		printBox(0, 0, 119, 29, WHITE);

		// �׸� ����
		selectedMenu = mainMenu();

		system("cls");
		printBox(0, 0, 119, 29, WHITE);

		switch (selectedMenu) {
			// ���α׷� ����
			case -1: {
				system("cls");
				gotoXY(50, 3);
				puts("���α׷��� �����մϴ�\n\n\n\n\n\n\n\n");
				return 0;
			}
			// Ÿ�� ���� ����
			case 0: case 1: case 2: {
				while (1) {
					keep = playGame(selectedMenu);
					if (keep != 1) break;
				}
				break;
			}
			// �ܾ��� ���
			case 3: {
				setting();
				break;
			}
			// ����
			case 4: {
				system("cls");
				gotoXY(50, 3);
				puts("���α׷��� �����մϴ�\n\n\n\n\n\n\n\n");
				return 0;
			}
		}
	}
}
