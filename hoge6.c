#include <stdio.h>
#include <stdlib.h>


double get_x(int h,int n,double x[n],double a[n][n+1]){ //x_hを返す関数
    double m=0;
    m+=a[h][n];
    for(int i=1;i<n;i++){
        m-=a[h][(h+i)%n]*x[(h+i)%n];
    }
    m/=a[h][h];
    return m;
}

//n個の要素全てがほぼ一致したときに1を返す関数
//使いまわしにつきあまり綺麗でない
int compe(double *a,double *b,int n){ 
    for(int i=0;i<n;i++){
        if((a[i]-b[i]<0.000000000001&&a[i]-b[i]>0)||(b[i]-a[i]<0.000000000001&&b[i]-a[i]>0)){
            
        }else{
            return 0;
        }
    }
    return 1;
}


int main(){
    //======init=======
    int n,count,clr=1;

    //=====================input=====================
    printf("このプログラムは連立方程式をガウスザイデル法で解きます\n次のメッセージに続き数値を入力してください\n行列の大きさ(n|1<n<10)を入力してください:");
    scanf("%d",&n);
    while(n<2||n>9){  
        printf("2以上9以下の数直してください:");
        scanf("%d",&n);
    }
    //callocを使わずともこれでコンパイルが通り動くのでこちらのバージョンも....c99(gccのver.4.5.0)から対応しているらしい...
    double A[n][n+1];
    double x[n];
    double tmp[n];

    //===行列のイメージ表示===
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
    //各パラメータを入力
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
    printf("xの初期値を入力してください:");
    scanf("%lf",&x[0]);
    for(int i=1;i<n;i++){
        x[i]=x[0];
    }
    printf("繰り返し回数を入力してください(目安：20):");
    scanf("%d",&count);

    //======================calculate======================
    for(int i=0;i<count;i++){
        
        for(int j=0;j<n;j++){
            x[j]=get_x(j,n,x,A);  //xを更新
        }
        
        if(compe(x,tmp,n)){  //xとtmpの中身が全部一致したらプログラム終了
            puts("\x1b[31m\nCongratulations!\nFinish\n");  //赤色に変更
            break;
        }
        for(int i=0;i<n;i++){  //前回のxを保存
            tmp[i]=x[i];
        }
        
        if(clr){  //行が見やすいように色分け(環境ごとに色が違うらしい)
            printf("\x1b[38;5;44m");clr=0;
        }else{
            printf("\x1b[38;5;74m");clr=1;
        }

        if(i<9){ //出力の幅を揃える一手間
            printf("%d  :",i+1);
        }else{
            printf("%d :",i+1);
        }
        for(int j=0;j<n;j++){ //要素をプリント
            if(x[j]>0){
                printf(" x%d= %.10lf",j+1,x[j]);
            }else{
                printf(" x%d=%.10lf",j+1,x[j]);
            }
        }puts("");
    }

    return 0;
}