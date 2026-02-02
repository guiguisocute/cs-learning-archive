package lab.lab07.p1.inner; // 声明包名，对应 src 目录结构

/**
 * 【考试重点：使用 Runnable 接口实现多线程】
 * 题目要求：用“内嵌线程”的方式实现 1-100 的累加。
 * 所谓内嵌，通常指的是类实现了 Runnable 接口，并内部持有一个 Thread 对象。
 */
class Test1 {
    /**
     * 程序主入口
     * 
     * @param args 命令行参数
     * @throws InterruptedException 因为调用了 join()，可能抛出中断异常
     */
    public static void main(String[] args) throws InterruptedException {
        // 1. 创建任务实例 s1，负责前半部分 1-50
        sum100 s1 = new sum100(1, 50);

        // 2. 创建任务实例 s2，负责后半部分 51-100
        sum100 s2 = new sum100(51, 100);

        // 【关键点】由于我们将 Thread 对象“组合”在了 sum100 类中，
        // 此时我们需要访问 s1 内部的那个 thread 对象来调用 join()。
        // join() 确保 main 线程等待 s1 和 s2 任务执行完毕。
        s1.thread.join();
        s2.thread.join();

        // 3. 打印最终汇总在静态变量 total_sum 中的结果
        System.out.println("sum=" + sum100.total_sum);
    }
}

/**
 * 实现 Runnable 接口是 Java 推荐的多线程实现方式。
 * 优势：解耦了“任务逻辑” (Runnable) 和“执行机制” (Thread)。
 */
class sum100 implements Runnable {
    int init_start; // 计算区间的开始值
    int init_end; // 计算区间的结束值

    // 静态变量：类级别共享的累加器
    static int total_sum = 0;

    // 内部持有的 Thread 引用，用于控制线程启动和等待
    Thread thread;

    /**
     * 构造器：初始化任务范围，并绑定 Thread 对象后启动
     */
    sum100(int sum_start, int sum_end) {
        this.init_start = sum_start;
        this.init_end = sum_end;

        // 创建 Thread 对象，并将当前实例 (this) 作为任务目标传递进去
        this.thread = new Thread(this);

        // 启动线程，JVM 会随后调用下面的 run 方法
        this.thread.start();
    }

    /**
     * 线程任务的具体实现
     */
    @Override
    public void run() {
        int sum = 0; // 局部累加器，保存当前线程负责部分的和

        // 遍历指定区间进行累加
        for (int i = init_start; i <= init_end; i++) {
            sum += i;
        }

        // 将局部和合并到静态变量 total_sum 中
        total_sum += sum;
    }
}
