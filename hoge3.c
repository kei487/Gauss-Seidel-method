#include<stdio.h>


double get_x(int n,double x_a,double x_b,double *p[3]){  //n行目xの値を返す関数
    n--;
    return (p[n][3] -p[n][(n+1)%3]*x_a -p[n][(n+2)%3]*x_b)/p[n][n];
}

int co(double a,double b){   //与えられた2実数の差が十分に小さければ１を返しそうでなければ０を返す関数
    if((a-b<0.00000000001&&a-b>0)||(b-a<0.00000000001&&b-a>0)){
        return 1;
    }else{
        return 0;
    }
}


int main(){
    //init
    double *pA[3];
    double x_1=1,x_2=1,x_3=1;
    double tmp1=0,tmp2=0,tmp3=0;
    double A[3][4]={{5, 1, 1,  10},
                    {1, 4, 1,  12},
                    {2, 1, 3,  13}};
    pA[0]=A[0];pA[1]=A[1];pA[2]=A[2];

    //calculate
    for(int i=0;i<20;i++){
        //xを更新
        x_1=get_x(1,x_2,x_3,pA);
        x_2=get_x(2,x_3,x_1,pA);
        x_3=get_x(3,x_1,x_2,pA);
        
        if(co(x_1,tmp1)&&co(x_2,tmp2)&&co(x_3,tmp3)){  //x_1,x_2,x_3がそれぞれ前回との差がなくなったらおしまい
            printf("finish\n");
            break;
        }
        tmp1=x_1;tmp2=x_2;tmp3=x_3;  //tmpを更新

    //output
        if(i<9){ //出力の幅を揃える一手間
            printf("%d  : x1=%.10lf x2=%.10lf x3=%.10lf \n",i+1,x_1,x_2,x_3);  //%.10lfで小数点以下10桁表示に
        }else{
            printf("%d : x1=%.10lf x2=%.10lf x3=%.10lf \n",i+1,x_1,x_2,x_3);
        }
    }
}