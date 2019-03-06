#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;


int judge(string str){

    int index = str.find(' ');
    if(str[0]=='#' && index == string::npos){

        return 2;
    }
    else if(index != string::npos){

        return 3;
    }
    else{

        return 1;
    }



}

int findNoDocIndex(string doc){

    int i = 0;

    for(;doc[i] == '.';++i);

    return i;
}

int findLabelSpace(string doc){


    int i = 0;
    for(; i < doc.length() && doc[i] != ' ' ;++i);

    return i;
}

void toUpper(string& str){

    for(int i = 0; i < str.length(); ++i){


        if(str[i]>='a' && str[i] <= 'z'){

            str[i] = str[i] - 'a' + 'A';
        }
    }

    return;
}


vector<int> findLabel(vector<string>& doc,string selector){



    vector<int> res; //���ҽ��
    res.push_back(0);

    for(int i = 0;i < doc.size(); ++i){


        int index1 = findNoDocIndex(doc[i]);//�ҵ���һ������.���ַ����±꣬Ҳ���Ǳ�ǩ��һ����ĸ�±�
        int index2 = findLabelSpace(doc[i]);//�ҵ���һ���ո�����ַ�����β

        string label = doc[i].substr(index1,index2-index1); //��ȡ�Ӵ��õ���ǩ
        toUpper(label); //��Ϊ��Сд�������Ƕ�ת���ɴ�д
        toUpper(selector);

        if(label == selector){

            ++res[0];
            res.push_back(i+1);

        }

    }

    return res;

}

vector<int> findID(vector<string>& doc,string selector){



    vector<int> res;
    res.push_back(0);

    selector = selector.substr(1);
    for(int i = 0; i < doc.size();++i){


        int index1 = doc[i].find('#'); //�ҵ���һ��#
        if(index1 == string::npos){ //��������ĸ���docû��#˵��û��id������һ��

            continue;
        }

        string ID = doc[i].substr(index1+1);//��#��ʼ��һ���ַ�����󣬻�ȡ�ִ�


        if(ID == selector){

            ++res[0];
            res.push_back(i+1);
        }
    }

    return res;

}

void findMore(vector<string>& doc,int startLine,vector<int>& res,vector<string>selectors,int index){



    if(index == selectors.size()){

        ++res[0];
        res.push_back(startLine+1);

        return;
    }



    int startLineDotNum = findNoDocIndex(doc[startLine]);

    for(int i = startLine+1;i < doc.size();++i){

        int curDotNum = findNoDocIndex(doc[i]);
        if(curDotNum <= startLineDotNum){

            break;
        }
        else if(curDotNum != startLineDotNum + 2){

            continue;
        }
        else{


            if(selectors[index][0] == '#'){



                int indexTemp = doc[i].find('#');

                if(indexTemp == string::npos){

                    continue;
                }

                string str1 = selectors[index].substr(1);
                string str2 = doc[i].substr(indexTemp+1);

                if(str1 == str2){

                    findMore(doc,i,res,selectors,index+1);
                }
                else{

                    continue;
                }

            }
           else{


               string str1 = selectors[index];
               int lastTemp = findLabelSpace(doc[i]);
               string str2 = doc[i].substr(curDotNum,lastTemp-curDotNum);


               toUpper(str1);
               toUpper(str2);

               if(str1 == str2){


                    findMore(doc,i,res,selectors,index+1);
               }
               else{

                    continue;
               }

           }


        }


    }



}

vector<string> split(string str){

    int index = 0;
    vector<string> res;
    int index1;
    while(index < str.length() && (index1 = str.find(' ',index)) != string::npos){

        res.push_back(str.substr(index,index1-index));
        index = index1+1;
    }

    res.push_back(str.substr(index));

    return res;
}

int main(void){

    int n;
    int m;
    cin >> n;

    cin >> m;

    vector<string>doc;

    string temp;
    getchar();
    for(int i = 0;i < n;++i){


        getline(cin,temp);
        doc.push_back(temp);



    }
    vector<string>selector;

    for(int i = 0; i < m;++i){

        getline(cin,temp);

        selector.push_back(temp);
    }


    vector<vector<int>> res;

    for(int i = 0; i < m; ++i){

        int kind = judge(selector[i]);


        if(kind == 1){ //����Ǳ�ǩѡ�����Ļ�

            res.push_back(findLabel(doc,selector[i]));

        }
        else if(kind == 2){ //�����idѡ�����Ļ�

            res.push_back(findID(doc,selector[i]));
        }
        else{ //����Ǻ��ѡ�����Ļ�

            vector<string> selectors = split(selector[i]);

            vector<int> temp;
            if(selectors[0][0] == '#'){


                temp = findID(doc,selectors[0]);

            }
            else{

                temp = findLabel(doc,selectors[0]);
            }

            if(temp[0] == 0){

                continue;
            }
            vector<int> resTemp;
            resTemp.push_back(0);

            for(int i = 0; i < temp[0]; ++i){

                findMore(doc,temp[i+1]-1,resTemp,selectors,1);

            }
            sort(resTemp.begin()+1,resTemp.end());
            res.push_back(resTemp);

        }
    }



    for(int i = 0; i < res.size(); ++i){


        for(int j = 0;j < res[i].size();++j){


            if(j == res[i].size()-1){

                cout << res[i][j];
            }
            else{

                cout << res[i][j] << ' ';
            }
        }

        cout << endl;
    }


    return 0;
}
