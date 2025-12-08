package lab.lab07.p1.extend;

/*
TODO:用继承Thread类的方式实现累加和的计算，要求在main中用两个线程共同完成1+2+…+100的计算。一个线程计算1+2+…+50，另一个线程计算+51+52+…+100。
（注意：最后只输出一个结果：sum=5050)
*/
class Test2 {
    public static void main(String[] args) throws InterruptedException {
        sum100 s1 = new sum100(1, 50);
        sum100 s2 = new sum100(51, 100);
        s1.join();
        s2.join();
        System.out.println("sum=" + sum100.total_sum);
    }

}

class sum100 extends Thread {
    int init_start;
    int init_end;
    static int total_sum = 0;

    sum100(int sum_start, int sum_end) {
        this.init_start = sum_start;
        this.init_end = sum_end;
        this.start();
    }

    @Override
    public void run() {
        int sum = 0;
        for (int i = init_start; i <= init_end; i++) {
            sum += i;
        }
        total_sum += sum;
    }

}
