#include <iostream>
#include <string>
#include <vector>
typedef std::string String;
#include <io.h>
#include <Windows.h>

typedef struct FileInfo_
{
	_finddata_t dd;
	String filePath;	// 文件所在路径
}FileInfo_;

typedef std::vector<FileInfo_> VectorFile;


// fileDir：需要查找的目录（比如D:\\01_Web\\DataFTP\\LD\\SW4200001）
// ruleFile：文件规则（比如*.json）
// fileVec：存放结果的列表
int getLocalFiles(const String fileDir, const String ruleFile, VectorFile& fileVec)
{
	// 递归查找目录
	long handle = 0;                                       //用于查找的句柄
	_finddata_t fdd;									   //文件信息的结构体

	String pathName = fileDir;
	String exdName = ruleFile;

	// 在目录后面加上"\\*.*"进行第一次搜索
	handle = _findfirst(pathName.append("\\*.*").c_str(), &fdd);
	if (-1 == handle)	// 检查是否成功
	{
		return -1;
	}

	// 递归循环查找其他符合的文件名，找到则放入文件列表中
	while (_findnext(handle, &fdd) == 0)
	{
		if (fdd.attrib & _A_SUBDIR) {	// 如果是目录(则递归遍历)
			// 如果是目录.或者..，则继续
			if (strcmp(fdd.name, ".") == 0 || strcmp(fdd.name, "..") == 0)
			{
				continue;
			}
			else  // 如果目录是20190627等，则递归遍历，查找符合文件规则的文件,否则继续
			{
				// 获取当前的年份
				String currentYear;
				SYSTEMTIME st;
				GetLocalTime(&st);
				currentYear = std::to_string(st.wYear);
				// 当前目录名
				String subDir = fdd.name;
				if (subDir.find(currentYear) == std::string::npos)	// 如果目录不包含当前年份如2019，则忽略继续遍历
				{
					continue;
				}
				else    // 若目录名中包含当前的年份如2019，则递归查找
				{
					String tempDir = fileDir + "\\" + subDir;
					getLocalFiles(tempDir, ruleFile, fileVec);
				}
			}
		}
		else  // 如果是文件
		{
			// 如果是文件，判断是否符合文件规则
			String fileName = fdd.name;
			if (fileName.find(ruleFile) != std::string::npos)
			{
				// 符合条件，则加入列表
				FileInfo_ fileItem;
				fileItem.filePath = fileDir;
				fileItem.dd = fdd;
				fileVec.push_back(fileItem);
			}
		}
	}

	_findclose(handle);		// 关闭搜索句柄

	return 0;
}

using namespace std;

int main(int argc, char *argv[])
{
	//String fileDir = "D:\\01_Web\\DataFTP\\LD\\SW4200001";

	String fileDir = "F:\\AVORS\\AVORS";
	String ruleFile = ".json";

	VectorFile fileVec;
	getLocalFiles(fileDir, ruleFile, fileVec);

	int iCount = 0;
	for (auto it = fileVec.begin(); it != fileVec.end(); ++it)
	{
		String fileDir = (*it).filePath;
		String fileName = (*it).dd.name;
		unsigned long fileSize = (*it).dd.size;
		__int64 lastWriteTime = (*it).dd.time_write;
		std::cout << "第" << ++iCount << "个文件信息：" << std::endl;
		std::cout << "文件路径：" << fileDir << "|" << "文件名：" << fileName
				<< "|" << "文件大小：" << fileSize <<"字节" << "|"
			    << "文件最后写入时间："  << lastWriteTime << std::endl;
	}

	system("pause");

	return 0;
}
