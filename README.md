# MIMXRT1060_GC6153
It's a gc6153 demo code based on IMXRT1062 with RGB565 output format.


# GC6153  
The GC6153 is a highly integrated CMOS image sensor, active pixel is 240x320. GC6153 outputs YUV/YCrCb 4:2:2 or RGB565 data through SPI interface.
It has a on-chip ISP.

Without HSYNC & VSYNC, Sync Code is packed into frame header and frame end. Sync_Code and SYNC_HEADER can be defined by yourself.

![image](https://user-images.githubusercontent.com/88095003/152766915-40f15d60-6d72-4f45-8e6b-2606686b1a8f.png)
![image](https://user-images.githubusercontent.com/88095003/152769229-7830951e-c733-4619-8182-6c0ec63a5b77.png)


Sync_Code0 -> Frame Start Packet(VSYNC)

Sync_Code1 -> Line Start Packet (HSYNC)

Sync_Code2 -> Data Packet

Sync_Code3 -> Frame End Packet



# image frame structure 
![image](https://user-images.githubusercontent.com/88095003/152768604-5bd7099f-5f98-4ea3-907e-0e34e1995d4f.png)


# Reference 
https://blog.csdn.net/tllfyj/article/details/114304661
