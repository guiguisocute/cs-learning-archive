package lab.lab07.p2; // 声明包名

/**
 * 【考试重点：线程同步 synchronized】
 * 题目要求：模拟多人竞争打电话的过程。
 * 重点：必须确保每个人说话时是连续的，不能被别人插嘴。这就需要用到互斥锁机制。
 */
class App {
    public static void main(String[] args) {
        // 1. 创建共享资源对象：电话亭
        // 多个线程（张三、李四、王五）将争夺对这同一个 d 对象的所有权
        DianHuaTing d = new DianHuaTing();

        // 2. 准备每个人的台词数据
        String[] s1 = { "1", "2", "3" };
        String[] s2 = { "A", "B", "C", "D", "E" };
        String[] s3 = { "你好，", "我也好，", "大家都好！" };

        // 3. 创建线程对象，将同一个电话亭对象 d 传给他们
        Talkers t1 = new Talkers(d, "张三", s1);
        Talkers t2 = new Talkers(d, "李四", s2);
        Talkers t3 = new Talkers(d, "王五", s3);

        // 4. 启动线程
        // 此时三个线程进入就绪状态，开始竞争 CPU 时间片和同步锁
        t1.start();
        t2.start();
        t3.start();
    }
}

/**
 * 共享资源类
 */
class DianHuaTing {
    // 此类对象在多线程中作为“锁对象”使用
    private final String dht = "我是电话亭";
}

/**
 * 说话者类，继承 Thread
 */
class Talkers extends Thread {
    private DianHuaTing dianHuaTing; // 记录要抢占的电话亭
    private String name; // 说话者的名字
    private String[] sentence; // 说话者的内容

    // 构造方法：初始化属性
    Talkers(DianHuaTing d_in, String name_in, String[] sentence_in) {
        dianHuaTing = d_in;
        name = name_in;
        sentence = sentence_in;
    }

    @Override
    public void run() {
        /**
         * 【同步代码块：synchronized】
         * 这里锁定的是 dianHuaTing 这个对象。
         * 当一个线程（比如张三）进入这个块时，它就拿到了“锁头”。
         * 其他线程（如李四）即使 CPU 切换到了它，由于它拿不到同一个对象的锁，
         * 只能在 synchronized 入口处排队阻塞，从而保证了打印输出的完整性。
         */
        synchronized (dianHuaTing) {
            System.out.print(name + "说“");

            // 循环打印每一句话
            for (String word : sentence) {
                try {
                    // 故意休眠 500 毫秒，模拟说话的间隙。
                    // 有了 synchronized，即使在休眠期间，别的线程也进不来。
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.print(word);
            }
            System.out.println("”"); // 说完之后换行，此时才会释放锁
        }
    }
}
