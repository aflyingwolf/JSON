#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "cJSON.h"

//读文件内容
char* readFile(char *fileName)
{
    if(fileName == NULL)
        return NULL;

    FILE *pFile = fopen(fileName, "r");
    if(pFile == NULL)
        return NULL;

    //移动文件指针到文件末尾
    fseek(pFile, 0, SEEK_END);
    //获取文件长度
    int length = ftell(pFile);
    //定义文件指针
    char *pBuf = (char *)malloc(length + 1);
    if(pBuf == NULL)
        return NULL;

    //把指针移动到文件开头
    rewind(pFile);
    //读文件内容
    fread(pBuf, 1, length, pFile);
    //文件末尾添0
    pBuf[length] = 0;

    //关闭文件
    fclose(pFile);

    return pBuf;
}

//写文件
void writeFile(char *fileName, char *fileData)
{
    if(fileName == NULL || fileData == NULL)
        return ;

    FILE *pFile = fopen(fileName, "w");
    if(pFile == NULL)
        return ;

    fwrite(fileData, 1, strlen(fileData), pFile);
    fflush(pFile);

    fclose(pFile);
}

int main()
{
    char *str = readFile("../test-json/test1.json");
    if(str != NULL)
    {
        cJSON *root = cJSON_Parse(str);
        printf("name : %s\n", cJSON_GetObjectItem(root, "name")->valuestring);
        printf("sex : %s\n", cJSON_GetObjectItem(root, "sex")->valuestring);
        cJSON_Delete(root);
        //printf("%s\n", str);
        free(str);
    }
    printf("\n");

    str = readFile("../test-json/test2.json");
    if(str != NULL)
    {
        cJSON *root = cJSON_Parse(str);
        cJSON *val = cJSON_GetObjectItem(root, "info");
        printf("info: {\n");
        printf("\tname : %s\n", cJSON_GetObjectItem(val, "name")->valuestring);
        printf("\tsex : %s\n", cJSON_GetObjectItem(val, "sex")->valuestring);
        printf("\tage : %d\n", cJSON_GetObjectItem(val, "age")->valueint);
        printf("\theight : %f\n", cJSON_GetObjectItem(val, "height")->valuedouble);
        printf("      }\n");

        cJSON_Delete(root);
        //printf("%s\n", str);
        free(str);
    }
    printf("\n");

    str = readFile("../test-json/test3.json");
    if(str != NULL)
    {
        cJSON *root = cJSON_Parse(str);
        cJSON *ary = cJSON_GetObjectItem(root, "class");
        printf("class: [\n");

        //获取数组个数
        int length = cJSON_GetArraySize(ary);
        int i = 0;
        for(; i < length; ++i)
        {
            cJSON *child = cJSON_GetArrayItem(ary, i);
            printf("\tname : %s, ", cJSON_GetObjectItem(child, "name")->valuestring);
            printf("sex : %s\n", cJSON_GetObjectItem(child, "sex")->valuestring);
        }
        printf("       ]\n");

        cJSON_Delete(root);
        //printf("%s\n", str);
        free(str);
    }
    printf("\n");

    str = readFile("../test-json/test4.json");
    if(str != NULL)
    {
        cJSON *root = cJSON_Parse(str);
        cJSON *ary = cJSON_GetObjectItem(root, "info");
        printf("info: {\n");
        printf("\tname : %s\n", cJSON_GetObjectItem(ary, "name")->valuestring);
        printf("\tsex : %s\n", cJSON_GetObjectItem(ary, "sex")->valuestring);
        printf("\tage : %d\n", cJSON_GetObjectItem(ary, "age")->valueint);
        printf("      }\n");

        ary = cJSON_GetObjectItem(root, "class");
        printf("class: [\n");

        //获取数组个数
        int length = cJSON_GetArraySize(ary);
        int i = 0;
        for(; i < length; ++i)
        {
            cJSON *child = cJSON_GetArrayItem(ary, i);
            printf("\tname : %s, ", cJSON_GetObjectItem(child, "name")->valuestring);
            printf("sex : %s\n", cJSON_GetObjectItem(child, "sex")->valuestring);
        }
        printf("       ]\n");

        cJSON_Delete(root);
        //printf("%s\n", str);
        free(str);
    }
    printf("\n");

    printf("Hello World!\n");
    return 0;
}
