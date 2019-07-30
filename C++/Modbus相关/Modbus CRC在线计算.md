## [CRC（循环冗余校验）在线计算-ip33.com](http://www.ip33.com/crc.html)
CRC校验（循环冗余校验）小知识
CRC即循环冗余校验码（Cyclic Redundancy Check）：是数据通信领域中最常用的一种查错校验码，其特征是信息字段和校验字段的长度可以任意选定。循环冗余检查（CRC）是一种数据传输检错功能，对数据进行多项式计算，并将得到的结果附在帧的后面，接收设备也执行类似的算法，以保证数据传输的正确性和完整性。

CRC算法参数模型解释： 
NAME：参数模型名称。 
WIDTH：宽度，即CRC比特数。 
POLY：生成项的简写，以16进制表示。例如：CRC-32即是0x04C11DB7，忽略了最高位的"1"，即完整的生成项是0x104C11DB7。 
INIT：这是算法开始时寄存器（crc）的初始化预置值，十六进制表示。 
REFIN：待测数据的每个字节是否按位反转，True或False。 
REFOUT：在计算后之后，异或输出之前，整个数据是否按位反转，True或False。 
XOROUT：计算结果与此参数异或后得到最终的CRC值。

其他相关工具：LRC校验BCC校验

## [Modbus RTU CRC](http://cht.nahua.com.tw/index.php?url=http://cht.nahua.com.tw/software/crc16/&key=Modbus,%20RTU,%20CRC16&title=計算%20Modbus%20RTU%20CRC16)
Modbus RTU CRC16算法的描述：
Modbus RTU CRC
計算 Modbus RTU 檢查碼

RTU 檢查碼(CRC)計算, 運算規則如下:
步驟1: 令 16-bit 暫存器 (CRC 暫存器) = 0xFFFF。
步驟2: Exclusive OR 第一個 8-bit byte 的訊息指令與低位元 16-bit CRC 暫存器, 做 Exclusive OR 將結果存入 CRC 暫存器內。
步驟3: 右移一位 CRC 暫存器, 將 0 填入高位元處。
步驟4: 檢查右移的值, 如果是 0 將步驟3 的新值存入 CRC 暫存器內, 否則 Exclusive OR 0xA001 與 CRC 暫存器, 將結果存入 CRC 暫存器內。
步驟5: 重複步驟3~步驟4, 將 8-bit 全部運算完成。
步驟6: 重複步驟2~步驟5, 取下一個 8-bit 的訊息指令, 直到所有訊息指令運算完成。最後, 得到的 CRC 暫存器的值, 即是 CRC 的檢查碼。
值得注意的是 CRC 的檢查碼必須交換放置於訊息指令的檢查碼中。

### 使用Boost库计算Modbus RTU CRC16
```cpp
#include <boost/crc.hpp>

typedef boost::crc_optimal<16, 0x8005, 0xFFFF, 0, true, true>	mbscrc_16_type;
// 计算modbus中CRC16校验值
static uint16 jisuanCRC16(const void* buffer, size_t byte_size)
{
		mbscrc_16_type crc16;
		crc16.process_bytes(buffer, byte_size);
		return crc16();
}
```
