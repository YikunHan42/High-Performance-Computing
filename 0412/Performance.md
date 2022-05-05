# Performance
![[性能.pdf]]
[[HighPerformanceComputation]]
>加速比=串行所消耗时间/并行所消耗时间
在理想情况下，加速比等于处理器的数量
效率=加速比/处理器数量

>并行计算的最终目的是减少处理问题的时间
骗术：选择一个慢的算法，穿行比例非常低，加速比很好，但是效率依然很差

>阿姆达尔定律
$\alpha$设为代码中的串行比例，最大的加速比为
$$Speedup=T_s/T_p$$

>并行开销
>阿姆达尔定律限制了并行的收益
>并行开销包括：创建线程....

>强扩展与弱扩展
>强扩展：固定规模
>弱扩展：非固定规模，处理器增加，整个问题的大小也在增加

>负载均衡
>线程的木桶原理，短板效应

```c
//串行
#include<stdio.h>

#include<omp.h>

static long num_steps = 100000000;

double step;

int main()

{

 int i;

 double x, pi, sum = 0.0;

 double start_time, run_time;

  

 step = 1.0 / (double) num_steps;

  

 start_time = omp_get_wtime();

  

 for(i = 0; i < num_steps; i++){

 x = (i + 0.5) * step;

 sum += 4.0/(1.0 + x * x);

 }

  

 pi = step * sum;

 run_time = omp_get_wtime() - start_time;

 printf("pi = %1f, \%1d steps \%1f, %1f secs\n ",

 pi, num_steps, run_time);

}

```

```c
//并行按周期分割
#include <stdio.h>

#include <omp.h>

  

#define NTHREADS 4

  

static long num_steps = 100000000;

double step;

int main()

{

 int i , j, actual_nthreads;

 double pi, start_time, run_time;

 double sum[NTHREADS] = {0.0};

  

 step = 1.0 / (double) num_steps;

  

 omp_set_num_threads(NTHREADS);

  

 start_time = omp_get_wtime();

 #pragma omp parallel

 {

 int i;

 int id = omp_get_thread_num();

 int numthreads = omp_get_num_threads();

 double x;

  

 if(id == 0) actual_nthreads = numthreads;

  

 for(i = id; i<num_steps ; i+= numthreads){

 x = (i + 0.5) * step;

 sum[id] += 4.0 / (1.0 + x * x);

 }

 }//end of parallel region

 pi = 0.0;

 for(i = 0; i< actual_nthreads; i++)

 pi += sum[i];

  

 pi = step * pi;

 run_time = omp_get_wtime() - start_time;

 printf("\n pi is \%f in \%f seconds \%d thrds \n",

 pi, run_time, actual_nthreads);

}
```
```c
//并行按块分割
#include <stdio.h>

#include <omp.h>

  

#define NTHREADS 4

  

static long num_steps = 100000000;

double step;

int main()

{

 int i , j, actual_nthreads;

 double pi, start_time, run_time;

 double sum[NTHREADS] = {0.0};

  

 step = 1.0 / (double) num_steps;

  

 omp_set_num_threads(NTHREADS);

  

 start_time = omp_get_wtime();

 #pragma omp parallel

 {

 int i;

 int id = omp_get_thread_num();

 int numthreads = omp_get_num_threads();

 double x;

  

 if(id == 0) actual_nthreads = numthreads;

  

 int istart = id * num_steps / numthreads;

 int iend = (id + 1) * num_steps / numthreads;

 if(id == (numthreads - 1)) iend = num_steps;

  

 for(i = istart; i < iend; i++){

 x = (i + 0.5) * step;

 sum[id] += 4.0 / (1.0 + x * x);

 }

 }//end of parallel region

 pi = 0.0;

 for(i = 0; i< actual_nthreads; i++){

 pi += sum[i];

  

 pi = step * pi;

 run_time = omp_get_wtime() - start_time;

 printf("\n pi is \%f in \%f seconds \%d thrds \n",

 pi, run_time, actual_nthreads);

}
```
同步：临界区 
`#pragma omp critical`进行排队
`pragma omp barrier`显式栅栏