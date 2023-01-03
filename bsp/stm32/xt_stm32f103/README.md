
### 简介

1、本工程基于 o2ospring 的《makefile_demo/5_rt-thread》开源项目搭建！  
2、本工程使用 rt-thread v4.1.0 工程，其版本信息为：

```bash
commit 201bd8871dff1efd1f48bdfd01a1938e4547ffd5 (HEAD -> master, tag: v4.1.0)
Author: guo <guozhanxin@rt-thread.com>
Date:   Wed Mar 30 16:59:20 2022 +0800

    Revert "优化build输出" (#5747)
```

**特别补充**：2023-01-03 前则是使用 rt-thread v4.1.1 及 v5.0.0 新版本工程，但好像新版本的 rt_thread_yield() 线程让出机制有问题，导致《xt_wiznet》网络模块工作不正常！

