# Beyond the Common Core
[[HighPerformanceComputation]]

## 附加子句
`if`可以放在预编译中，对串行代码的影响尽可能小

## 共享循环构造
`lastprivate`：每个变量赋值为循环中最后一次（串行方法）迭代的值
	`firstprivate`和`lastprivate`并不冲突

## 任务构造
`#pragma omp taskyled`：显示放置任务调度点
`untitled`：显示的将任务标记为非绑定状态（默认任务和线程是绑定的，否则如果中间收到指令去做别的，原有任务有可能无法完成）
`priority(int)`：相对较弱，不需要精准调控
`depend(in,out,intout)`：设置依赖关系，确定

## `threadprivate`

## `master`
定义线程组主线程的工作块，等效于获取id+判断id为0
```c
int id = omp_get_thread_num()
if(id == 0){
	structure = block
}
```
一定要是主线程，比如单线程的程序，`id == 1`则无法顺利执行

## `atomic`
原子的构造确保了一个变量作为一个独立的，不被中断的，整体的被读取和写入
避免**数据竞争**，避免并发线程对一个变量多次更新的可能性
参考`critical`（保护下面一段），`atomic`只保护写入的变量，但效率更高

## `OMP_STACKSIZE`
环境变量

## 运行时库例程
+ `omp_get_num_threads`
+ `omp_set_dynamic`：优化模式
+ `omp_in_parallel`：判断是否在并行