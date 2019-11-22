#include "pipe.h"
#include "pipe_util.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define UNUSED_PARAMETER(var) (var) = (var)

#define array_eq(a1, a2)                   \
    (sizeof(a1) == sizeof(a2)              \
         ? memcmp(a1, a2, sizeof(a1) == 0) \
         : 0)

#define array_eq_len(a1, a2, len2)          \
    (sizeof(a1) == sizeof((a2)[0]) * (len2) \
         ? memcmp(a1, a2, sizeof(a1)) == 0  \
         : 0)

typedef struct
{
    int orig;
    int new;
} testdata_t;

void test_stage(const void *elems, size_t count, pipe_producer_t *out, void *aux)
{
    UNUSED_PARAMETER(aux);

    if (count == 0)
        return;

    testdata_t outbuffer[count];

    memcpy(outbuffer, elems, count * sizeof(testdata_t));

    for (size_t i = 0; i < count; ++i)
    {
        outbuffer[i].new *= 2;
        // printf("out=%d\n",outbuffer[i].new);
    }
    printf("out=%d\n",outbuffer[1].new);

    pipe_push(out, outbuffer, count);
}

static void double_elems(const void *elems, size_t count, pipe_producer_t *out, void *aux)
{
    UNUSED_PARAMETER(aux);

    if (count == 0)
        return;

    testdata_t outbuffer[count];

    memcpy(outbuffer, elems, count * sizeof(testdata_t));

    for (size_t i = 0; i < count; ++i)
    {
        outbuffer[i].new *= 2;
        // printf("out=%d\n",outbuffer[i].new);
    }
    printf("out=%d\n",outbuffer[1].new);

    pipe_push(out, outbuffer, count);
}

#ifdef PIPE_DEBUG
#define MAX_NUM 250000
#else
#define MAX_NUM 5
#endif

static void generate_test_data(pipe_producer_t *p)
{
    for (int i = 0; i < MAX_NUM; ++i)
    {
        testdata_t t = {i, i};
        pipe_push(p, &t, 1);
    }
}

static inline void validate_test_data(testdata_t t, int multiplier)
{
    assert(t.new == t.orig *multiplier);
}

static void validate_consumer(pipe_consumer_t *c, unsigned doublings)
{
    testdata_t t;

    while (pipe_pop(c, &t, 1))
        validate_test_data(t, 1 << doublings);
}

int main()
{
    //pipe_run_test_suite();

    pipe_t *pipe = pipe_new(sizeof(int), 0); //元素为int类型，大小4字节，不是buf的长度
    pipe_producer_t *p = pipe_producer_new(pipe);
    pipe_consumer_t *c = pipe_consumer_new(pipe);
    pipe_free(pipe);

    int a[] = {0, 1, 2, 3, 4};
    int b[] = {9, 8, 7, 6, 5};

    pipe_push(p, a, countof(a));
    pipe_push(p, b, countof(b));

    pipe_producer_free(p);

    int bufa[6];  //
    int bufb[10]; //

    size_t acnt = pipe_pop(c, bufa, countof(bufa)), //target为bufa
        bcnt = pipe_pop(c, bufb, countof(bufb));    //只会接收到4个数据

    printf("acnt=%d\n", acnt);
    printf("bcnt=%d\n", bcnt);

    int expecteda[] = {
        0, 1, 2, 3, 4, 9};

    int expectedb[] = {
        8, 7, 6, 5};

    assert(array_eq_len(expecteda, bufa, acnt));
    assert(array_eq_len(expectedb, bufb, bcnt));

    pipe_consumer_free(c);

    /********************pipeline************************/

    pipeline_t pipeline =
        pipe_pipeline(sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                      &double_elems, (void *)NULL, sizeof(testdata_t),
                    //   &double_elems, (void *)NULL, sizeof(testdata_t),
                    //   &double_elems, (void *)NULL, sizeof(testdata_t),
                      (void *)NULL);

    assert(pipeline.in);
    assert(pipeline.out);

    generate_test_data(pipeline.in); //参数为上面pipe_pipeline函数的返回值
    pipe_producer_free(pipeline.in);
    validate_consumer(pipeline.out, 6);//前面的处理节点数量
    validate_consumer(pipeline.out, 6);
    pipe_consumer_free(pipeline.out);

/********************pipe_parallel************************/

    pipeline_t pipeline_1 =
        pipe_parallel(4,
                      sizeof(testdata_t),
                      &test_stage, (void*)NULL,
                      sizeof(testdata_t));

    assert(pipeline_1.in);
    assert(pipeline_1.out);

    generate_test_data(pipeline_1.in); 
    pipe_producer_free(pipeline_1.in);
    validate_consumer(pipeline_1.out, 1); 
    pipe_consumer_free(pipeline_1.out);
    return 0;
}
