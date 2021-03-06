//
// Created by wy on 2021/2/22.
//

#include "registerCenter.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100
struct member{
    char* serverName;
    char* addr;
};
void registers(char* serverName,char* addr);
void getMessage(char* serverName);
void updateServerByKey(char* serverName);
void deleteServerByKey(char* serverName);
void openf();

void openf()//打开文件
{
    FILE *f1;
    char c;

    f1=fopen("infor.txt","r");
    while ((c=getc(f1))!=EOF)
        printf("%c",c);
    fclose(f1);
    //getch();
    return;
}

int readfile()//文件读取
{
    int i=0;
    FILE  *p;
    struct members{
        char serverName[10];
        char addr[20];
    };
    struct members infor2[MAX];
    p=fopen("infor.txt","r");
    if ((p==NULL)){
        printf("\nCan't open the file!");
        getchar();
        exit(1);
    }
    while (!feof(p))
    {
        fscanf(p,"%s%s",infor2[i].serverName,infor2[i].addr);
        i++;
    }
    fclose(p);
    return i;
}
void getMessage(char* serverName){
    FILE *p;
    bool idsn= false;//看serverName是否存在
    struct member infor[MAX];
    int j=readfile();
    //读取文件内容
    p=fopen("infor.txt","r");
    if ((p==NULL))
    {
        printf("\nCan't open the file");
        exit(1);
    }
    for (int i = 0; i < j; ++i) {
        fscanf(p,"%s%s",infor[i].serverName,infor[i].addr);
        if (serverName==infor[i].serverName){
            idsn= true;
            //若serverName对应的addr为空,报错
            if (infor[i].addr==NULL){
                printf("\naddr is NULL!");
                exit(1);
            }
        }
    }
    //如果servrName不存在，创建serverName
    if (idsn== false){
        char* port="127.0.0.1:10010";//待定
        registers(serverName,port);//注册新的
    }
    return;
}
//注册
void registers(char *serverName,char *addr){
    FILE *fp;
    struct member infor;
    /*printf("Please enter memeber'information:\n");
    for (int j = 0; j < MAX; ++j) {
        printf("serverName:");
        scanf("%s",infor[i].serverName);
        printf("addr:");
        scanf("%s",infor[i].addr);
        count+=1;
    }*/
    infor.serverName=serverName;
    infor.addr=addr;
    fp=fopen("infor.txt","ab");
    fwrite(&infor,sizeof(struct member),1,fp);
    fclose(fp);
    getchar();
    return;
}

void updateServerByKey(char* serverName)//服务保护和检查机制
{
    FILE *fp;
    int i=0,count=0;
    struct member infor[50];
    fp=fopen("infor.txt","rb");
    if (fp==NULL)
    {
        printf("\nCan't open the file");
        exit(1);
    }
    while (1){
        if (feof(fp))
        {
            printf("Have listed all information!\n");//显示所有会员信息
            break;
        }
        fread(&infor[i],sizeof(struct member),1,fp);
        i++;
        count+=1;
    }
    fclose(fp);
    for (int j = 0; j < count; ++j) {
        if (strcmp(infor[i].serverName,serverName)==0){

        }
    }

}

void deleteServerByKey(char* serverName)//服务停止时删除
{
    struct member infor[MAX],*p;
    FILE *fp;
    int i=0;
    fp=fopen("infor.txt","rb");
    if (fp==NULL)
    {
        printf("\nCan't open the file");
        exit(1);
    }
    //记录servername的位置 i
    /*while (1)
    {
        fread(&infor[i],sizeof(struct member),1,fp);
        if (strcmp(infor[i].serverName,serverName)){
            fwrite(&infor[i],sizeof(struct member),1,fp);
            fclose(fp);
            break;
        }
    }*/
}


int main() {

    return 0;
}
