#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
char trash_can[100];//不要なデータを格納する。
int classes(int day){ //時間割を読み込んで表示するための関数。
	int i;//iはループのカウンタ。
	char subject[40][100];//教科を格納する。
	FILE *fp;
	fp = fopen("jknwr.smd", "r");//時間割データを開きます。

	if(fp == NULL) {    //エラー処理
		printf("jknwr.smdがありません。時間割を作成してください。\n");
		return(-1);//とりあえずエラーなので-1を返すが意味は特にない。
		printf("終了するにはエンターキーを押してください。");
		scanf("%s", &trash_can);
	}

	else{
		fscanf(fp,"%s", &trash_can); //時間割データの1行目を無視するための文。
		for (i = 0; i<25; ++i){
			fscanf(fp, "%s", &subject[i]);
		}
		fclose(fp);
		printf("今日の授業は");
		if (day == 0)		//休日は授業がない!!
			printf("ありません。\n");
		else if (day == 6)		//同上
			printf("ありません。\n");
		else{
			printf("\n");
			day = (day-1)* 5;
			for (i = 0; i<5; ++i){
				printf("%d限目・・・%s\n", i+1, subject[day]);//時間割を表示する。
				++day;
			}
		printf("です。\n");
		}
	}
}

int mk(void){//実際に時間割を編集する関数
	FILE *fp;
	fp = fopen("jknwr.smd", "w");
	if(fp == NULL) {
		printf("jknwr.smdを開けませんでした。原因はわかりません。");
		return(-1);
	}

	else{
		int i ;//ループカウンタ
		int j ; //時限
		char line[30][100];//教科を格納する。
		char day[10];//曜日
		fputs("<--この下から入力してください。ここが1行目。-->\n",fp);
		for(i = 0; i < 25; ++i ){
			if (i < 5){
				j = i;
				strcpy(day, "月");
			}
			else if (i < 10){
				j = i -5;
				strcpy(day, "火");
			}
			else if(i < 15){
				j = i - 10;
				strcpy(day, "水");
			}
			else if (i < 20){
				j = i - 15;
				strcpy(day, "木");
			}
			else{
				j = i - 20;
				strcpy(day, "金");
			}
			printf("%s曜日の%d時間目の教科を入力してください。授業がない場合は「なし」と入力してください。\n", day, j + 1);
			fgets(line[i], sizeof(line[i]), stdin);
			fputs(line[i], fp);
		}//forここまで
		fputs("<--入力ここまで。ここが27行目になってないとエラーになる。-->", fp);
		printf("お疲れさまでした。完了です。\n");
		fclose(fp);
		printf("終了するにはエンターキーを押してください。\n");
		fgets(trash_can, sizeof(trash_can), stdin);
	}//else ここまで
}//関数ここまで

int edit(){ //時間割データ作成、編集用関数。
	char line[10];
	printf("時間割データを作成します。すでに時間割データが存在する場合、そのデータに上書きします。\n");
	while(1){
		printf("続行しますか？ Y/N\n");

		fgets(line, sizeof(line), stdin);
		if (strcmp(line, "y\n") == 0){
			mk();
			break;
		}
		else if (strcmp(line, "Y\n") == 0){
			mk();
			break;
		}
		else if (strcmp(line, "n\n") == 0)
			break;
		else if (strcmp(line, "N\n") == 0)
			break;
		else
			printf("入力は半角のYまたはNのみ可能です。\n");
	}
}
int main(){  //メイン関数 曜日を調べる。
	int day;
	char check[5];
	time_t timer;
	time(&timer);
	struct tm *local;
	local = localtime(&timer);
	timer = time(NULL);
	day = local-> tm_wday;
	classes(day);
	printf("終了するにはエンターキーを押してください。\n時間割の編集、作成をするには「e」を入力してからエンターキーを押してください。\n");
	fgets(check, sizeof(check), stdin);
	if (strcmp(check, "e\n") == 0)
		edit();
	else
		exit(0);
}
