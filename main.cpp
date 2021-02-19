#include "main.h"


/*char* ToRedis::insert(char* key, string value) {
    //返回的redis指令集 初始化select MASTER
    char* toredis="*3\r\n$3\r\nset\r\n$";
    string key_=key;
    string keysize=tos(key_.size());
    string valuesize=tos(value.size());
    *toredis+keysize+"\r\n"+key_+"\r\n$"+valuesize+"\r\n"+value+"\r\n,";
    *//*cout<<key<<endl;
    string key_=key;
    //得到表名
    const char *split = ",; _";
    char *p2 = strtok(key,split);
    string tablename=p2;
    cout<<tablename<<endl;
    int size=tablename.size();
    // int 转 string
    string size1=tos(size);
    string num=tos(slave);
    string keysize=tos(key_.size());
    string valuesize=tos(value.size());
    //set 表名　num(2-15循环)
    //select num
    if (slave<10){
        *toredis+"*3\r\n$3\r\nset\r\n$"+size1+"\r\n"+tablename+"\r\n$1\r\n"+num+"\r\n,";
        *toredis+"*2\r\n$6\r\nselect\r\n$1\r\n"+num+"\r\n,";
        slave++;
    }else{
        *toredis+"*3\r\n$3\r\nset\r\n$"+size1+"\r\n"+tablename+"\r\n$2\r\n"+num+"\r\n,";
        *toredis+"*2\r\n$6\r\nselect\r\n$2\r\n"+num+"\r\n,";
        slave++;
        if (slave=16)
            slave=2;
    }
    //set key value
    *toredis+"*3\r\n$3\r\nset\r\n$"+keysize+"\r\n"+key_+"\r\n$"+valuesize+"\r\n"+value+"\r\n,";*//*
    //返回命令集
    return toredis;
}*/
char* ToRedis::insert(char str[]){
    char* toredis=",";
    bool iskey=true;
    //分隔符拆分
    const char *split = ",;";
    char *p2 = strtok(str,split);
    while( p2 != NULL )
    {
        cout<<p2<<endl;
        //p2 = strtok(NULL,split);
        char *firstName ="*3\r\n$3\r\nset\r\n$";
        char *r="\r\n";
        string p3=p2;
        //string size=tos(p3.size());
        char *size;
        switch (p3.size()) {
            case 1: size="1";
            case 2: size="2";
            case 3: size="3";
            case 4: size="4";
            case 5: size="5";
            case 6: size="6";
            case 7: size="7";
            case 8: size="8";
        }
//    char *firstName = "Theo";
//    char *lastName = "Tsao";
//    char *name = (char *) malloc(strlen(firstName) + strlen(lastName));
//    strcpy(name, firstName);
//    strcat(name, lastName);
//    printf("%s\n", name);
        if (iskey== true){
            char *lastName =jonit(firstName,size);
            char *lastName1=jonit(lastName,r);
            char *lastName2=jonit(lastName1,p2);
            char *r1="\r\n$";
            toredis=jonit(lastName2,r1);
            //*toredis+"*3\r\n$3\r\nset\r\n$"+size+"\r\n"+p2+"\r\n$";
            cout<<1<<endl;
            cout<<toredis<<endl;
            iskey= false;
        } else{
            char *lastName =jonit(toredis,size);
            char *lastName1=jonit(lastName,r);
            char *lastName2=jonit(lastName1,p2);
            char *r1="\r\n,";
            toredis=jonit(lastName2,r1);
            //*toredis+size+"\r\n"+p3+"\r\n,";
            cout<<2<<endl;
            cout<<toredis<<endl;
            iskey=true;
        }
        p2 = strtok(NULL,split);
    }

    return toredis;
}
char* ToRedis::deleter(char key[]) {
    char* toredis="*2\r\n$3\r\ndel\r\n$";
    char* r="\r\n";
    string key_=key;
    char *size;
    switch (key_.size()) {
        case 1: size="1";
        case 2: size="2";
        case 3: size="3";
        case 4: size="4";
        case 5: size="5";
        case 6: size="6";
        case 7: size="7";
        case 8: size="8";
    }
    toredis=jonit(toredis,size);
    toredis=jonit(toredis,r);
    toredis=jonit(toredis,key);
    char* r1="\r\n,";
    toredis=jonit(toredis,r1);
    //*toredis+size+"\r\n"+key_+"\r\n";
    const char *split = ",;";
    char *p2 = strtok(str,split);
    while( p2 != NULL )
    {
        cout<<p2<<endl;
        //p2 = strtok(NULL,split);
        char *firstName ="*3\r\n$3\r\nset\r\n$";
        char *r="\r\n";
        string p3=p2;
        //string size=tos(p3.size());
        char *size;
        switch (p3.size()) {
            case 1: size="1";
            case 2: size="2";
            case 3: size="3";
            case 4: size="4";
            case 5: size="5";
            case 6: size="6";
            case 7: size="7";
            case 8: size="8";
        }

        if (iskey== true){
            char *lastName =jonit(firstName,size);
            char *lastName1=jonit(lastName,r);
            char *lastName2=jonit(lastName1,p2);
            char *r1="\r\n$";
            toredis=jonit(lastName2,r1);
            //*toredis+"*3\r\n$3\r\nset\r\n$"+size+"\r\n"+p2+"\r\n$";
            cout<<1<<endl;
            cout<<toredis<<endl;
            iskey= false;
        } else{
            char *lastName =jonit(toredis,size);
            char *lastName1=jonit(lastName,r);
            char *lastName2=jonit(lastName1,p2);
            char *r1="\r\n,";
            toredis=jonit(lastName2,r1);
            //*toredis+size+"\r\n"+p3+"\r\n,";
            cout<<2<<endl;
            cout<<toredis<<endl;
            iskey=true;
        }
        p2 = strtok(NULL,split);
    }

    return toredis;
}

int main() {
    /*string s="abc";
    char ss[]="student_1_name";
    ToRedis toRedis;
    char* str=toRedis.insert(ss,s);
    s=str;
    std::cout << str<< std::endl;*/
    char str[]= "I,am,a,student; hello world!";
    ToRedis toRedis;
    char* s=toRedis.insert(str);
    cout<<s<<endl;
    return 0;
}
