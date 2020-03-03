#include <stdio.h>
#include "cJSON.h"


cJSON * get_json_object(char * file_name)
{
	FILE * fp;
	long len;
	char * content;
	cJSON * result;

	fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	content = (char *) malloc(len + 1);
	fread(content, 1, len, fp);
	fclose(fp);
	result = cJSON_Parse(content);
	free(content);
	return result;
}

void print_json(cJSON * root)//以递归的方式打印json的最内层键值对
{
    for(int i = 0; i<cJSON_GetArraySize(root); i++)   //遍历最外层json键值对
    {
        cJSON * item = cJSON_GetArrayItem(root, i);        
        if(cJSON_Object == item->type)      //如果对应键的值仍为cJSON_Object就递归调用printJson
            print_json(item);
        else                                //值不为json对象就直接打印出键和值
        {
            printf("%s->", item->string);
            printf("%s\n", cJSON_Print(item));
        }
    }
}


int main(int argc, char const *argv[])
{	
    cJSON * root = NULL;
    cJSON * item = NULL;
    root = get_json_object(argv[1]);
    //root = cJSON_Parse(argv[1]);    // for afl-fuzz


    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    else
    {
    	printf("有格式打印: %s\n", cJSON_Print(root));
    	printf("原始文件: %s\n", cJSON_PrintUnformatted(root));

    	item = cJSON_GetObjectItem(root, "animal");
    	if(item)
    	{
    		printf("筛选一: %s\n", cJSON_Print(item));
    	}

    	item = cJSON_GetObjectItem(item, "dog");
    	if(item)
    	{
    		printf("筛选二: %s\n", cJSON_Print(item));
    		printf("%s:", item->string);   //看一下cjson对象的结构体中这两个成员的意思
        	printf("%s\n", item->valuestring);
    	}

    	printf("打印json所有最内层键值对: %s\n");
    	print_json(root);
    }
	return 0;
}