package xuexitong_test.week_13.p1;

/*
TODO:用内嵌线程的方式实现累加和的计算，要求在main中用两个线程共同完成1+2+…+100的计算。一个线程计算1+2+…+50，另一个线程计算+51+52+…+100。
（注意：最后只输出一个结果：sum=5050)
*/

class T {
    public static void main(String[] args){
        sum100 s1=new sum100(1,50);
        sum100 s2=new sum100(51,100);
    }

//补充完整

}

class sum100 implements Runnable{
    int init_start;
    int init_end;
    static int total_sum = 0;
    static int total_count = 0;
    static final Object lock = new Object();
    Thread thread;


    @Override
    public void run() {
        int sum=0;
        for (int i = init_start; i <= init_end; i++) {
            sum+=i;
        }
        synchronized (lock){
            total_sum+=sum;
            total_count++;
            if (total_count == 2){
                System.out.println("sum="+ total_sum);
            }
        }
    }
    sum100(int sum_start,int sum_end){
        this.init_start=sum_start;
        this.init_end=sum_end;
        this.thread = new Thread(this);
        this.thread.start();
    }

}
