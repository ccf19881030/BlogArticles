## [C++版的网络数据包解析策略(升级版)](https://www.cnblogs.com/wjshan0808/p/6580638.html)
### 一、数据包格式形如下图所示:
![image](https://github.com/ccf19881030/BlogArticles/blob/master/C%2B%2B/网络编程/TCP_DataPackage.png)
### 二、代码
```cpp
int ReceiveFromRemoteEndPoint()
{     
    int nPackageDataLength = 0; 
    char *szPackageCleaner = NULL;
    char *szPackageIterator = NULL;
    do 
    {
        char *szReceiveArray = new char[RECEIVED_BUFFER_LENGTH]();
        int nReceiveLength = RECEIVED_BUFFER_LENGTH; 
        nReceiveLength = Receive(szReceiveArray, nReceiveLength, TIMEOUT);
        if (nReceiveLength <= 0)
        {
            Log("Recveived Time-Out(%d)...", nReceiveLength);   
            delete[] szReceiveArray;
            break;
        }
        Log("Received (%d) Bytes", nReceiveLength);  
    
        char *szReceive = szReceiveArray;

        do 
        {
            if(nPackageDataLength == 0)
            { 
                if(szReceive[0] != HEADER) 
                {
                    Log("Package Data Header-Analysis Error, Size(%d).", nReceiveLength); 
                    break;  
                }
                if(nReceiveLength < PACKHEADERLENGTH)
                {
                    Log("Package Data Length-Analysis Error, Size(%d).", nReceiveLength); 
                    break;   
                }

                //offset HEADER length
                char *szPackageDataLength = szReceive + sizeof(char);

                //包数据的长度(不包含包头长度)
                LengthResolve(szPackageDataLength, nPackageDataLength); 

                szPackageCleaner = new char[nPackageDataLength + PACKHEADERLENGTH + 1]();
                szPackageIterator = szPackageCleaner;

                memcpy(szPackageIterator, szReceive, PACKHEADERLENGTH);
                szPackageIterator += PACKHEADERLENGTH;

                szReceive += PACKHEADERLENGTH;
                nReceiveLength -= PACKHEADERLENGTH;
            } 
            //已接收的包数据长度 < 包数据长度 = 一个不完整的包 
            if(nReceiveLength < nPackageDataLength)
            {   
                memcpy(szPackageIterator, szReceive, nReceiveLength);

                szPackageIterator += nReceiveLength;
                nPackageDataLength -= nReceiveLength;

                szReceive += nReceiveLength;
                nReceiveLength -= nReceiveLength;
            }
            else//(nReceiveLength >= nPackageDataLength)
            {
                //已接收的包数据长度 == 包数据长度 = 一个完整的包  
                //已接收的包数据长度 > 包数据长度  = 至少有一个完整的包 + 至少一个数据片段 
                memcpy(szPackageIterator, szReceive, nPackageDataLength);
                //szPackageIterator += nPackageDataLength;
                Resolve(szPackageCleaner, (szPackageIterator - szPackageCleaner) + nPackageDataLength);

                szReceive += nPackageDataLength;
                nReceiveLength -= nPackageDataLength;

                nPackageDataLength = 0;

                delete[] szPackageCleaner;
                szPackageCleaner = NULL; 
            }            

        }while(nReceiveLength > 0);    

        delete[] szReceiveArray;
        Sleep(8);

    }while(IsStop);//Receiving
    
    if(szPackageCleaner != NULL)
        delete[] szPackageCleaner;
    
    return 0;
}
```

### 三、说明

网络数据包接收，最好是有超时机制的，比如2秒左右。
```cpp
if(nReceiveLength < PACKHEADERLENGTH)
{
         Log("Package Data Length-Analysis Error, Size(%d).", nReceiveLength);
         //这里会出现些问题 
         break;   
}
```

### 四、问题描述：
　　假如一个完整的数据包解析后，剩余的接收长度 < PACKHEADERLENGTH, 即包头HEADER校验正确，但是解析包数据长度的时接收到的数据不足以解析出

数据要接收的长度。此策略会丢弃包数据至下一个正确的包被正确解析，这个和缓冲区设置的长度是没有直接关系的，当然长度要大于PACKHEADERLENGTH.

要解决这个问题，可以在 break; 之前保存这个数据片，并在和下次接收的拼接解析数据长度。

此策略不是最好的更不是最优的，更好的可能就在你那里呢，有你的指点我相信会更好的。
