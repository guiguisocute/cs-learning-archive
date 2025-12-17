package lab.lab07.p4;

/*
TODO:类 BufferArea 用于产生一个[1..100]的随机整数，并可取出此数。存数线程类 ThreadPutNumber 将数存入缓冲区（BufferArea）。
 读数线程类ThreadGetNumber 从缓冲区读取数并判断是否是素数。要求 main 线程最后结束。
 */
/*
输出：
put number is 48
48 is not a prime!
put number is 34
34 is not a prime!
put number is 83
83 is a prime!
put number is 84
84 is not a prime!
put number is 42
42 is not a prime!
put number is 20
20 is not a prime!
put number is 95
95 is not a prime!
main is over!
 */

import java.util.Random;

public class App {
    public static void main(String[] args) throws InterruptedException {
        BufferArea bufferArea = new BufferArea();
        ThreadPutNumber threadPutNumber = new ThreadPutNumber(bufferArea);
        ThreadGetNumber threadGetNumber = new ThreadGetNumber(bufferArea);
        threadPutNumber.start();
        threadGetNumber.start();

        threadPutNumber.join();
        threadGetNumber.join();

        System.out.println("main is over!");
    }

}

class BufferArea {
    boolean isEmpty = true;
    int value;

    synchronized void put(int value_in) {
        while (!isEmpty) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        value = value_in;
        System.out.println("put number is " + value_in);
        isEmpty = false;
        notifyAll();
    }

    synchronized int get() {
        while (isEmpty) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        isEmpty = true;
        return value;
    }

    synchronized void release() {
        notifyAll();
    }

}

class ThreadPutNumber extends Thread {
    BufferArea bufferArea;
    Random random;

    public ThreadPutNumber(BufferArea bufferArea_in) {
        bufferArea = bufferArea_in;
        random = new Random();
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            int value = random.nextInt(100) + 1;
            bufferArea.put(value);
        }
    }

}

class ThreadGetNumber extends Thread {
    BufferArea bufferArea;

    public ThreadGetNumber(BufferArea bufferArea_in) {
        bufferArea = bufferArea_in;
    }

    public static boolean isPrime(int value_in) {
        for (int i = 2; i < value_in; i++) {
            if (value_in % i == 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            int val = bufferArea.get();
            if (isPrime(val)) {
                System.out.println(val + " is a prime!");
            } else {
                System.out.println(val + " is not a prime!");
            }
            bufferArea.release();
        }
    }

}
