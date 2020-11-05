# G server
服务端测试项目

# Boost 依赖
Boost通过github下载，作为cmake的External project引入

# Protobuf 依赖
需要在本机安装，作为共享库引入
```sh
$ sudo apt-get install autoconf automake libtool curl make g++ unzip
$ wget https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/protobuf-cpp-3.6.1.zip
$ unzip protobuf-cpp-3.6.1.zip 
$ cd protobuf-3.6.1/
$ ./autogen.sh
$ ./configure
$ make && sudo make install
```