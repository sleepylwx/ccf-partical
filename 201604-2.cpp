#include<cstdio>

struct pairs{

    int x;
    int y;
    //
    //����ṹ����Ϊ�˼�¼��ǰ������ĸ�����ʲôλ��
    //�����жϵ�ǰ�ķ�����������ƶ���ʹ���������������������ƶ�

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

                arr[i][j+start-1] = 2; //�Ȱ������ͼ���������У�Ϊ������ԭ�������������Ԫ�أ����2

            }

        }

    }

    int flag = 0; //�����㷽���޷������ƶ�������ʱ��flag��1
    pairs movearr[4];//��¼��ǰ�����ĸ����ӵ�λ��
    int counter; //movearr���±������

    //whileѭ��������ͣ�ĸ�������������״̬
    while(1){

        //�����˫��forѭ������ÿ�α����������̣��жϵ�ǰ״̬�ķ�����ĸ������ܷ�����
        //�������ƣ�ÿ���ƶ�һ����λ�������Ǵ������Ͻ��У���Ϊ�����Ԫ�����ȵ���ײ���������ʵ��������Ҳ����
        counter = 0;
        for(int i = 14; i >= 0; --i){


            for(int j = 9; j >= 0; --j){

                if(arr[i][j] == 2){ //�����ǰ�����Ƿ����е�Ԫ��


                    if(i == 14){ //�������ײ����޷�����

                        flag = 1;
                        break;
                    }
                    if(arr[i+1][j] == 1){ //���������¸�Ԫ�������������е�Ԫ�أ��޷�����

                        flag = 1;
                        break;
                    }
                    //��ȥ���������������������ƶ������¼�·����з���ĵ�ǰλ�ã���������
                    movearr[counter].x = i;
                    movearr[counter].y = j;
                    ++counter;

                }

            }

        }

        //flag == 1 ˵�������޷����ƣ�����״̬�ȶ�
        if(flag == 1){

            break;
        }

        //����Ԫ������
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
