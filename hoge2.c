#include<stdio.h>

int main(){
    //init
    int n=3;double cnst;int x[3]={1,2,3};
    double x_1=1,x_2=1,x_3=1;
    double A[3][4]={{5, 1, 1,  10},
                    {1, 4, 1,  12},
                    {2, 1, 3,  13}};

    //cluculate
    for(int i=0;i<20;i++){
        x_1=(A[0][3] -A[0][1]*x_2 -A[0][2]*x_3)/A[0][0];
        x_2=(A[1][3] -A[1][0]*x_1 -A[1][2]*x_3)/A[1][1];
        x_3=(A[2][3] -A[2][0]*x_1 -A[2][1]*x_2)/A[2][2];
        
        if(i<9){
            printf("%d  : x1=%.10lf x2=%.10lf x3=%.10lf \n",i+1,x_1,x_2,x_3);
        }else{
            printf("%d : x1=%.10lf x2=%.10lf x3=%.10lf \n",i+1,x_1,x_2,x_3);
        }
    }
}