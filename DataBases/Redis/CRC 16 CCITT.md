## [CRC 16 CCITT In C#](http://www.sanity-free.com/133/crc_16_ccitt_in_csharp.html)
Once again I found myself needing another type of CRC algorithm in C#. I found one on code project, but their implementation of CRC 16 CCITT didn't produce that checksum I needed. 
Come to find out there are different methods to calculate CRC 16 CCITT which use different initial values for the crc.

I ended up writing this one for my own purposes: 
```C#
using System;

public enum InitialCrcValue { Zeros, NonZero1 = 0xffff, NonZero2 = 0x1D0F }

public class Crc16Ccitt {
    const ushort poly = 4129;
    ushort[] table = new ushort[256];
    ushort initialValue = 0;

    public ushort ComputeChecksum(byte[] bytes) {
        ushort crc = this.initialValue;
        for(int i = 0; i < bytes.Length; ++i) {
            crc = (ushort)((crc << 8) ^ table[((crc >> 8) ^ (0xff & bytes[i]))]);
        }
        return crc;
    }

    public byte[] ComputeChecksumBytes(byte[] bytes) {
        ushort crc = ComputeChecksum(bytes);
        return BitConverter.GetBytes(crc);
    }

    public Crc16Ccitt(InitialCrcValue initialValue) {
        this.initialValue = (ushort)initialValue;
        ushort temp, a;
        for(int i = 0; i < table.Length; ++i) {
            temp = 0;
            a = (ushort)(i << 8);
            for(int j = 0; j < 8; ++j) {
                if(((temp ^ a) & 0x8000) != 0) {
                    temp = (ushort)((temp << 1) ^ poly);
                } else {
                    temp <<= 1;
                }
                a <<= 1;
            }
            table[i] = temp;
        }
    }
}
```

This was used for testing during the time we were looking at the Battlefield 2142 auth token, and were trying to figure out what the last 2 bytes of that token were made of.  Battlefield 2142's auth token uses the CRC 16 CCITT with the initial value of 0 (new Crc16Ccitt(InitialCrcValue.Zeros) in the above class. 

If you need for this code to be CLS compliant, you can change the method signature's return type from ushort to int and it will operate the same (the ushort crc value will be implicitly converted from ushort to int)

Links to the other C# CRC implementations CRC32, CRC16, CRC16-CCITT Kermit, and CRC8 
