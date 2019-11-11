/* pipe_util.c - The implementation for experimental pipe extensions.
 *
 * The MIT License
 * Copyright (c) 2011 Clark Gaebel <cg.wowus.cg@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "pipe_util.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef _WIN32 // use the native win32 API on Windows

#include <windows.h>

#define thread_create(f, p) CloseHandle(            \
        CreateThread(NULL,                          \
                     0,                             \
                     (LPTHREAD_START_ROUTINE)(f),   \
                     (p),                           \
                     0,                             \
                     NULL))

#else // fall back on pthreads

#include <pthread.h>

static inline void thread_create(void *(*f) (void*), void* p)
{
    pthread_t t;
    pthread_create(&t, NULL, f, p);
}

#endif

//创建一个pipe_stage节点，包含一个生产者、消费者，并返回pipeline
pipeline_t pipe_trivial_pipeline(pipe_t* p)
{
    return (pipeline_t) {
        .in  = pipe_producer_new(p),
        .out = pipe_consumer_new(p)
    };
}

#define DEFAULT_BUFFER_SIZE     128

typedef struct {
    pipe_consumer_t* in;
    pipe_processor_t proc;
    void* aux;
    pipe_producer_t* out;
} connect_data_t;

/* 
 * 内部函数，pipe节点处理：连续pop数据，连续处理proc
 */
static void* process_pipe(void* param)
{
    connect_data_t p = *(connect_data_t*)param;
    free(param);
    //分配空间
    char* buf = malloc(DEFAULT_BUFFER_SIZE * pipe_elem_size(PIPE_GENERIC(p.in)));

    size_t elems_read;
    //从pipe输入读取数据
    while((elems_read = pipe_pop(p.in, buf, DEFAULT_BUFFER_SIZE)))//不断读，不断处理？，有数据则处理while(1),无数据则while(0)跳过
        p.proc(buf, elems_read, p.out, p.aux);

    p.proc(NULL, 0, NULL, p.aux);

    free(buf);

    pipe_consumer_free(p.in);
    pipe_producer_free(p.out);

    return NULL;
}

/* 
 *  连接节点、创建proc处理线程
 */
void pipe_connect(pipe_consumer_t* in,
                  pipe_processor_t proc, void* aux,
                  pipe_producer_t* out)
{
    assert(in);
    assert(out);
    assert(proc);

    connect_data_t* d = malloc(sizeof *d);

    *d = (connect_data_t) {//学习这种结构体赋值方式
        .in = in,
        .proc = proc,
        .aux = aux,
        .out = out
    };

    thread_create(&process_pipe, d);//创建proc处理线程，注意不是linux的线程函数
}


/* 
 *  创建并行处理节点
 */
pipeline_t pipe_parallel(size_t           instances,//
                         size_t           in_size,
                         pipe_processor_t proc,//多个节点运行同一个处理函数，并行处理
                         void*            aux,
                         size_t           out_size)
{
    pipe_t* in  = pipe_new(in_size,  0),//创建一个in
          * out = pipe_new(out_size, 0);//创建一个out

    while(instances--)//实体数量
        pipe_connect(pipe_consumer_new(in),//所有消费者或生产者都基于同一个pipe_t创建
                     proc, aux,//多个proc同时处理同一个in的数据？
                     pipe_producer_new(out));//连接instances个节点

    pipeline_t ret = {//pipeline节点
        .in  = pipe_producer_new(in),//new
        .out = pipe_consumer_new(out)
    };

    pipe_free(in);
    pipe_free(out);

    return ret;//
}

/* 
 *  返回 pipeline_t va_pipe_pipeline，递归调用，循环连续创建处理节点
 */
static pipeline_t va_pipe_pipeline(pipeline_t result_so_far,//in、out
                                   va_list args)
{
    pipe_processor_t proc = va_arg(args, pipe_processor_t);//这个宏检索函数参数列表中类型为 type 的下一个参数。

    if(proc == NULL)
        return result_so_far;

    void*  aux       = va_arg(args, void*); //获取参数，调用一次获取一个参数
    size_t pipe_size = va_arg(args, size_t);//获取参数，调用一次获取一个参数

    if(pipe_size == 0)//节点为空？
    {
        pipe_consumer_free(result_so_far.out);
        result_so_far.out = NULL;
        return result_so_far;
    }

    pipe_t* pipe = pipe_new(pipe_size, 0); //创建pipe

    pipe_connect(result_so_far.out , proc, aux, pipe_producer_new(pipe));//连接：生产者\处理函数\消费者
    result_so_far.out = pipe_consumer_new(pipe);//指向新的消费者?,类似链表？

    pipe_free(pipe);//用完就释放，pipe

    return va_pipe_pipeline(result_so_far, args);//返回函数本身，递归调用，连续创建节点
}


/* 
 * 用于最终创建流水线pipeline过程，所有过程都列在这里 
 * 
 */
pipeline_t pipe_pipeline(size_t first_size, ...)
{
    va_list va;
    va_start(va, first_size);//这个宏初始化 ap 变量，它与 va_arg 和 va_end 宏是一起使用的。last_arg 是最后一个传递给函数的已知的固定参数，即省略号之前的参数。

    pipe_t* p = pipe_new(first_size, 0);//创建一个pipe,包含元素的尺寸为first_size，元素数量无上限

    pipeline_t ret = va_pipe_pipeline(pipe_trivial_pipeline(p), va);

    pipe_free(p);

    va_end(va); // 这个宏允许使用了 va_start 宏的带有可变参数的函数返回。如果在从函数返回之前没有调用 va_end，则结果为未定义。

    return ret;
}


/* vim: set et ts=4 sw=4 softtabstop=4 textwidth=80: */
