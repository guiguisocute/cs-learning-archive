package xuexitong_test.week_14.p1;

/*
TODO:线程类 T 实现依次输出 data 的 1~10 倍数据， 必须同时满足如下要求：

（1）main 中构造三个线程 t2、t3、t5，分别输出 2、3、5 的倍数；
（2）t2、t3、t5三个线程结果交叉输出；
（3）只有当 t2、t3、t5 执行完成后，才能输出“程序结束”。
（4）已给出的代码部分不得改动，否则算错。

注意提交时，需要提交整个程序！且程序有唯一输出结果：

线程开始：

3 5 2 6 10 4 9 15 6 12 20 8 15 25 10 18 30 12 21 35 14 24 40 16 27 45 18 30 50 20 程序结束。

//注：冒号是中文输入，每个数值后有一个空格

 */
class Test {

    public static void main(String[] args) throws Exception {

        System.out.print("线程开始：\n");
        shareResource sr = new shareResource();

        T t2 = new T(sr, "t2", 2, 0, 1); // now = 0，next = 1，意思是synchronized的锁是0，跑完变成1，后面线程定义同理
        T t3 = new T(sr, "t3", 3, 1, 2);
        T t5 = new T(sr, "t5", 5, 2, 0);

        /* 补充代码④ */
        t2.thread.start();
        t3.thread.start();
        t5.thread.start();

        t2.thread.join();
        t3.thread.join();
        t5.thread.join();

        System.out.print("程序结束。");
    }
}

class shareResource {

    // 补充代码②
    int flag = 1; // 初始让3线程跑，所以flag要初始化1

}

class T implements Runnable {// 采用内嵌线程的方式

    private shareResource sr;
    private int now, next, data;
    Thread thread;
    String name;

    /* 补充代码③，可能包含属性、方法、构造函数 */
    public T(shareResource sr_in, String name_in, int data_in, int now_in, int next_in) {
        sr = sr_in;
        name = name_in;
        data = data_in;
        now = now_in;
        next = next_in;
        thread = new Thread(this);
    }

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            synchronized (sr) {

                while (sr.flag != now) {
                    try {
                        sr.wait();// 只要没有获取到锁类中的值，就一直处于wait状态，等待其它线程去获取锁并且把锁中的属性变更为自己等到的应该等到的值
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                System.out.print(data * i + " ");
                sr.flag = next;
                sr.notifyAll();
            }
        }
    }

}
