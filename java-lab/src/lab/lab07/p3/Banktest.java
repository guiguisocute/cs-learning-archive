package lab.lab07.p3;
/*
TODO:假设某个银行，它可以授受顾客的汇款，每做一次汇款，便可计算出汇款的总额。现有两个顾客对同一个银行帐号操作，一个顾客分 3 次，每次将 100 元钱存入，要求存入后将钱的总额输出。
 */

/*
输出：
银行当前余额为1000.0,aa第1次存入100.0元
当前银行总额为:1100.0
银行当前余额为1100.0,bb第1次存入100.0元
当前银行总额为:1200.0
银行当前余额为1200.0,aa第2次存入100.0元
当前银行总额为:1300.0
银行当前余额为1300.0,bb第2次存入100.0元
当前银行总额为:1400.0
银行当前余额为1400.0,aa第3次存入100.0元
当前银行总额为:1500.0
银行当前余额为1500.0,bb第3次存入100.0元
当前银行总额为:1600.0
 */
public class Banktest {
    public static void main(String[] args) {
        Bank bank = new Bank(1000.0);
        bank.deposit("aa",100.0,3);
        bank.deposit("bb",100.0,3);
    }


}

class Bank{
    double balance;
    Thread thread;

    Bank(double init_balance){
        balance = init_balance;
    }

    // synchronized void deposit(String name, double money, int times){            // 一种同步的封装，用synchronized修饰的方法就是同步方法，它表示整个方法的锁都是this（不过要是修饰的是static呢，回去研究一下），【本来是想整个方法加锁的，后来发现这并不能让两个程序并行，还是注释掉吧、、、】

    // }
    void deposit(String name_in, double money_in, int times_in){
        thread = new Thread(() -> {
            for(int i=1; i<=times_in; i++){
                synchronized(this){
                    System.out.println("银行当前余额为" + balance + "," + name_in + "第" + i + "次存入" + money_in + "元");
                    balance += money_in;
                    System.out.println("当前银行总额为:" + balance);
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        thread.start();
    }


}


