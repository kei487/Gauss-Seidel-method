#include <stdio.h>
#include "path_data.h" //これがポイント

double get_x(int h,int n,double *x,double *a[N]){ //x_hを返す関数
    double m=0;
    m+=a[h][n];
    for(int i=1;i<n;i++){
        m-=a[h][(h+i)%n]*x[(h+i)%n];
    }
    m/=a[h][h];
    return m;
}

int compe(double *a,double *b,int n){ //n個の要素全てがほぼ一致したときに1を返す関数（前回の使いまわし）
    for(int i=0;i<n;i++){
        if((a[i]-b[i]<0.000000000001&&a[i]-b[i]>0)||(b[i]-a[i]<0.000000000001&&b[i]-a[i]>0)){
            //skip
        }else{
            return 0;
        }
    }
    return 1;
}


int main(){
    //---init----
    int clr=0;
    double *pA[N];
    double tmp[N];
    for(int i=0;i<N;i++){
        pA[i]=A[i];
    }

    for(int i=0;i<loop_times;i++){

    //----calculate----
        for(int j=0;j<N;j++){
            x[j]=get_x(j,N,x,pA);  //xを更新
        }

        if(compe(x,tmp,N)){  //x_1,x_2,x_3がそれぞれ変化しなくなったらおしまい
            puts("\x1b[31m\nCongratulations!\nFinish\n");  //赤色に変更
            break;
        }
        for(int i=0;i<N;i++){  //前回のxを保存
            tmp[i]=x[i];
        }

    //----print-----
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
        for(int j=0;j<N;j++){ //要素をプリント
            if(x[j]>0){
                printf(" x%d= %.10lf",j+1,x[j]);
            }else{
                printf(" x%d=%.10lf",j+1,x[j]);
            }
        }puts("");

    }
}