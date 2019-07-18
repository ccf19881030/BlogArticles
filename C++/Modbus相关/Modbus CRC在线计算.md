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
