#include<cstdio>

struct pairs{

    int x;
    int y;
    //
    //这个结构体是为了记录当前方块的四个格在什么位置
    //方便判断当前的方块可以向下移动后，使用这里面的坐标进行向下移动

};
int main(void){


    int arr[15][10];

    for(int i = 0; i < 15;++i){


        for(int j = 0; j < 10; ++j){


            scanf("%d",&arr[i][j]);
        }

    }

    int arrTemp[4][4];

    for(int i = 0; i < 4; ++i){


        for(int j = 0; j < 4; ++j){

            scanf("%d",&arrTemp[i][j]);

        }

    }

    int start;
    scanf("%d",&start);

    for(int i = 0; i < 4; ++i){


        for(int j = 0; j < 4; ++j){

            if(arrTemp[i][j] == 1){

                arr[i][j+start-1] = 2; //先把最初的图形填到方格版中，为了区分原来方格版中已有元素，填充2

            }

        }

    }

    int flag = 0; //当满足方块无法向下移动的条件时，flag置1
    pairs movearr[4];//记录当前方块四个格子的位置
    int counter; //movearr的下标计数器

    //while循环用来不停的更新整个方格版的状态
    while(1){

        //下面的双层for循环用来每次遍历整个棋盘，判断当前状态的方块的四个格子能否下移
        //若能下移，每次移动一个单位。遍历是从下往上进行，因为下面的元素最先到达底部，但是其实从上往下也可以
        counter = 0;
        for(int i = 14; i >= 0; --i){


            for(int j = 9; j >= 0; --j){

                if(arr[i][j] == 2){ //如果当前方格是方块中的元素


                    if(i == 14){ //如果到达底部，无法下移

                        flag = 1;
                        break;
                    }
                    if(arr[i+1][j] == 1){ //如果方格的下个元素是棋盘中已有的元素，无法下移

                        flag = 1;
                        break;
                    }
                    //除去以上两种情况，方块可以移动，则记录下方块中方格的当前位置，方便下移
                    movearr[counter].x = i;
                    movearr[counter].y = j;
                    ++counter;

                }

            }

        }

        //flag == 1 说明方块无法下移，棋盘状态稳定
        if(flag == 1){

            break;
        }

        //进行元素下移
        for(int i = 0; i < 4; ++i){

            int x = movearr[i].x;
            int y = movearr[i].y;

            arr[x][y] = 0;
            arr[x+1][y] = 2;
        }

    }


    for(int i = 0;i < 15; ++i){

        for(int j = 0; j < 10; ++j){

            if(j == 0){

                printf("%d",arr[i][j] == 2 ? 1:arr[i][j]);
            }
            else{

                printf(" %d",arr[i][j] == 2 ? 1:arr[i][j]);
            }


        }

        printf("\n");
    }

    return 0;
}
