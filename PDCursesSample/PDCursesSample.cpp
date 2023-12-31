﻿// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//車両の計測結果をみるプログラム
//選んだ秒数から15秒間分の計測結果をみることができる
#include "Setting.h"
#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#define CHARBUFF 124
#define BUFFSIZE 1024
#define TIME 5000
#define OTHERDATA 4


//fpは読み込み用
FILE* fp;
char s[BUFFSIZE];
char s2[BUFFSIZE];


//構造体
struct Data {
	double data[TIME][OTHERDATA];

};

//関数
void CSV2Array(const char* fileName, double data[TIME][OTHERDATA]);
void printGraphoutside();
void printGraph(double data[TIME][OTHERDATA]);
void printGraphsecond(double data[TIME][OTHERDATA]);
void printGraphthird(double data[TIME][OTHERDATA]);
void printGraphfourth(double data[TIME][OTHERDATA]);
void printKekka(double data[TIME][OTHERDATA]);
void fileout(double data[TIME][OTHERDATA]);

//宣言
struct Data a;
int x = 0;

int main(int argc, char* argv[])
{
	//ファイル名読み込み
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
	
	//整数の入力
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

	//ファイル出力
	fileout(a.data);

	// 初期化
	if (initscr() == NULL) {
		return 1;
	}

	while (true) {
		// 画面をクリア
		erase();
		//グラフ外形
		printGraphoutside();
		//回転数グラフ
		printGraph(a.data);

		//キー判定
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		int key = getch();

		//→
		if (key == KEY_RIGHT) {
			erase();
			printGraphoutside();
			//tpsグラフ
			printGraphsecond(a.data);
		}
		//←
		else if (key == KEY_LEFT) {
			erase();
			printGraphoutside();
			//水温グラフ
			printGraphthird(a.data);
		}
		//↓
		else if (key == KEY_DOWN) {
			erase();
			printGraphoutside();
			//A/Fグラフ
			printGraphfourth(a.data);
		}
		//↑
		else if (key == KEY_UP) {
			erase();
			//結果
			printKekka(a.data);
		}

		// 画面を更新
		refresh();



		// 0.5秒待機
		napms(500);
	}
	return 0;
}

//ファイル読み込み
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
					

					//文字列を分離 
					p = strtok_s(NULL, ",", &token);
					if (i < 4) {

						double tmp = atof(p);
						data[j][i] = tmp;
						//printf("data[%d][%d]:%lf\n", j, i, data[j][i]);
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

//グラフ外形
void printGraphoutside() {
	int i = 20;

	// 文字列を描く
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
	mvaddstr(i + 1, 88, "(経過時間)");

	mvaddstr(25, 7, "←水温グラフ");
	mvaddstr(25, 80, "スロットル開度グラフ→");
	mvaddstr(26, 42, "↓A/Fグラフ");
	mvaddstr(24, 42, "↑結果");


}

//回転数グラフ
void printGraph(double data[TIME][OTHERDATA]) {
	int i = 20;
	int k, j;

	mvaddstr(20, 11, "0");
	mvaddstr(19, 8, "1000");
	mvaddstr(18, 8, "2000");
	mvaddstr(17, 8, "3000");
	mvaddstr(16, 8, "4000");
	mvaddstr(15, 8, "5000");
	mvaddstr(14, 8, "6000");
	mvaddstr(13, 8, "7000");
	mvaddstr(12, 8, "8000");
	mvaddstr(11, 8, "9000");
	mvaddstr(10, 7, "10000");
	mvaddstr(9, 7, "11000");
	mvaddstr(8, 7, "12000");
	mvaddstr(7, 7, "13000");
	mvaddstr(6, 7, "14000");
	mvaddstr(5, 7, "15000");
	mvaddstr(4, 9, "(rpm)");
	mvaddstr(2, 40, "RPM");

	//mvaddstr(27, 44, "↓");
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][0] / 1000); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}

