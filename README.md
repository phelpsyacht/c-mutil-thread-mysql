# c-gumbo-html-mysql
展示如何用c语言多线程连接mysql, 提供了处理网页信息的基本方法

1.请安装gumbo,详情见https://github.com/google/gumbo-parser
2.请安装curl c语言版本库
3.安装mysql开发工具
4.demo里包含了一个简单的sql表文件
5. compile:gcc -o p_w -g  curl_book_process.c split_string.c  curl_component.c sql_crud.c -lgumbo -lcurl  -lpthread -lmysqlclient
6. run:./p_w
           

