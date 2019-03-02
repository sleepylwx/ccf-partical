#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<list>


using namespace std;

string format(string temp){


    string str = "";
    int counter = 0;
    int flag = 0;
    for(int i = 0;i < temp.length(); ++i){


        if(temp[i] == '.'){

            ++counter;
        }
        if(temp[i] == '/'){

            flag = 1;
        }
    }


    if(flag == 1){



        int index = temp.find('/');

        str = temp.substr(0,index);

        for(int i = 0; i < 3 - counter; ++i){

            str += ".0";

        }
        str += '/';
        str += temp.substr(index+1);

    }
    else{

        str = temp;
        for(int i = 0; i < 3 - counter ; ++i){

            str += ".0";
        }
        str += '/';

        str += to_string((1+counter)*8);

    }

    return str;
}

long long getIPNum(string o,int index);

bool compare(string o1,string o2){




    int index1 = o1.find('/');
    int index2 = o2.find('/');


    string temp11 = o1.substr(index1+1);
    string temp22 = o2.substr(index2+1);

    long long temp1 = getIPNum(o1,index1);
    long long temp2 = getIPNum(o2,index2);

    if(temp1 < temp2){

        return true;
    }
    else if(temp1 == temp2){

        if(temp11 < temp22){

            return true;
        }
        else{

            return false;
        }
    }
    else{

        return false;
    }
}

long long getIPNum(string o,int index){

    string temp = o.substr(0,index);

    int indexTemp1 = 0;
    int indexTemp2 = 0;
    long long res = 0;
    for(int i = 0; i < 3;++i){

        indexTemp2 = temp.find('.',indexTemp1);

        string numStr = temp.substr(indexTemp1,indexTemp2);
        res += (long long)(atoi(numStr.c_str())*pow(256,3-i));

        if(i == 2){

            numStr = temp.substr(indexTemp2);
            res += (long long)(atoi(numStr.c_str()));

        }

        indexTemp1 = indexTemp2 + 1;
    }

    return res;
}


string combine(string o1,string o2){

    int index1 = o1.find('/');
    int index2 = o2.find('/');

    long long num1 = getIPNum(o1,index1);
    long long num2 = getIPNum(o2,index2);

    int len = atoi(o1.substr(index1+1).c_str());


    num1 = num1 >> 32 - len;
    num2 = num2 >> 32 - len;

    if(num1 == num2 ){

        return o1;
    }
    else{

        return "";
    }
}

bool judgeIP(string ip){

    int index = ip.find('/');
    int len = atoi(ip.substr(index+1).c_str());

    long long ipNum = getIPNum(ip,index);

    if(len > 32 || len < 0){

        return false;
    }
    else{

        if((ipNum << len) != 0){

            return false;
        }
        else{

            return true;
        }

    }
}


void toMerge(list<string>& res,string temp){

    string last = res.back();
    int index1 = last.find('/');
    int index2 = temp.find('/');

    string ip1 = last.substr(0,index1);
    string ip2 = temp.substr(0,index2);
    int len1 = atoi(last.substr(index1+1).c_str());
    int len2 = atoi(temp.substr(index2+1).c_str());


    if(len1 == len2){

        string newIP = ip1;
        int newLen = len1-1;
        string newStr = newIP+'/'+to_string(newLen);

        if(judgeIP(newStr)){

            if(combine(newStr,last)!= "" && combine(newStr,temp) != ""){

                res.pop_back();
                if(res.size() != 0){

                    toMerge(res,newStr);
                }
                else{

                    res.push_back(newStr);
                }
            }
            else{

                res.push_back(temp);
                return;
            }
        }
        else{

            res.push_back(temp);
            return;
        }
    }
    else{

        res.push_back(temp);
        return;
    }
}


int main(void){

    int n;
    scanf("%d",&n);

    vector<string> strs;
    char temp[19];

    for(int i = 0; i < n; ++i){


        scanf("%s",temp);
        strs.push_back(format(temp));

    }

    sort(strs.begin(),strs.end(),compare);

    vector<string> resTemp;
    resTemp.push_back(strs[0]);
    for(int i = 1; i < n; ++i){

        string temp = combine(resTemp.back(),strs[i]);

        if(temp == resTemp.back()){

            continue;
        }
        else{

            resTemp.push_back(strs[i]);
        }
    }


    list<string> res;
    res.push_back(resTemp[0]);

    for(int i = 1; i <resTemp.size();++i){

        toMerge(res,resTemp[i]);
    }

    for(list<string>::iterator i = res.begin(); i != res.end();++i){

        printf("%s\n",(*i).c_str());
    }

    return 0;
}
