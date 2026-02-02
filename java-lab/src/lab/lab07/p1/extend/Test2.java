package lab.lab07.p1.extend; // 声明当前文件所属的包路径，方便类管理

/**
 * 【考试重点：多线程累加】
 * 题目要求：使用继承 Thread 类的方式，在 main 方法中创建两个线程，共同完成从 1 加到 100 的计算。
 * 分工：一个线程负责 1-50，另一个线程负责 51-100。
 * 预期结果：sum=5050。
 */
class Test2 {
    public static void main(String[] args) throws InterruptedException {
        // 1. 创建第一个线程实例，负责计算 1 到 50 的闭区间
        // 在构造方法中，我们已经设计了让它自动启动 (start)
        sum100 s1 = new sum100(1, 50);

        // 2. 创建第二个线程实例，负责计算 51 到 100 的闭区间
        sum100 s2 = new sum100(51, 100);

        // 【关键点：等待线程结束】
        // join() 方法的作用是：让“当前线程”（即 main 线程）进入阻塞状态，
        // 直到调用 join 的那个线程（s1 或 s2）执行完毕后，main 线程才继续往下跑。
        // 如果不加 join，main 线程可能会在 s1 和 s2 还没算完时就直接打印 total_sum，导致结果不准确。
        s1.join();
        s2.join();

        // 3. 输出最终所有的累加和。由于 total_sum 是静态变量，所有的实例共享这个结果。
        System.out.println("sum=" + sum100.total_sum);
    }
}

/**
 * 继承 Thread 类是 Java 中实现多线程的常用手段之一。
 * 注意：必须重写 run() 方法，线程启动后会自动执行 run() 里的逻辑。
 */
class sum100 extends Thread {
    // 成员变量：用于记录当前线程需要计算的起始值和结束值
    int init_start;
    int init_end;

    // 【静态变量：全局累加器】
    // 使用 static 关键字，意味着 total_sum 属于类本身，而不属于某个对象。
    // 所有 sum100 的实例对象都在往同一个变量里加分。
    static int total_sum = 0;

    /**
     * 构造方法：在创建对象时初始化范围，并直接启动线程。
     * 
     * @param sum_start 计算范围的起点
     * @param sum_end   计算范围的终点
     */
    sum100(int sum_start, int sum_end) {
        this.init_start = sum_start;
        this.init_end = sum_end;
        // 【注意】：在构造器中直接调用 start() 是为了方便题目要求。
        // start() 方法会向操作系统申请开启新线程，并由 JVM 调用本类的 run() 方法。
        this.start();
    }

    /**
     * 线程的执行体：run 方法内写的是线程具体要干的活。
     */
    @Override
    public void run() {
        int sum = 0; // 定义一个局部变量，存储当前这个线程自己算出来的部分和

        // 典型的 for 循环累加
        for (int i = init_start; i <= init_end; i++) {
            sum += i;
        }

        // 将局部算出的部分和，平摊、累加到全局的静态变量 total_sum 中。
        // （考试注意点：在严格多线程环境下，此处 += 是非原子的，可能存在同步问题，
        // 但针对目前简单的 lab 练习和 join() 的使用，结果通常是正确的。）
        total_sum += sum;
    }
}