//tpsグラフ
void printGraphsecond(double data[TIME][OTHERDATA]) {
	int i = 20;
	mvaddstr(20, 11, "0");
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

//水温グラフ
void printGraphthird(double data[TIME][OTHERDATA]) {
	int i = 20;
	mvaddstr(20, 11, "0");
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

//A/Fグラフ
void printGraphfourth(double data[TIME][OTHERDATA]) {
	int i = 20;
	mvaddstr(20, 11, "0");
	mvaddstr(19, 11, "2");
	mvaddstr(18, 11, "4");
	mvaddstr(17, 11, "6");
	mvaddstr(16, 11, "8");
	mvaddstr(15, 10, "10");
	mvaddstr(14, 10, "12");
	mvaddstr(13, 10, "14");
	mvaddstr(12, 10, "16");
	mvaddstr(11, 10, "18");
	mvaddstr(10, 10, "20");
	mvaddstr(9, 10, "22");
	mvaddstr(8, 10, "24");
	mvaddstr(7, 10, "26");
	mvaddstr(6, 10, "28");
	mvaddstr(5, 10, "30");
	mvaddstr(4, 9, "(度)");
	mvaddstr(2, 40, "A/F");


	int k, j;
	for (k = x; k < x + 15; k++) {
		for (j = 0; j < (data[k][3] / 2); j++) {
			mvaddstr(i - (j + 1), 13 + ((k - x) * 5), "*");
		}

	}
}

//結果
void printKekka(double data[TIME][OTHERDATA]) {
	int i = 20;

	mvaddstr(25, 7, "←水温グラフ");
	mvaddstr(25, 80, "スロットル開度グラフ→");
	mvaddstr(26, 42, "↓A/Fグラフ");
	mvaddstr(24, 42, "↑結果");

	mvaddstr(2, 40, "結果");

	//抜き出した15秒間のデータの平均
	int k;
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
	mvprintw(6, 40, "回転数平均:%lf", ave_rpm);
	mvprintw(7, 40, "アクセル開度平均:%lf", ave_tps);
	mvprintw(8, 40, "水温平均:%lf", ave_wtp);
	mvprintw(9, 40, "A/F平均:%lf", ave_AF);

	//判定
	if (ave_rpm <= 2000 && 1000<=ave_rpm) {
		mvaddstr(11, 40, "*アイドリング時");
	}
	if (ave_rpm >= 9000) {
		mvaddstr(12, 40, "*高回転域");
	}
	if (ave_tps >=100) {
		mvaddstr(13, 40, "*アクセル開度max");
	}
	if (ave_wtp >= 80) {
		mvaddstr(14, 40, "*ラジエーターファンを回す");
	}
	

}

void fileout(double data[TIME][OTHERDATA]) {
	using namespace std;

	//全データの平均
	int k;
	double count_AF = 0.0, count_wtp = 0.0, count_tps = 0.0, count_rpm = 0.0;
	for (k = 0; k < 4999; k++) {
		count_AF = count_AF + data[k][3];
		count_wtp = count_wtp + data[k][2];
		count_tps = count_tps + data[k][1];
		count_rpm = count_rpm + data[k][0];

	}
	double ave_AF = 0.0, ave_wtp = 0.0, ave_tps = 0.0, ave_rpm = 0.0;
	ave_AF = count_AF / 4999;
	ave_wtp = count_wtp / 4999;
	ave_tps = count_tps / 4999;
	ave_rpm = count_rpm / 4999;

	//テキストファイルに出力
	string filename("kekka.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::out);
	if (!file_out.is_open()) {
		cout << "failed to open " << filename << '\n';
	}
	else {
		file_out << "全データにおける平均は以下の通りです\n" << endl;
		file_out << "回転数平均は" << ave_rpm << "です\n" << endl;
		file_out << "水温平均は " << ave_wtp << "です\n" << endl;
		file_out << "スロットル開度平均は " << ave_tps << "です\n" << endl;
		file_out << "A/F平均は " << ave_AF << "です\n" << endl;
		cout << "Done Writing!" << endl;
	}
}