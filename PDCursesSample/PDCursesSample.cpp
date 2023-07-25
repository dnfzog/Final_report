// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//車両性能をみるプログラム
#include "Setting.h"
#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <iostream>

#define CHARBUFF 124
#define BUFFSIZE 1024
#define TIME 5000
#define OTHERDATA 4


//fpは読み込み用、fp2は書き込み用
FILE* fp, fp2;
char s[BUFFSIZE];
char s2[BUFFSIZE];
//double data[MONTHS][NUMDATA];

struct Data {
	double data[TIME][OTHERDATA];

};

void CSV2Array(const char* fileName, double data[TIME][OTHERDATA]);

void calAF(double data[TIME][OTHERDATA]);
void printGraphoutside();
void printGraph(double data[TIME][OTHERDATA]);
void printGraphsecond(double data[TIME][OTHERDATA]);
void printGraphthird(double data[TIME][OTHERDATA]);
void printGraphfourth(double data[TIME][OTHERDATA]);
void printKekka(double data[TIME][OTHERDATA]);
struct Data a;
struct Data b;
int x = 0;

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
	calAF(a.data);
	//int a[] = { 7,9,10,12,16,21,26,30,20,15,11,9 };
	//double a[] = { 7.0,9.0,10.0,12.0,16.0,21.0,26.0,30.0,20.0,15.0,11.0 ,9.0 };

	std::cout << "入力した整数から15秒間のデータを出力します\n ";
	std::cout << "0秒から4998秒までのデータしかありません\n";
	std::cout << "0から4998までで出力したい秒数を整数で入力してください\n";
	std::cout << "整数以外が入力された場合０秒からのデータが表示されます\n";
	std::cout << "範囲外の整数が入力された場合はデータが表示されません\n";
	std::cout << "整数を入力してください：";
	if (std::cin >> x) {
		std::cout << "入力した整数は " << x << " です。" << std::endl;

	}
	else {
		std::cout << "不正な入力です。" << std::endl;
	}



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

		else if (key == KEY_LEFT) {
			erase();
			printGraphoutside();
			printGraphthird(a.data);
		}
		else if (key == KEY_DOWN) {
			erase();
			printGraphoutside();
			printGraphfourth(a.data);
		}
		else if (key = KEY_UP) {
			erase();
			printKekka(a.data);
		}

		// 画面を更新
		refresh();



		// 0.5秒待機
		napms(500);
	}
	return 0;
}

void CSV2Array(const char* fileName, double data[TIME][OTHERDATA]) {
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
						printf("data[%d][%d]:%lf\n", j, i, data[j][i]);
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

void calAF(double data[TIME][OTHERDATA]) {
	int m;
	for (m = 0; m < TIME; m++) {
		data[m][3] = ((data[m][3] - 0.5) * 2.75) + 9;
	}
}
void printGraphoutside() {
	int i = 20;

	// 文字列を描く
	//mvaddstr(i, i, "Hello curses");
	mvprintw(i + 1, 13, "%d", x);
	mvprintw(i + 1, 18, "%d", x+1);
	mvprintw(i + 1, 23, "%d", x + 2);
	mvprintw(i + 1, 28, "%d", x + 3);
	mvprintw(i + 1, 33, "%d", x + 4);
	mvprintw(i + 1, 38, "%d", x + 5);
	mvprintw(i + 1, 43, "%d", x + 6);
	mvprintw(i + 1, 48, "%d", x + 7);
	mvprintw(i + 1, 53, "%d", x + 8);
	mvprintw(i + 1, 58, "%d", x + 9);
	mvprintw(i + 1, 63, "%d", x + 10);
	mvprintw(i + 1, 68, "%d", x + 11);
	mvprintw(i + 1, 73, "%d", x + 12);
	mvprintw(i + 1, 78, "%d", x + 13);
	mvprintw(i + 1, 83, "%d", x + 14);
	

	int z;
	for (z = 13; z < 85; z++) {
		mvaddstr(i, z, "_");
	}
	for (z = 5; z < 20; z++) {
		mvaddstr(z, 12, "|");

	}
	mvaddstr(i + 1, 85, "(経過時間)");

	mvaddstr(25, 7, "←水温グラフ");
	mvaddstr(25, 80, "スロットル開度グラフ→");
	mvaddstr(26, 42, "↓A/Fグラフ");
	mvaddstr(24, 42, "↑結果");


}

void printGraph(double data[TIME][OTHERDATA]) {
	int i = 20;
	int k, j;

	mvaddstr(20, 7, "0");
	mvaddstr(19, 7, "1000");
	mvaddstr(18, 7, "2000");
	mvaddstr(17, 7, "3000");
	mvaddstr(16, 7, "4000");
	mvaddstr(15, 7, "5000");
	mvaddstr(14, 7, "6000");
	mvaddstr(13, 7, "7000");
	mvaddstr(12, 7, "8000");
	mvaddstr(11, 7, "9000");
	mvaddstr(10, 6, "10000");
	mvaddstr(9, 6, "11000");
	mvaddstr(8, 6, "12000");
	mvaddstr(7, 6, "13000");
	mvaddstr(6, 6, "14000");
	mvaddstr(5, 6, "15000");
	mvaddstr(4, 9, "(rpm)");
	mvaddstr(2, 40, "RPM");

	//mvaddstr(27, 44, "↓");
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][0] / 1000); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}

