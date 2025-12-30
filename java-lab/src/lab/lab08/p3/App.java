package lab.lab08.p3;

//TODO:将 Fibonacci 序列值写入一个整数类型文件并读取输出到屏幕上
import java.io.*;

public class App {
    public static void main(String[] args) {
        String fileName = "fibonacci.dat";
        int n = 10;

        // 1. 写入二进制文件
        writeFibonacciBinary(fileName, n);

        // 2. 读取二进制文件
        readFibonacciBinary(fileName, n);
    }

    public static void writeFibonacciBinary(String file_inName, int n) {
        DataOutputStream dos = null;
        try {
            dos = new DataOutputStream(new FileOutputStream(file_inName));
            int a = 1, b = 1;
            for (int i = 0; i < n; i++) {
                dos.writeInt(a); // 写入 4 字节整数
                int next = a + b;
                a = b;
                b = next;
            }
            System.out.println("Fibonacci 序列已写入整数类型文件: " + file_inName);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (dos != null) {
                try {
                    dos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void readFibonacciBinary(String file_inName, int n) {
        DataInputStream dis = null;
        try {
            dis = new DataInputStream(new FileInputStream(file_inName));
            System.out.println("从二进制文件读取的整数内容如下：");
            for (int i = 0; i < n; i++) {
                int value = dis.readInt();
                System.out.println(value);
            }
        } catch (EOFException e) {
            // 到达文件末尾
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (dis != null) {
                try {
                    dis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
