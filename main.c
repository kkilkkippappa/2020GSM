#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>
#include<time.h>
#include<io.h>
#include<ctype.h>
#include<string.h>
// ���� ����� ���ϵ�
#include<MMSystem.h>
#pragma comment(lib, "winmm.lib")

void timeToString(struct tm* t);
void nextView(); //���� ȭ���� ��~~~ ����ϴ�
void head();	//���Ҹ� ����� �� ����
void First(int* i, int* hour, int* min); // 1��° ȭ���Դϴ�
void Second(int i, struct choose music[]);			// 2��° ȭ���Դϴ�
void Third(int i, int* hour, int* min, struct choose music[]);	//3��° ȭ���Դϴ�
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


//���� ȭ���� ����� ���� ȭ���� ��Ÿ�� ��
void nextView() {
	system("cls");
	Sleep(100);
}

//����
void head() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                       ������������������\n");
	printf("                       ��                              ��\n");
	printf("                       ��                              ��\n");
	printf("                       �� ----- ���Ҹ� �����~~ -----  ��\n");
	printf("                       ��                              ��\n");
	printf("                       ��                              ��\n");
	printf("                       ������������������\n");
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


//ù��° ȭ��(�ð� ���� ȭ��)
void First(int* i, int* hour, int* min) {
	char check; // yes ���� no ���� Ȯ���ϴ� ����
	head();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("1��° : �ð� ����  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("2��° : ���� ����  ");
	printf("3��° : �ð�\n");
	//���� �ð� ���� �˸�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("���� �ð��� �Է��� �ּ���\n");
	printf("ex)16:04  00:12  09:00\n");
	printf("�ִ� 50�� �Է� �����մϴ�.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	// �ð� ����
	do {
		printf("�ð� : ");
		printf(">> ");
		scanf("%d:%d", hour, min);
		// ��ũ�� �� ��ȯ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

		printf("<<%d��° �ð��� �ԷµǾ����ϴ�. (%d:%d)\n", (*i) + 1, *hour, *min);
		(*i)++;
		hour++;
		min++;
		// 50�� �Է¹����� 
		if ((*i) == 50) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("�ؽð� �Է��� �ʰ��Ǿ����ϴ�.\n");
			Sleep(1500);
			break;
		}
		// ������� ��ȯ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("<<�ð� �Է��� �����Ͻðڽ��ϱ�? (Yes-y | No-n)\n");
		getchar();
		printf(">> ");
		scanf("%c", &check);
		check = tolower(check);
	} while (check != 'y');
	nextView();
}

// �ι�° ȭ��(���� ����)
void Second(int i, struct choose music[]) {
	head();
	printf("1��° : �ð� ����  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //�����
	printf("2��° : ���� ����  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("3��° : �ð�\n\n");
	printf("�ð� �Է��� �������ϴ�.\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("������ �������ּ���\n");
	printf("���� �̸� �Է� ����) Bell\n");

	// ���� ���� ��� ǥ��
	struct _finddata_t fd;	// ���� ��� ǥ�� ����ü C:\Users\user\Desktop
	long handle;
	int result = 1;
	handle = _findfirst("D:\\BellMusic\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.
	int fnum = 1; // n��° ���� ��ȣ ǥ�� ����

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{	// 1, 2��°�� ��� ������ ����ִ��� ��Ÿ���� ǥ�ð� �����Ƿ� 3��°���Ͱ� BellMusic ������ �ִ� �����̴�. 

		printf("%d. File: %s\n", fnum++, fd.name);
		result = _findnext(handle, &fd);
	}
	_findclose(handle);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//���� ���� �̸� �Է�
	printf("���� ������ �������� ex) music.wav\n");

	for (int j = 0; j < i; j++) {
		printf("%d��° �ð� : ", j + 1);
		scanf("%s", music[j].music);
	}
	nextView();
}

void Third(int i, int* hour, int* min, struct choose music[]) {
	int t_num, muCheck, flag = 0; // ���� �ð��� �ʷ� �޴� ����, ���� Ȯ�� ����, ���� ���� Ȯ�� ����
	struct tm* t;   //�ð� ������ ����ü ���� ����
	time_t timer;
	head();
	printf("�ð� �Է��� �������ϴ�.\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	period(i, hour, min, music);
	while (1)
	{
		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
		t_num = t->tm_min + (t->tm_hour) * 60; //����ð��� �ʴ����� ���մϴ�.
		timeToString(t);	//����ð��� ǥ���մϴ�
		Sleep(200);
		system("cls");
		head();
		printf("1��° : �ð� ����  ");
		printf("2��° : ���� ����  ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //�����
		printf("3��° : �ð�  ");
		printf("���� ��� : D:/BellMusic/\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		period(i, hour, min, music);
		Sleep(550);

		// �ʰ� 0�̶�� flag�� �ʱ�ȭ�սô�
		if (t->tm_sec == 0)
			flag = 0;
		if (flag == 0) {
			for (int a = 0; a < i; a++) {

				// ���� ���� �ð��� (50���� ��� ��)������ �ð��밡 ���ٸ�
				if (t_num == (hour[a] * 60 + min[a])) {
					// ����
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					printf("�����մϴ�\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					muCheck = checkMusic(music, i, a); //�Է��� ���� ���� ������ ã�� �Լ�
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
					case 4: PlaySound(TEXT("D://BellMusic//���Ҹ�1.WAV"), NULL, SND_ASYNC);
						Sleep(10000);
						flag = 1;
						break;
					case 5: PlaySound(TEXT("D://BellMusic//���Ҹ�2.WAV"), NULL, SND_ASYNC);
						Sleep(10000);
						flag = 1;
						break;
					case -1: printf("���� ������ ã�� �� ���� ����� �� �����ϴ�.\n");
						break;
					}
				}
			}
		}
	}
}

void period(int i, int* hour, int* min, struct choose music[]) {
	int a;
	printf("����������������������������������������������������������������������������������������������������\n");
	for (a = 0; a < i; a++) {
		printf("��   %d. �ð� : %d�� %d��  ���� : %s\n", a + 1, *(hour), *min, music[a].music);
		hour++;
		min++;
	}
	printf("����������������������������������������������������������������������������������������������������\n");
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
	else if (strcmp(music[num].music, "���Ҹ�1") == 0)
		return 4;
	else if (strcmp(music[num].music, "���Ҹ�2") == 0)
		return 5;
	return -1;
}