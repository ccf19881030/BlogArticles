## Modbus CRC16 计算

###  1、ANSI CRC16计算方法
#### (1)、参考《HJ 212-2017.pdf》
中华人民共和国国家环境保护标准  污染物在线监控（监测）系统数据传输标准
附 录 A 
（规范性附录） 
循环冗余校验（CRC）算法 
CRC 校验（Cyclic Redundancy Check）是一种数据传输错误检查方法。本标准采用 ANSI CRC16，
简称 CRC16。 
CRC16 码由传输设备计算后加入到数据包中。接收设备重新计算接收数据包的 CRC16 码，并与接
收到的 CRC16 码比较，如果两值不同，则有误。 

#### (2)、CRC16 校验字节的生成步骤如下： 
1) CRC16 校验寄存器赋值为 0xFFFF； 
2) 取被校验串的第一个字节赋值给临时寄存器； 
3) 临时寄存器与 CRC16 校验寄存器的高位字节进行“异或”运算，赋值给 CRC16 校验寄存器； 
4) 取 CRC16 校验寄存器最后一位赋值给检测寄存器； 
5) 把 CRC16 校验寄存器右移一位； 
6) 若检测寄存器值为 1，CRC16 校验寄存器与多项式 0xA001 进行“异或”运算，赋值给 CRC16
校验寄存器； 
7) 重复步骤 4~6，直至移出 8 位； 
8) 取被校验串的下一个字节赋值给临时寄存器； 
9) 重复步骤 3~8，直至被校验串的所有字节均被校验； 
10) 返回 CRC16 校验寄存器的值。 
校验码按照先高字节后低字节的顺序存放。

#### (3)、CRC 校验算法示例：
```cpp
/**************************************************************************************** 
函 数: CRC16_Checkout 
描 述: CRC16 循环冗余校验算法。
参 数 一: *puchMsg：需要校验的字符串指针
参 数 二: usDataLen：要校验的字符串长度
返 回 值: 返回 CRC16 校验码
****************************************************************************************/ 
unsigned int CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen ) 
{ 
unsigned int i,j,crc_reg,check; 
crc_reg = 0xFFFF; 
for(i=0;i<usDataLen;i++) 
{ 
crc_reg = (crc_reg>>8) ^ puchMsg[i]; 
 for(j=0;j<8;j++) 
{ 
 check = crc_reg & 0x0001; 
 crc_reg >>= 1; 
 if(check==0x0001) 
HJ 212-2017 
{ 
 crc_reg ^= 0xA001; 
 } 
 } 
} 
return crc_reg; 
} 
```

#### (4)、示例：
##0101QN=20160801085857223;ST=32;CN=1062;PW=100000;MN=010000A8900016F000169DC0;Flag=5
;CP=&&RtdInterval=30&&1C80\r\n，其中 1C08 为 CRC16 校验码，是对数据段 QN=20160801085857223; 
ST=32;CN=1062;PW=100000;MN=010000A8900016F000169DC0;Flag=5;CP=&&RtdInterval=30&& 进 行
CRC16 校验所得的校验码。

### 2、Modbus RTU CRC16校验
#### (1)、Modbus协议格式 基本说明
校验通讯用的Modbus RTU CRC16计算器，根据地址码功能码及用户数据，校验对应的CRC16值。
Modbus RTU协议分为Modbus RTU主站协议和Modbus RTU从站协议。Modbus通信是由功能码来控制的，主站直接访问从站的数据区。
ModBus 通信协议的CRC ( 冗余循环校验码）含2个字节, 即 16 位二进制数。CRC码由发送设备计算, 放置于所发送信息帧的尾部。
接收设备再重新计算所接收信息的CRC, 比较计算得到的CRC是否与接收到的CRC相符, 如果两者不相符, 则认为数据出错。

#### (2)、crc算法描述
1、  加载一值为0XFFFF的16位寄存器，此寄存器为CRC寄存器。
2、  把第一个8位二进制数据（即通讯信息帧的第一个字节）与16位的CRC寄存器的相异或，异或的结果仍存放于该CRC寄存器中。
3、  把CRC寄存器的内容右移一位，用0填补最高位，并检测移出位是0还是1。
4、  如果移出位为零，则重复第三步（再次右移一位）；如果移出位为1，CRC寄存器与0XA001进行异或。
5、  重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理。
6、  重复步骤2和5，进行通讯信息帧下一个字节的处理。
7、  将该通讯信息帧所有字节按上述步骤计算完成后，得到的16位CRC寄存器的高、低字节进行交换
8、  最后得到的CRC寄存器内容即为：crc校验码

#### (3)、crc算法实现
此处CRC校验采用的多项式为g(x)=x16+x15+x2+1
```cpp
unsigned short crc16_calculate(unsigned char *p,unsigned int len)
{
  unsigned short wcrc = 0XFFFF;//16位crc寄存器预置

  unsigned char temp;

  int i=0,j=0;//计数

  for(i=0;i<len;i++)//循环计算每个数据
  {

    temp=*p & 0X00FF;//将八位数据与crc寄存器异或

    p++;//指针地址增加，指向下个数据

    wcrc^=temp;//将数据存入crc寄存器

    for(j=0;j<8;j++)//循环计算数据的
    {
      if(wcrc&0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。
      {
        wcrc>>=1;//先将数据右移一位

        wcrc^=0XA001;//与上面的多项式进行异或
      }
      else//如果不是1，则直接移出
      {
        wcrc>>=1;//直接移出
      }
    }
  }

  temp=wcrc; //crc的值
  
  return temp;

  //Temp中即存放了CRC的高八位和低八位

  unsigned char CRC[2];//定义数组

  CRC[0]=wcrc;//crc的低八位

  CRC[1]=wcrc>>8;//crc的高八位
}
```
// mbs.h
```cpp
#pragma once

#include <boost/crc.hpp>
#include <algorithm>
#include "type.h"

namespace Modbus {
	// Modbus RTU CRC16校验
	typedef boost::crc_optimal<16, 0x8005, 0xFFFF, 0, true, true>	mbscrc_16_type;
	// 计算modbus中CRC16校验值
	static uint16 jisuanCRC16(const void* buffer, size_t byte_size)
	{
		mbscrc_16_type crc16;
		crc16.process_bytes(buffer, byte_size);
		return crc16();
	}

	// 采用 ANSI CRC16(HJ 212-2017)
	//CRC 校验算法示例：
	/****************************************************************************************
		函 数: CRC16_Checkout
		描 述: CRC16 循环冗余校验算法。
		参 数 一: *puchMsg：需要校验的字符串指针
		参 数 二: usDataLen：要校验的字符串长度
		返 回 值: 返回 CRC16 校验码
		****************************************************************************************/
	static unsigned int CRC16_Checkout(unsigned char *puchMsg, unsigned int usDataLen)
	{
		unsigned int i, j, crc_reg, check;
		crc_reg = 0xFFFF;
		for (i = 0; i < usDataLen; i++)
		{
			crc_reg = (crc_reg >> 8) ^ puchMsg[i];
			for (j = 0; j < 8; j++)
			{
				check = crc_reg & 0x0001;
				crc_reg >>= 1;
				if (check == 0x0001)
				{
					crc_reg ^= 0xA001;
				}
			}
		}
		return crc_reg;
	}

}
```
