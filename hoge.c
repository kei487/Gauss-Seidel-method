#include <stdio.h>
#define swap(x,y){double tmp=x;x=y;y=tmp;}

int main(){
    //init
    int n=3;double cnst;int x[3]={1,2,3};
    int flag;
    double A[3][4]={{5, 1, 1,  10},
                    {1, 4, 1,  12},
                    {0, 1, 0,  13}};

    //inspeciton
    double detA = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] - A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2] - A[0][2]*A[1][1]*A[2][0];
    if(detA==0){  //行列式が0の時唯一の解が定まらないのではじく
        printf("Error\n");
        return 0;
    }
    for(int s=0;s<n;s++){
        flag=1;
        for(int i=0;i<n;i++){
            if(A[i][i]==0){  //(i,i)成分が0だと除算でエラーがでるので行入れ替えを行う
                flag=0;
                for(int j=0;j<n;j++){
                    if(i!=j){
                        if(A[j][i]!=0&&A[j][j]!=0){
                            printf("swap:A[%d][k],A[%d][k]\n",i,j);
                            for(int k=0;k<n+1;k++){
                                swap(A[i][k],A[j][k]);
                            }
                        }
                        break;
                    }
                }
            }
        }
        if(flag){
            break;
        }
    }

    //computing
    for(int i=0;i<n;i++){ //固定行
        for(int j=0;j<n;j++){ //計算行
            if(i!=j){ //固定行後回し
                cnst=A[j][i]/A[i][i];
                for(int k=0;k<n+1;k++){ //計算列
                    A[j][k] = A[j][k] - cnst*A[i][k];
                }
            }
        }
        for(int l=0;l<n+1;l++){ //固定行計算列
            if(i!=l){ //(i,i)要素が影響を与えるので後回し
                A[i][l] = A[i][l]/A[i][i];
            }
        }
        A[i][i]/=A[i][i]; //無駄な負荷
    }

    //ans
    printf("x1 = %lf\nx2 = %lf\nx3 = %lf\n",A[0][3],A[1][3],A[2][3]);
    return 0;
}