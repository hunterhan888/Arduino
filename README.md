# Arduino
* This is some Arduino code.
* 一些Arduino的代码,实现超声波小车避障,温湿度采集并通过WiFi上传到乐为物联网平台

*.ino是Arduino文件

### WiFi模块采用NodeMcu
* NodeMcu使用Lua语言
* 使用NodeMcu Studio 2015进行编辑解析
* init.lua是启动文件,需要先刷入NodeMcu
* dht11.lua是dht11温湿度传感器的驱动文件
* si7021.lua是si7021温湿度传感器的驱动文件
* SI7021_lewei.lua实现将SI7021的数据上传至乐为物联网平台
