## [C++使用通配符查找文件(FindFirstFile)](https://www.cnblogs.com/chay/p/10888771.html)
## [C++使用通配符查找文件(FindFirstFile)](https://blog.csdn.net/faithzzf/article/details/54290084)
```cpp
BOOL SearchFilesByWildcard(WCHAR *wildcardPath)
{
	HANDLE hFile = INVALID_HANDLE_VALUE; 
	WIN32_FIND_DATA pNextInfo;  
 
	hFile = FindFirstFile(wildcardPath,&pNextInfo); 
	if(INVALID_HANDLE_VALUE == hFile)  
	{  
		return FALSE;  
	}  
 
	WCHAR infPath[MAX_PATH] = {0};
	if(pNextInfo.cFileName[0] != '.')
	{
		printf("Find result = %ws\r\n",pNextInfo.cFileName);
	}
 
	while(FindNextFile(hFile,&pNextInfo))  
	{  
		if(pNextInfo.cFileName[0] == '.')
		{
			continue;  
		}
 
		printf("Find result = %ws\r\n",pNextInfo.cFileName);
	}
 
	return FALSE;
}
 
int main(int argc,char* argv[])
{
	setlocale(LC_ALL,"chs");
 
	//查找 abc开头的txt文件
	printf("Search 1:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*.txt");
	printf("\r\n");
 
	//查找 abc开头的文件
	printf("Search 2:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*");
	printf("\r\n");
 
	//查找jnt文件
	printf("Search 3:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*.jnt");
	printf("\r\n");
 
	//查找文件名为4个字符的txt文件
	printf("Search 4:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\????.txt");
	printf("\r\n");
 
	//查找包含"档案"的文件
	printf("Search 5:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*档案*");
	printf("\r\n");
 
	getchar();
	return 0;
}
```