void printGraphsecond(double data[TIME][OTHERDATA]) {
	int i = 20;
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
	mvaddstr(4, 9, "(tps)");
	mvaddstr(2, 40, "スロットル開度");


	int k, j;
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][1] / 10); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}

void printGraphthird(double data[TIME][OTHERDATA]) {
	int i = 20;
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
	mvaddstr(4, 9, "(度)");
	mvaddstr(2, 40, "水温");


	int k, j;
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][2] / 10); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}

void printGraphfourth(double data[TIME][OTHERDATA]) {
	int i = 20;
	mvaddstr(20, 11, "0");
	mvaddstr(19, 11, "5");
	mvaddstr(18, 10, "10");
	mvaddstr(17, 10, "15");
	mvaddstr(16, 10, "20");
	mvaddstr(15, 10, "25");
	mvaddstr(14, 10, "30");
	mvaddstr(13, 10, "35");
	mvaddstr(12, 10, "40");
	mvaddstr(11, 10, "45");
	mvaddstr(10, 10, "55");
	mvaddstr(9, 10, "60");
	mvaddstr(8, 10, "65");
	mvaddstr(7, 10, "70");
	mvaddstr(6, 10, "75");
	mvaddstr(5, 10, "80");
	mvaddstr(4, 9, "(度)");
	mvaddstr(2, 40, "A/F");


	int k, j;
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][3] / 5); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}


void printKekka(double data[TIME][OTHERDATA]) {
	int i = 20;

	mvaddstr(25, 7, "←水温グラフ");
	mvaddstr(25, 80, "スロットル開度グラフ→");
	mvaddstr(26, 42, "↓A/Fグラフ");
	mvaddstr(24, 42, "↑結果");

	mvaddstr(2, 40, "結果");


	int k, j;
	double count_AF = 0.0, count_wtp = 0.0, count_tps = 0.0, count_rpm = 0.0;
	for (k = x; k < x + 15; k++) {
		count_AF = count_AF + data[k][3];
		count_wtp = count_wtp + data[k][2];
		count_tps = count_tps + data[k][1];
		count_rpm = count_rpm + data[k][0];

	}
	double ave_AF = 0.0, ave_wtp = 0.0, ave_tps = 0.0, ave_rpm = 0.0;
	ave_AF = count_AF / 15;
	ave_wtp = count_wtp / 15;
	ave_tps = count_tps / 15;
	ave_rpm = count_rpm / 15;

	mvaddstr(5, 40, "選んだ秒数から15秒間の平均");
	mvprintw(6, 40, "回転数平均%lf", ave_rpm);
	mvprintw(7, 40, "アクセル開度平均%lf", ave_tps);
	mvprintw(8, 40, "水温平均%lf", ave_wtp);
	mvprintw(9, 40, "A/F平均%lf", ave_AF);

}