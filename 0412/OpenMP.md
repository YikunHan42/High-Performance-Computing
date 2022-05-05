# OpenMP
![[什么是OpenMP.pdf]]
![[OpenMP通用核心.pdf]]
![[第七周 循环并行化.pdf]]
![[第七周 OpenMP通用核心总结.pdf]]
![[第七周 OMP环境.pdf]]
![[第七周 NUMACTL.pdf]]

## 参考文献
[OpenMP中的规约](https://blog.csdn.net/SHU15121856/article/details/79350474)

[[HighPerformanceComputation]]
并行：线程级、进程级、指令级
什么是OpenMp
指导原址：标准化现有的实践，支持可移植的、高效的、可理解的共享内存并行程序，为Fortran、C、C++提供统一的API，创建一个小型的API、其规模足以表达重要的控制并行模式，保证严格的向后兼容性，支持编写串行等效的代码
## 结构
构造
区域
基本元素
+ 编译器指令
+ 运行时库例程序
+ 环境变量

线程和fork-join模式
## 编程规则

## 常用库函数
```C
void omp_set_num_threads(int num_threads); //设置线程数
int omp_get_num_threads; //返回当前的线程数
int omp_get_num_procs; //返回当前线程的id，编号从零开始
int omp_get_thread_num(); //返回当前线程的id，编号从零开始
double omp_get_wtime(); //返回当前的墙钟时间
```

## 控制线程数量
### 代码
1. 代码中显式调用函数控制
`omp_set_num_threads(64);`
2. 更改环境变量
`export OMP_NUM_THREADS=64`
3. 运行程序的时候设置
`OMP_NUM_THREADS=64./a.out`

### Tips
1. 优先级：环境变量<运行时环境变量<程序内控制
2. 数量：一般不超过逻辑处理器的数量；针对计算密集型的程序，一般不超过物理处理器的数量
3. 线程设置的一些观点
+  设置线程环境变量的副作用是改变了环境的最大线程数，不太合理
+  运行时设置线程或者代码中设置线程数量更为合理
+  代码中设置线程数量更为灵活

## 关键字(C\C++)
`#pragma omp parallel //并行构造` 最后有一个隐式栅栏
`#pragma omp critical //临界区域`
`#pragma omp barrier //显式栅栏`
`#reduction(+:sum) //规约`

## numactl -physcpubind =(-C)
## numactl -hradware( -H)

## 环境
`OMP_PROC_BIND=true //绑核`

## 共享工作构造
### 规约
```C
int i;
double ave = 0.0, A[N];

InitA(A,N);

#pragma omp prarallel for reduction (+:ave) //规约运算符加号 变量为ave
	for (i = 0; i < N; i++){
	ave += A[i];
	}
ave = ave/N;
```
+  规约的操作可以是：+、-、* 、min、max、逻辑运算符、位运算符号
+  对于列表中的每个变量（规约变量），系统将为每个线程创建一个同名的私有变量
+  初始化...
+  构造体内部代码正常执行...
+  所有线程都在构造体末的栅栏处等待
+  规约变量副本合并

例：ave分给0-39，40-79，80-119ave分别计算，最后在隐式栅栏前等待相加

+  规约操作唯一，规约变量可以是多个
+  如何合并部分和的结果具体实现没有做规范设定义
+  **浮点运算不是严格上的结合性运算**（**对数学算法的逼近**），精度有限，这意味着归约的结果可能会因程序的不同运行而不同
+  但并非是OpenMP的错
+  多数时候影响并不大，而且基本是算法和数据不稳定

### 循环调度
+  循环调度包括静态调度和动态调度（事前和事中确定）
+  静态调度：编译器再“编译”时将循环迭代映射到线程上的调度方式
	+  当没有提供分块大小时，编译器会循环迭代分解成与线程总数相等数量的分块，并为每一个线程分配一个分块
	+  最佳分块大小可能很复杂，需要多试几次
	+  `#pragma omp for schedule(static)`
	+  适用于循环迭代的运行时间大致相同的情形（任务之间的复杂度、计算时间相近）
	+  适用于循环迭代具有可预测的运行时间
	+  不适用于工作量很大的情形
	+  不适用于系统中处理器以不同速度运行的情形
+  动态调度
	+  每个分块循环迭代次数由于句子中的chunk参数值给出
	+  每个线程被分配给其初始分块
	+  完成工作后抓取下一个分块
	+  持续到被计算完
	+  分块分配是运行时进行的，即可变性来源
判断质数：任务不固定，且非线性
```C
#pragma omp for reduction(+:sum) schedule(static)
	for(i = 2; i...)
	......
```

调度选择
+  静态调度：运行时工作量少
+  动态调度：逻辑更复杂，开销更大

质数：考题，存出来求出来

### 隐式栅栏
+ 共享工作构造结束时有一个隐式栅栏
+ 成本较高
+ 需要时可以使用不需要跳过
+ 跳过方法：
+ `#pragma omp for nowait` C
	+ `#!Somp do`
	+ `Somp end do no wait` Fortran
+ 并行结束时无法关闭栅栏

nowait(及openmp)：容易出现能够编译但功能错误的问题