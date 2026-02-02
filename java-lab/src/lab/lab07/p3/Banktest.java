package lab.lab07.p3; // 声明包名

/**
 * 【考试重点：经典银行存钱同步问题】
 * 题目要求：两个顾客并行操作同一个银行账户，每人分 3 次存入 100 元。
 * 重点：必须保证余额计算的准确性。如果存钱动作不加锁，可能会导致两个线程同时读取旧余额，造成“钱算少了”的情况。
 */
public class Banktest {
    public static void main(String[] args) {
        // 1. 创建银行对象，初始余额为 1000.0
        Bank bank = new Bank(1000.0);

        // 2. 启动第一个线程 (aa) 进行存钱任务
        // 注意：deposit 方法内会自行启动一个新的计算线程
        bank.deposit("aa", 100.0, 3);

        // 3. 启动第二个线程 (bb) 进行存钱任务
        // 它们将并发地操作同一个 bank 对象
        bank.deposit("bb", 100.0, 3);
    }
}

/**
 * 银行类：作为共享资源，包含余额和操作逻辑
 */
class Bank {
    double balance; // 银行总余额
    Thread thread; // 线程引用

    // 构造器：设置初始钱数
    Bank(double init_balance) {
        balance = init_balance;
    }

    /**
     * 存钱动作
     * 
     * @param name_in  顾客姓名
     * @param money_in 单次存入金额
     * @param times_in 存入总次数
     */
    void deposit(String name_in, double money_in, int times_in) {
        // 【Java 8 Lambda 写法】：new Thread(() -> { ... })
        // 这里的 Lambda 表达式充当了 Runnable 接口的 run 方法实现
        thread = new Thread(() -> {
            for (int i = 1; i <= times_in; i++) {
                /**
                 * 【同步对象锁：synchronized(this)】
                 * this 代表当前的 Bank 对象。
                 * 两个线程（aa和bb）调用的是同一个 bank 对象的 deposit，因此 this 是同一个。
                 * 这个块确保了“读取余额、显示、加钱、显示结果”这四步是连贯的原子操作，
                 * 不会被另一个线程在中途打断。
                 */
                synchronized (this) {
                    System.out.println("银行当前余额为" + balance + "," + name_in + "第" + i + "次存入" + money_in + "元");
                    balance += money_in; // 临界区操作：修改共享余额
                    System.out.println("当前银行总额为:" + balance);
                }

                try {
                    // 故意休眠 1000 毫秒，让出 CPU 执行权，让两个线程交替存钱的现象更明显
                    // 注意：休眠放在同步块之外，这样 aa 睡着时，bb 才能拿到锁进来存钱。
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        // 正式开启子线程
        thread.start();
    }
}
