#include<cstdio>


int main(void){

    int ryg[3];
    scanf("%d%d%d",&ryg[0],&ryg[2],&ryg[1]);

    int n;

    scanf("%d",&n);
    int arr[n][2];
    int kindTemp;
    int timeTemp;
    for(int i = 0;i < n; ++i){

        scanf("%d%d",&kindTemp,&timeTemp);
        if(kindTemp == 2){

            kindTemp = 3;
        }
        else if(kindTemp == 3){

            kindTemp = 2;
        }

        arr[i][0] = kindTemp;
        arr[i][1] = timeTemp;
    }

    int time = 0;
    for(int i = 0; i < n; ++i){


        if(arr[i][0] == 0){

            /***״̬ת������***********/
            //ͨ��ĳ��·����ʱ�䣬Ҫ�ӵ�����ĵ���
            for(int j = i + 1; j < n; ++j){

                if(arr[j][0] != 0){

                    arr[j][1] -= arr[i][1];


                }
            }
            /************************/
            time += arr[i][1];
        }
        else{

            /***״̬ת������***********/
            //������ʱ���ж����費��Ҫ����״̬
            if(arr[i][1] <= 0){


                int index = arr[i][0]+1;
                while(1){

                    if(index > 3){

                        index = index % 4 + 1;
                    }

                    arr[i][1] += ryg[index-1];

                    if(arr[i][1] > 0){

                        arr[i][0] = index;
                        break;
                    }

                    ++index;


                }
            }

            /************************/


            if(arr[i][0] == 1){

                time += arr[i][1];

                 /***״̬ת������***********/
                 //������״̬���������ʱ��������ĵƼ��ϵȴ�ʱ��
                for(int j = i + 1; j < n; ++j){

                    if(arr[j][0] != 0){

                        arr[j][1] -= arr[i][1];

                    }

                }
                /************************/
            }
            else if(arr[i][1] == 2){


            }
            else{

                int timeTemp = arr[i][1];
                timeTemp += ryg[0];
                time += timeTemp;

                 /***״̬ת������***********/
                 //������״̬�������Ƶ�ʱ��������ĵƼ��ϵȴ�ʱ��
                for(int j = i + 1; j < n; ++j){

                    if(arr[j][0] != 0){

                        arr[j][1] -= timeTemp;

                    }

                }
                /************************/
            }

        }

    }

    printf("%d",time);
    return 0;
}
