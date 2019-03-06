#include<cstdio>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

void fillPatterns(vector<vector<string>>& patterns,string temp){

    int index = 1;
    int index1;

    int flag = 0;
    while(1){


        if(index >= temp.length()){

            flag = 1;
            break;
        }

        int index1 = temp.find("/",index);

        if(index1 == string::npos){

            break;
        }


        patterns.back().push_back(temp.substr(index,index1-index));
        index = index1 + 1;

    }

    if(flag == 0){

       patterns.back().push_back(temp.substr(index));
    }


    return;
}

string compatInt(string str){


    for(int i = 0; i < str.length();++i){

        if(str[i] >= '0' && str[i] <= '9'){

            continue;
        }
        else{

            return "$";
        }
    }

    return str;
}

string compatStr(string str){


    for(int i = 0; i < str.length() ;++i){

        if(isalpha(str[i])){


        }
        else{

            return "%";
        }
    }

    return str;

}

string compatPath(string str){

    return str;

}

string split(string str,int& index){


    int index1;

    index1 = str.find('/',index);

    string temp;
    if(index1 == string::npos){

        temp = str.substr(index);

    }
    else{

        temp = str.substr(index,index1-index);
    }


    index = index1 + 1;

    return temp;
}

int main(void){


    int n;
    int m;
    scanf("%d%d",&n,&m);
    vector<vector<string>> patterns;//存放每条url规则映射
    char temp[101];
    for(int i = 0; i < n; ++i){

        scanf("%s",temp);
        patterns.push_back(vector<string>());
        fillPatterns(patterns,temp); //把输入的url映射规则拆分成一个个单词，例如/a/b/c/ 则拆分成a b c存入vector中
        scanf("%s",temp);
        patterns.back().push_back(temp); //把每条url映射规则的名字放到最后

    }

    vector<string> urls;//存url
    for(int i = 0; i < m; ++i){

        scanf("%s",temp);
        urls.push_back(temp);

    }

    //对每条url遍历url映射规则
    for(int i = 0; i < m; ++i){

        int flag = 0;
        vector<string> res;

        for(int j = 0; j < patterns.size();++j){


            int index = 1; //当前正在匹配的url中的字符串的下标
            string url = urls[i];
            vector<string> params; //存放<int> <str> <path>匹配到的参数
            int k;
            //对于每条url映射规则，遍历其拆分后的词
            for(k = 0; k < patterns[j].size()-1; ++k){


                if(index >= url.length()){

                    break;
                }
                string pattern = patterns[j][k];

                if(pattern == "<int>"){

                    string temp = split(url,index);//把当前正在匹配的url的下一个/之间的词取出

                    string command = compatInt(temp); //判断取出的词是否满足整数

                    if(command == "$"){ //$为非整数时返回的标志

                        break;
                    }
                    else{

                        int counter = 0;
                        //消除前面多余的0
                        for(int i = 0; i < command.length(); ++i){

                            if(command[i] == '0'){

                                ++counter;
                            }
                            else{
                                break;
                            }
                        }

                        command = command.substr(counter);
                        params.push_back(command);
                        continue;
                    }

                }
                else if(pattern == "<str>"){

                    //这部分代码与<int> 中的部分作用一样
                    string temp = split(url,index);

                    string command = compatStr(temp);

                    if(command == "%"){

                        break;
                    }
                    else{

                        params.push_back(command);
                        continue;

                    }

                }
                else if(pattern == "<path>"){

                    //遇到<path>时，直接把index之后的字符串全都取出来匹配上
                    string temp = url.substr(index);

                    params.push_back(temp);
                    index = string::npos; //string::npos是一个很大的数，保证循环最开始的if判断成立，匹配结束，退出循环
                }
                else{

                    //正常的字符串匹配
                    string temp = split(url,index);

                    if(temp == pattern){

                        continue;
                    }
                    else{

                        break;
                    }

                }


            }

            //若某个url映射规则匹配的循环退出后，已经遍历完该规则的所有拆分的单词，且
            // url也已经匹配到最后，即index已经超过了url的长度，则匹配成功。
            //将映射规则的名字放入res中，把匹配到的参数也放入res中。
            //flag置1，表明该url有匹配的结果。便可以break该循环，进入下一个url的匹配
            if(k == patterns[j].size()-1 && index >= url.length()){

                flag = 1;
                res.push_back(patterns[j].back());

                for(int k = 0; k < params.size();++k){

                    res.push_back(params[k]);
                }

                break;
            }

        }



        if(flag == 0){
            //该url没有匹配到映射规则
            printf("404\n");
        }
        else{

            for(int j = 0; j < res.size() ;++j){

                if(j == 0){

                    printf("%s",res[j].c_str());
                }
                else{

                    printf(" %s",res[j].c_str());
                }

            }

            printf("\n");
        }

    }

    return 0;
}
