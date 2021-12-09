#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>
#include<time.h>
#include<io.h>
#include<ctype.h>
#include<string.h>
// 음악 재생용 파일들
#include<MMSystem.h>
#pragma comment(lib, "winmm.lib")

void timeToString(struct tm* t);
void nextView(); //지금 화면을 싹~~~ 지웁니다
void head();	//종소리 울려라 의 제목
void First(int* i, int* hour, int* min); // 1번째 화면입니다
void Second(int i, struct choose music[]);			// 2번째 화면입니다
void Third(int i, int* hour, int* min, struct choose music[]);	//3번째 화면입니다
void period(int i, int* hour, int* min, struct choose music[]);
int checkMusic(struct choose music[], int i, int num);

struct choose {
	char music[100];
};

int main() {
	int i = 0;
	int hour[50] = { 0 }, min[50] = { 0 };
	struct choose music[55] = { "\0" };
	First(&i, hour, min);
	Second(i, music);
	Third(i, hour, min, music);
	return 0;
}


//현재 화면을 지우고 다음 화면을 나타낼 때
void nextView() {
	system("cls");
	Sleep(100);
}

//제목
void head() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                       ■■■■■■■■■■■■■■■■■\n");
	printf("                       ■                              ■\n");
	printf("                       ■                              ■\n");
	printf("                       ■ ----- 종소리 울려라~~ -----  ■\n");
	printf("                       ■                              ■\n");
	printf("                       ■                              ■\n");
	printf("                       ■■■■■■■■■■■■■■■■■\n");
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


//첫번째 화면(시간 선택 화면)
void First(int* i, int* hour, int* min) {
	char check; // yes 인지 no 인지 확인하는 변수
	head();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("1번째 : 시간 선택  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("2번째 : 음악 선택  ");
	printf("3번째 : 시계\n");
	//시종 시간 선택 알림
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("시종 시간을 입력해 주세요\n");
	printf("ex)16:04  00:12  09:00\n");
	printf("최대 50번 입력 가능합니다.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	// 시간 선택
	do {
		printf("시간 : ");
		printf(">> ");
		scanf("%d:%d", hour, min);
		// 핑크로 색 변환
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

		printf("<<%d번째 시간이 입력되었습니다. (%d:%d)\n", (*i) + 1, *hour, *min);
		(*i)++;
		hour++;
		min++;
		// 50번 입력받으면 
		if ((*i) == 50) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("※시간 입력이 초과되었습니다.\n");
			Sleep(1500);
			break;
		}
		// 흰색으로 변환
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("<<시간 입력을 종료하시겠습니까? (Yes-y | No-n)\n");
		getchar();
		printf(">> ");
		scanf("%c", &check);
		check = tolower(check);
	} while (check != 'y');
	nextView();
}

// 두번째 화면(음악 선택)
void Second(int i, struct choose music[]) {
	head();
	printf("1번째 : 시간 선택  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //노란색
	printf("2번째 : 음악 선택  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("3번째 : 시계\n\n");
	printf("시간 입력이 끝났습니다.\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("음악을 선택해주세요\n");
	printf("파일 이름 입력 예시) Bell\n");

	// 음악 파일 목록 표시
	struct _finddata_t fd;	// 파일 경로 표시 구조체 C:\Users\user\Desktop
	long handle;
	int result = 1;
	handle = _findfirst("D:\\BellMusic\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.
	int fnum = 1; // n번째 파일 번호 표시 변수

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{	// 1, 2번째는 어느 폴더에 담겨있는지 나타내는 표시가 있으므로 3번째부터가 BellMusic 폴더에 있는 파일이다. 

		printf("%d. File: %s\n", fnum++, fd.name);
		result = _findnext(handle, &fd);
	}
	_findclose(handle);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//음악 파일 이름 입력
	printf("음악 파일을 적으세요 ex) music.wav\n");

	for (int j = 0; j < i; j++) {
		printf("%d번째 시간 : ", j + 1);
		scanf("%s", music[j].music);
	}
	nextView();
}

void Third(int i, int* hour, int* min, struct choose music[]) {
	int t_num, muCheck, flag = 0; // 현재 시간을 초로 받는 변수, 음악 확인 변수, 음악 실행 확인 변수
	struct tm* t;   //시간 저장할 구조체 변수 선언
	time_t timer;
	head();
	printf("시간 입력이 끝났습니다.\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	period(i, hour, min, music);
	while (1)
	{
		timer = time(NULL);    // 현재 시각을 초 단위로 얻기
		t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
		t_num = t->tm_min + (t->tm_hour) * 60; //현재시간을 초단위로 구합니다.
		timeToString(t);	//현재시간을 표시합니다
		Sleep(200);
		system("cls");
		head();
		printf("1번째 : 시간 선택  ");
		printf("2번째 : 음악 선택  ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //노란색
		printf("3번째 : 시계  ");
		printf("파일 경로 : D:/BellMusic/\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		period(i, hour, min, music);
		Sleep(550);

		// 초가 0이라면 flag를 초기화합시다
		if (t->tm_sec == 0)
			flag = 0;
		if (flag == 0) {
			for (int a = 0; a < i; a++) {

				// 만약 현재 시간과 (50개의 목록 중)선택한 시간대가 같다면
				if (t_num == (hour[a] * 60 + min[a])) {
					// 실행
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					printf("실행합니다\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					muCheck = checkMusic(music, i, a); //입력한 값과 같은 음악을 찾는 함수
					switch (muCheck) {
					case 1: PlaySound(TEXT("D://BellMusic//APPLAUSE.WAV"), NULL, SND_ASYNC);
						Sleep(500);
						flag = 1;
						break;
					case 2: PlaySound(TEXT("D://BellMusic//ironman.WAV"), NULL, SND_ASYNC);
						Sleep(120000);
						flag = 1;
						break;
					case 3: PlaySound(TEXT("D://BellMusic//schoolmusic.WAV"), NULL, SND_ASYNC);
						Sleep(300000);
						flag = 1;
						break;
					case 4: PlaySound(TEXT("D://BellMusic//종소리1.WAV"), NULL, SND_ASYNC);
						Sleep(10000);
						flag = 1;
						break;
					case 5: PlaySound(TEXT("D://BellMusic//종소리2.WAV"), NULL, SND_ASYNC);
						Sleep(10000);
						flag = 1;
						break;
					case -1: printf("음악 파일을 찾을 수 없어 재생할 수 없습니다.\n");
						break;
					}
				}
			}
		}
	}
}

void period(int i, int* hour, int* min, struct choose music[]) {
	int a;
	printf("┌────────────────────────────────────────────────┐\n");
	for (a = 0; a < i; a++) {
		printf("│   %d. 시간 : %d시 %d분  음악 : %s\n", a + 1, *(hour), *min, music[a].music);
		hour++;
		min++;
	}
	printf("└────────────────────────────────────────────────┘\n");
}
void timeToString(struct tm* t) {
	printf("%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
	);
}

int checkMusic(struct choose music[], int i, int num) {
	if (strcmp(music[num].music, "APPLAUSE") == 0)
		return 1;
	else if (strcmp(music[num].music, "ironman") == 0)
		return 2;
	else if (strcmp(music[num].music, "schoolmusic") == 0)
		return 3;
	else if (strcmp(music[num].music, "종소리1") == 0)
		return 4;
	else if (strcmp(music[num].music, "종소리2") == 0)
		return 5;
	return -1;
}