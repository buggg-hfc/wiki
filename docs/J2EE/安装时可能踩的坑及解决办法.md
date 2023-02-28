# 安装时可能踩的坑及解决办法

**注意：养成好习惯，安装目录里不要有中文！**

## 运行 $\text{startup.bat}$ 时闪退

1. 首先请参照文档检查环境变量是否正确配置，提供一个检查单：

    - [ ] `JAVA_HOME` 是否正确配置，注意该变量值末尾没有 `\`
    - [ ] `CLASSPATH` 是否为 `.;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\htmlconverter.jar`
    - [ ] `Path` 中是否配置了 `%JAVA_HOME%\bin`
    - [ ] `CATALINA_HOME` 是否正确配置，注意该变量值末尾没有 `\`
    - [ ] `Path` 中是否配置了 `%CATALINA_HOME%\bin`

2. 若环境变量正确配置且 $\text{Tomcat}$ 版本为 $\text{10}$，则需在环境变量中添加一个 `JRE_HOME`，内容与 `JAVA_HOME` 一样
3. 若环境变量正确配置后仍闪退，请重启电脑

## 运行 $\text{startup.bat}$ 时因端口号被占用报错

提供两种方法：

1. 杀掉占用端口号的进程：打开终端/命令提示符，输入 `netstat -ano|findstr 8080`，记下最后一列的数字；输入 `taskkill /T /F /PID 参数`，其中 `参数` 替换为刚刚记下的数字
2. 修改默认使用的端口号：打开 $\text{Tomcat}$ 目录下的 $\text{conf}$ 文件夹中的 $\text{server.xml}$ 文件，即 `apache-tomcat-x.x.x\conf\server.xml`，大约在其 $\text{70}$ 行左右，有个 `port="8080"`，将 `8080` 改成未被占用的端口号，例如 `8088`、`8011` 等等

## 运行 $\text{startup.bat}$ 时出现乱码

1. 打开 $\text{Tomcat}$ 目录下的 $\text{conf}$ 文件夹中的 $\text{logging.properties}$ 文件，即 `apache-tomcat-x.x.x\conf\logging.properties`，大约在其 $\text{47-50}$ 行，将 `java.util.logging.ConsoleHandler.encoding = UTF-8` 修改为 `java.util.logging.ConsoleHandler.encoding = GBK`