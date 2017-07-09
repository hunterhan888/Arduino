wifi.setmode(wifi.STATION)
wifi.sta.config("name","password")
print(wifi.sta.getip())
led1 = 3
led2 = 4
gpio.mode(led1, gpio.OUTPUT)
gpio.mode(led2, gpio.OUTPUT)
srv=net.createServer(net.TCP)
--监听
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
        --这里输出一个简单的页面
        buf = buf.."<h1>点击开关控制</h1>";
        buf = buf.."<p>D4 <a href=\"?pin=ON2\"><button>ON</button></a>&nbsp;<a href=\"?pin=OFF2\"><button>OFF</button></a></p>";
        local _on,_off = "",""
        if(_GET.pin == "ON1")then
              gpio.write(led1, gpio.LOW);
        elseif(_GET.pin == "OFF1")then
              gpio.write(led1, gpio.HIGH);
        elseif(_GET.pin == "ON2")then
              gpio.write(led2, gpio.LOW);
        elseif(_GET.pin == "OFF2")then
              gpio.write(led2, gpio.HIGH);
        end
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)



 SDA_PIN = 6 -- sda pin, GPIO12
 SCL_PIN = 7 -- scl pin, GPIO14
 tmr.alarm(0, 10000, 1, function()
 si7021 = require("si7021")
 si7021.init(SDA_PIN, SCL_PIN)
 si7021.read(OSS)
 Hum = si7021.getHumidity()
 Temp = si7021.getTemperature()
T=Temp/100
H=Hum/100
print(string.format("Temp = %.2f",T))
print(string.format("Hum = %.2f",H))
     --定义数据变量格式
     PostData = "[{\"Name\":\"T\",\"Value\":\"" ..(string.format("%.2f",T)).. "\"},{\"Name\":\"H\",\"Value\":\"" ..(string.format("%.2f",H)).. "\"}]"
     --创建一个TCP连接
     socket=net.createConnection(net.TCP, 0)
     --域名解析IP地址并赋值
     socket:dns("www.lewei50.com", function(conn, ip)
      ServerIP = ip
      print("Connection IP:" .. ServerIP)
      end)
     --开始连接服务器
     socket:connect(80, ServerIP)
     socket:on("connection", function(sck) end)
     --HTTP请求头定义
     socket:send("POST /api/V1/gateway/UpdateSensors/01 HTTP/1.1\r\n" ..
        "Host: www.lewei50.com\r\n" ..
        "Content-Length: " .. string.len(PostData) .. "\r\n" ..
        "userkey: 847052eea02d4373894a37aea4139694 \r\n\r\n" ..
        PostData .. "\r\n")
     --HTTP响应内容
     socket:on("receive", function(sck, response)
      print(response)
      end) 

    end)