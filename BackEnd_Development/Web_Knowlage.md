# Web Knowlage

Web传输数据的两种格式：JSON、XML
Node.js
基于Node.js的Web框架: Express、
实现网页更新
AJAX = Asynchronous JavaScript and XML
1. XHR(XMLHttpRequest)用于和服务器交互，可以在操作界面中，不刷新页面和不影响用户操作的情况下，请求特定的URL接口，获取数据动态更新页面的局部内容(XHR在AJAX编程中被大量使用)

## 参考
1. [XMLHttpRequest](https://developer.mozilla.org/zh-CN/docs/Web/API/XMLHttpRequest)
# OSI Model
1. Application: 应用层 Protocols: HTTP、HTTPS、FTP、NFS、TELENT、DHCP、SMTP等
2. Presentation: 表示层
   1. Translation: 将应用层接收到的数据转换为机器可以识别的二进制形式
   2. Date compression: 压缩数据
   3. Encryption: 加密数据
3. Session: 会话层 设置和管理服务器和客户端的链接，实现发送和接收数据 
   1. Authentication
   2. Authorization
   3. Session Management : Keep a track of  the files 
4. Transport: 传输层 Protocols: TCP( Transmission Control  Protocol)、UDP(User  Datagram  Protocol)
   1. Segmentation: 来自会话层的数据被分成了许多小的数据块，每个数据块包括source、destination的端口号和块号；其中，通过端口号，可将数据块发送到正确的应用方，块号可以将发送到同一应用方的数据进行排序，从而形成正确的消息。
   2. Flow control: 可以控制数据的传输速率，假设服务器的传输速率是100Mbps，客户端的处理速度是10Mbps，客户端的处理速度赶不上服务器的传输速度，此时，客户端可以通过传输层告诉服务器放缓传输速度为10Mbps即可，同样的，如果服务器的传输速率过慢，可以提高传输速率。
   3. Error control: 
5. Network: 网络层 解决路由和路径计算
   1. Data Units in the network layer are called packets 
   2. 含有源ip和目的ip
6. Data Link: 数据链锯层
7. Physical: 物理层

Web browser可以执行OSI七层中应用层、表示层、会话层的所有API函数