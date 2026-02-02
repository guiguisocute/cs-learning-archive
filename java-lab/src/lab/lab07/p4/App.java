package lab.lab07.p4; // 声明包名，对应 src 目录结构

import java.util.Random;

/**
 * 【实验 7 任务 4：生产者-消费者模型】
 * 题目要求：
 * 1. BufferArea 类作为缓冲区，产生并存放 [1..100] 的随机整数。
 * 2. ThreadPutNumber 线程负责存数。
 * 3. ThreadGetNumber 线程负责取数并判断是否为素数。
 * 4. 要求 main 线程在所有子线程结束后再结束。
 */

/**
 * 【考试重难点：生产者-消费者模型 (wait/notify)】
 * 题目要求：一个线程存数，一个线程取数并判断素数，缓冲区大小为 1。
 * 重点：main 线程必须最后结束。
 */
public class App {
    public static void main(String[] args) throws InterruptedException {
        // 1. 创建共享缓冲区
        BufferArea bufferArea = new BufferArea();

        // 2. 创建生产者线程（存数）
        ThreadPutNumber threadPutNumber = new ThreadPutNumber(bufferArea);

        // 3. 创建消费者线程（取数并判断素数）
        ThreadGetNumber threadGetNumber = new ThreadGetNumber(bufferArea);

        // 4. 启动线程
        threadPutNumber.start();
        threadGetNumber.start();

        // 【关键点：main 线程最后结束】
        // 调用 join()，让 main 线程等待这两个子线程干完活再继续
        threadPutNumber.join();
        threadGetNumber.join();

        System.out.println("main is over!");
    }
}

/**
 * 缓冲区类：协调生产者和消费者的中转站
 */
class BufferArea {
    // 标志位：isEmpty 为 true 表示缓冲区没数，可以存；为 false 表示有数，可以取
    boolean isEmpty = true;
    int value; // 存放内容的变量

    /**
     * 同步方法：存数
     * synchronized 确保同一时间只有一个线程操作缓冲区
     */
    synchronized void put(int value_in) {
        // 如果缓冲区里已经有数了（不为空），存数线程就得等着
        while (!isEmpty) {
            try {
                // wait() 使当前线程进入等待池，并释放锁
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // 走到这说明缓冲区空了，可以存数
        value = value_in;
        System.out.println("put number is " + value_in);

        // 修改状态：现在有数了
        isEmpty = false;

        // 【核心】叫醒所有正在等待的线程（尤其是取数线程）
        notifyAll();
    }

    /**
     * 同步方法：取数
     */
    synchronized int get() {
        // 如果缓冲区是空的，取数线程就得等着
        while (isEmpty) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // 走到这说明有数了，取走它
        isEmpty = true; // 取走后，状态变回空
        return value;
    }

    /**
     * 辅助同步方法：释放所有等待中的线程
     */
    synchronized void release() {
        notifyAll();
    }
}

/**
 * 生产者：负责制造随机数并存入缓冲区
 */
class ThreadPutNumber extends Thread {
    BufferArea bufferArea;
    Random random;

    public ThreadPutNumber(BufferArea bufferArea_in) {
        bufferArea = bufferArea_in;
        random = new Random();
    }

    @Override
    public void run() {
        // 模拟存 10 次数
        for (int i = 0; i < 10; i++) {
            int value = random.nextInt(100) + 1; // 产生 [1, 100] 的随机数
            bufferArea.put(value);
        }
    }
}

/**
 * 消费者：从缓冲区拿数并进行素数判定
 */
class ThreadGetNumber extends Thread {
    BufferArea bufferArea;

    public ThreadGetNumber(BufferArea bufferArea_in) {
        bufferArea = bufferArea_in;
    }

    /**
     * 静态工具方法：素数判断逻辑
     */
    public static boolean isPrime(int value_in) {
        if (value_in < 2)
            return false;
        for (int i = 2; i <= Math.sqrt(value_in); i++) {
            if (value_in % i == 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void run() {
        // 对应生产者的 10 次，取 10 次数
        for (int i = 0; i < 10; i++) {
            int val = bufferArea.get(); // 阻塞式获取

            // 判定并打印
            if (isPrime(val)) {
                System.out.println(val + " is a prime!");
            } else {
                System.out.println(val + " is not a prime!");
            }

            // 完成一次消费后，手动叫醒另一边的生产者
            bufferArea.release();
        }
    }
}
