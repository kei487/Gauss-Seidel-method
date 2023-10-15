#include<stdio.h>


int print_matrix(int n);

int main(){
	FILE *fp1, *fp2;
	double A[10][11],x[10];
	int n,loop_times,mood;
	
	//tmpファイルを読み取りモードで開く、開けなかったら終了
	if((fp2 = fopen("tmp_data.txt","r"))==NULL){
		fprintf(stderr, "Can not open tmp_data.txt\n");
		return -1;
	}
	
	//各パラメータを一度変数に格納
	fscanf(fp2,"%d",&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n+1;j++){
			fscanf(fp2," %lf",&A[i][j]);
		}
	}
	fscanf(fp2,"%lf",&x[0]);
	for(int i=1;i<n;i++){
		x[i]=x[0];
	}
	fscanf(fp2,"%d",&loop_times);

	printf("n:%d x:%lf loop_times:%d\n",n,x[0],loop_times);
	for(int i=0;i<n;i++){
		for(int j=0;j<n+1;j++){
			printf("A[%d][%d]=%lf ",i,j,A[i][j]);
		}puts("");
	}puts("");

	//データ更新パート
	while(1){
		printf("入力するパラメータを選択してください\n");
		printf("0:行列全体 1:係数行列 2:定数項ベクトル");
		printf("3:xの初期値 4:繰り返し回数 -1:終了\n:");
		scanf("%d",&mood);
		if(mood==-1){break;}
		switch (mood){
			case 0:
				printf("行列の大きさ(n|1<n<10)を入力してください:");
    			scanf("%d",&n);
    			while(n<2||n>9){  
        			printf("2以上9以下の数直してください:");
        			scanf("%d",&n);
    			}
				print_matrix(n);
				printf("左辺を入力してくださいa[1][1],a[1][2],~,a[%d][%d]:",n,n);
    			for(int i=0;i<n;i++){
        			for(int j=0;j<n;j++){
            			scanf("%lf",&A[i][j]);
        			}
    			}
    			printf("右辺を入力してくださいx1~x%d:",n);
    			for(int i=0;i<n;i++){
        			scanf("%lf",&A[i][n]);
    			}
				break;
			case 1:
				print_matrix(n);
				printf("左辺を入力してくださいa[1][1],a[1][2],~,a[%d][%d]:",n,n);
    			for(int i=0;i<n;i++){
        			for(int j=0;j<n;j++){
            			scanf("%lf",&A[i][j]);
        			}
    			}
				break;
			case 2:
				print_matrix(n);
				printf("右辺を入力してくださいx1~x%d:",n);
    			for(int i=0;i<n;i++){
        			scanf("%lf",&A[i][n]);
    			}
				break;
			case 3:
				printf("xの初期値を入力してください:");
    			scanf("%lf",&x[0]);
    			for(int i=1;i<n;i++){
        			x[i]=x[0];
    			}
				break;
			case 4:
				printf("繰り返し回数を入力してください(目安：20):");
    			scanf("%d",&loop_times);
				break;
			default:
				break;
		}
	}

	fclose(fp2);//いったん閉じる（必要？）

	//書き込みパート
	//ヘッダファイルとtmpファイルを書き込みモードで開く
	if((fp1 = fopen("path_data.h","w"))==NULL){
		fprintf(stderr, "Can not open path_data.h\n");
		return -1;
	}
	if((fp2 = fopen("tmp_data.txt","w"))==NULL){
		fprintf(stderr, "Can not open tmp_data.txt\n");
		return -1;
	}

	printf("tmpファイルを生成しています....\n");

	fprintf(fp2,"%d\n",n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n+1;j++){
			fprintf(fp2," %lf",A[i][j]);
		}
	}fprintf(fp2,"\n");
	fprintf(fp2,"%lf\n%d",x[0],loop_times);
	fprintf(fp2,"\n\n1:n\n2:a[0][0] a[0][1] ... a[n-1][n]\n3:x_0\n4:loop_times");

	printf("ヘッダを生成しています....\n");

	fprintf(fp1,"#ifndef PATH_DATA_H\n#define PATH_DATA_H\n//------------------------------------------------\n#include <stdio.h>\n \n//------------------------------------------------\n//  プロトタイプ宣言(Prototype declaration)\n//------------------------------------------------\n");
	fprintf(fp1,"#define N %d\n",n);
	fprintf(fp1,"#define loop_times %d\n \n",loop_times);
	fprintf(fp1,"//------------------------------------------------\n//  プロトタイプ宣言(Prototype declaration)\n//------------------------------------------------\n");
	fprintf(fp1,"double A[%d][%d] = {",n,n+1);
	for(int i=0;i<n;i++){
		fprintf(fp1,"{");
		for(int j=0;j<n+1;j++){
			fprintf(fp1," %.1lf",A[i][j]);
			if(j==n){break;}
			fprintf(fp1,",");
		}
		fprintf(fp1,"}");
		if(i==n-1){break;}
		fprintf(fp1,",");
	}
	fprintf(fp1,"};\n");
	fprintf(fp1,"double x[%d] = {",n);
	for(int i=0;i<n;i++){
		fprintf(fp1," %.1lf",x[i]);
		if(i==n-1){break;}
		fprintf(fp1,",");
	}
	fprintf(fp1,"};\n");
	fprintf(fp1,"//------------------------------------------------\n#endif");

	fclose(fp1);
	fclose(fp2);
	
	printf("path_data.h and tmp_data.txt is generated sucessfully.\n");

    return 0;
}

//任意の大きさnの行列の方程式を描画する関数
int print_matrix(int n){ 
    for(int i=1;i<n+1;i++){
        printf("|");
        for(int j=1;j<n+1;j++){
            printf(" a[%d][%d]",i,j);
        }
        printf(" |");
        if(i==(n+1)/2){
            printf("=");
        }else{
            printf(" ");
        }
        printf("| x%d |\n",i);
    }
	return 0;
}