#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gumbo.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <pthread.h>

#include "curl_component.h"
#include "sql_crud.h"

#define  THREAD_NUM 3
 
pthread_mutex_t pmt;
pthread_t pt[THREAD_NUM];
int book_lists(char *, char *, MYSQL *);
void *thread_book();
void *thread_catalog();
void *thread_charpter();
void *thread_book();
void thread_wait();
void thread_create();

int main(void){
    /*command:gcc -o p_w -g  curl_book_process.c split_string.c  curl_component.c sql_crud.c -lgumbo -lcurl  -lpthread -lmysqlclient*/ 
    mysql_library_init(0,NULL,NULL);
    
    printf("main process:\n");

    printf("main thread will create subthread:\n");
    thread_create();
    thread_wait();  

    mysql_library_end(); 

    printf("return====>ok\n");

    return 0;
}

int book_lists(char *cn, char * fn, MYSQL *conn_prt){
    GumboOutput *output;
    char *buf;
    
    char url[108] = "http://www.www.com/index.php?page=";
    strcat(url ,cn);
    printf("link is %s\n", url);  
 
    buf=file_pt(url, fn);
    if (!buf) return -1;
    output=gumbo_parse(buf);
    if (!output){
        free(buf);
        return -1;
    }
    get_content(output->root, conn_prt);
    gumbo_destroy_output(&kGumboDefaultOptions,output);
    free(buf);

    return 0;
}

void *thread_book(){
    mysql_thread_init();
    MYSQL *conn_prt_book=mysql_init(NULL);
    if(!mysql_real_connect(conn_prt_book,"localhost","root",
        "book","book",0,NULL,0))
    {
        printf("failed to connect:%s\n",mysql_error(conn_prt_book));
        exit(0) ;
    }
    printf("connect success!\n");
    char cn[10];
    printf("thread_%ld:start\n", pthread_self());
    int n = 1;
    while(n < 1000){
        sprintf(cn, "%d", n);
        int book_pn = book_lists(cn, "index.html", conn_prt_book);
        if (book_pn == 0){
            printf("curl book executed successfully\n");
        }

        n++;
    }

    mysql_close(conn_prt_book);
    mysql_thread_end();

    pthread_exit((void *)0);
}

void *thread_catalog(){    
    /*slimilar to thread_book*/
}

void *thread_charpter(){
    /*slimilar to thread_book*/
}

void thread_create(){     
        /*book name lists*/
            int book_pc = pthread_create(&pt[0], NULL, thread_book, NULL);
        
            if (book_pc == 0){
                printf("thread_book created successfully\n");
            }else{
                printf("thread_book created failed\n");
            }
            

            /*catalog name lists*/
            int catalog_pc = pthread_create(&pt[1], NULL, thread_catalog, NULL);
            if (catalog_pc == 0){
                printf("thread_catalog created successfully\n");
            }else{
                printf("thread_catalog created successfully\n");
            }
            

           /*charpter content*/
            int charpter_pc = pthread_create(&pt[2], NULL, thread_charpter, NULL);
            if (charpter_pc == 0){
                printf("thread_charpter created successfully\n");
            }else{
                printf("thread_charpter created successfully\n");
            }
}

void thread_wait(){
    for (int n = 0; n < THREAD_NUM; n++){
        int pj = pthread_join(pt[n], NULL);
        if (pj !=0){
            printf("thread===>%d joined failed\n", n);
        }else{
            printf("thread===>%d joined successfully\n", n);
        }
    }
}







 

