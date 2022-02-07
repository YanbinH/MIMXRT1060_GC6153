# MIMXRT1060_GC6153
It's a gc6153 demo code based on IMXRT1062 with RGB565 output format.


# GC6153  
The GC6153 is a highly integrated CMOS image sensor, active pixel is 240x320. GC6153 outputs YUV/YCrCb 4:2:2 or RGB565 data through SPI interface.
It has a on-chip ISP.

Without HSYNC & VSYNC, Sync Code is packed into frame header and frame end.

![image](https://user-images.githubusercontent.com/88095003/152766915-40f15d60-6d72-4f45-8e6b-2606686b1a8f.png)

Sync Code0 -> Frame Start Packet(VSYNC)
Sync Code1 -> Line Start Packet (HSYNC)
Sync Code2 -> Data Packet
Sync Code3 -> Frame End Packet

