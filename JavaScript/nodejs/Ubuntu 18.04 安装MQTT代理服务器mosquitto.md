## [Ubuntu 18.04 安装MQTT代理服务器mosquitto](https://blog.csdn.net/lx121451/article/details/81137408)
1. 引入mosquitto仓库并更新

sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa

sudo apt-get update

2. 执行以下命令安装mosquitto包

sudo apt-get install mosquitto

3. 安装mosquitto开发包

sudo apt-get install libmosquitto-dev

4. 安装mosquitto客户端

sudoapt-get install mosquitto-clients

5. 查询mosquitto是否正确运行

sudo service mosquitto status

6. 本机测试

打开一个终端，执行以下命令订阅主题"mqtt"

mosquitto_sub -h localhost -t "mqtt" -v

 

打开另外一个终端，发布消息到主题 “mqtt”

mosquitto_pub -h localhost -t "mqtt" -m "Hello MQTT"
