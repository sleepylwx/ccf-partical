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
    vector<vector<string>> patterns;
    char temp[101];
    for(int i = 0; i < n; ++i){

        scanf("%s",temp);
        patterns.push_back(vector<string>());
        fillPatterns(patterns,temp);
        scanf("%s",temp);
        patterns.back().push_back(temp);

    }

    vector<string> urls;
    for(int i = 0; i < m; ++i){

        scanf("%s",temp);
        urls.push_back(temp);

    }

    for(int i = 0; i < m; ++i){

        int flag = 0;
        vector<string> res;

        for(int j = 0; j < patterns.size();++j){


            int index = 1;
            string url = urls[i];
            vector<string> params;
            int k;
            for(k = 0; k < patterns[j].size()-1; ++k){

                if(index >= url.length()){

                    break;
                }
                string pattern = patterns[j][k];

                if(pattern == "<int>"){

                    string temp = split(url,index);

                    string command = compatInt(temp);

                    if(command == "$"){

                        break;
                    }
                    else{

                        int counter = 0;
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

                    string temp = url.substr(index);

                    params.push_back(temp);
                    index = string::npos;
                }
                else{


                    string temp = split(url,index);

                    if(temp == pattern){

                        continue;
                    }
                    else{

                        break;
                    }

                }


            }

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
