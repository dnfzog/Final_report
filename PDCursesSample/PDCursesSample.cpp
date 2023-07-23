// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//車両性能をみるプログラム
#include "Setting.h"
#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#define CHARBUFF 124
#define BUFFSIZE 1024
#define RPM 5000
#define OTHERDATA 4


//fpは読み込み用、fp2は書き込み用
FILE* fp, fp2;
char s[BUFFSIZE];
char s2[BUFFSIZE];
//double data[MONTHS][NUMDATA];

struct Data {
	double data[RPM][OTHERDATA];
	
};

void CSV2Array(const char* fileName, double data[RPM][OTHERDATA]);


void printGraphoutside();
void printGraph(double data[RPM][OTHERDATA]);
void printGraphsecond(double data[RPM][OTHERDATA]);
struct Data a;
struct Data b;

int main(int argc, char* argv[])
{
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "keyword1");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\Setting.ini", currentDirectory);
	char keyValue[CHARBUFF];

	//fprintf(stdout, "%s , %s\n", settingFile, readChar( section, keyWord,  "None", keyValue, settingFile));
	if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf(stdout, "%s , %s\n", settingFile, keyValue);
	}
	else {
		fprintf(stdout, "%s doesn't contain [$s] %s \n", settingFile, section, keyWord);
	}

	//ファイル読み込み
	CSV2Array(keyValue, a.data);
	//int a[] = { 7,9,10,12,16,21,26,30,20,15,11,9 };
	//double a[] = { 7.0,9.0,10.0,12.0,16.0,21.0,26.0,30.0,20.0,15.0,11.0 ,9.0 };

	// 初期化
	if (initscr() == NULL) {
		return 1;
	}
	
	while (true) {
		// 画面をクリア
		erase();
		printGraphoutside();
		printGraph(a.data);
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		int key = getch();

		
		if (key == KEY_RIGHT) {
			erase();
			printGraphoutside();
			printGraphsecond(a.data);
		}
		


		// 画面を更新
		refresh();



		// 1秒待機
		napms(1000);
	}
	return 0;
}

void CSV2Array(const char* fileName, double data[RPM][OTHERDATA]) {
	char* p;
	int j = 0;
	int n = 0;

	errno_t error;
	error = fopen_s(&fp, fileName, "r");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		char* token;
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			if (n != 0) {
				int i = 0;
				p = strtok_s(s, ",", &token);
				while (p != NULL) {

					//分離後の文字列を表示 
					//printf("分離後の文字列：%s\n", token);

					//文字列を分離 
					p = strtok_s(NULL, ",", &token);
					if (i < 4) {

						double tmp = atof(p);
						data[j][i] = tmp;
						printf("data[%d][%d]降水量:%lf\n", j, i, data[j][i]);
					}
					i++;
				}
				j++;



			}
			n++;
		}
		fclose(fp);
	}
}

void printGraphoutside() {
	int i = 20;

	// 文字列を描く
	//mvaddstr(i, i, "Hello curses");
	mvaddstr(i + 1, 13, "5");
	mvaddstr(i + 1, 18, "6");
	mvaddstr(i + 1, 23, "7");
	mvaddstr(i + 1, 28, "8");
	mvaddstr(i + 1, 33, "9");
	mvaddstr(i + 1, 38, "10");
	mvaddstr(i + 1, 43, "11");
	mvaddstr(i + 1, 48, "12");
	mvaddstr(i + 1, 53, "1");
	mvaddstr(i + 1, 58, "2");
	mvaddstr(i + 1, 63, "3");
	mvaddstr(i + 1, 68, "4");
	int z;
	for (z = 13; z < 70; z++) {
		mvaddstr(i, z, "_");
	}
	for (z = 5; z < 20; z++) {
		mvaddstr(z, 12, "|");

	}
	mvaddstr(i + 1, 73, "(月)");
	//i++;
	mvaddstr(20, 10, "0");
	mvaddstr(19, 10, "10");
	mvaddstr(18, 10, "20");
	mvaddstr(17, 10, "30");
	mvaddstr(16, 10, "40");
	mvaddstr(15, 10, "50");
	mvaddstr(14, 10, "60");
	mvaddstr(13, 10, "70");
	mvaddstr(12, 10, "80");
	mvaddstr(11, 10, "90");
	mvaddstr(10, 9, "100");
	mvaddstr(9, 9, "110");
	mvaddstr(8, 9, "120");
	mvaddstr(7, 9, "130");
	mvaddstr(6, 9, "140");
	mvaddstr(5, 9, "150");
	mvaddstr(4, 9, "降水量(mm)");
	mvaddstr(2, 35, "降水量平均");
	
}

void printGraph(double data[RPM][OTHERDATA]) {
	int i = 20;
	int k, j;
	mvaddstr(1, 30, "2021年5月-2022年4月");
	for (k = 0; k < 12; k++) {
		for (j = 0; j < (data[k][0] / 1000); j++) {
			mvaddstr(i - (j + 1), 13 + (k * 5), "*");
		}

	}
}

void printGraphsecond(double data[RPM][OTHERDATA]) {
	int i = 20;

	
	
	mvaddstr(1, 30, "2022年5月-2023年4月");
	int k, j;
	for (k = 24; k < 36; k++) {
		for (j = 0; j < (data[k][0] / 1000); j++) {
			mvaddstr(i - (j + 1), 13 + ((k-24) * 5), "*");
		}

	}
}