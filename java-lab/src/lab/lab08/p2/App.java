package lab.lab08.p2;
//TODO:将 Fibonacci 序列值写入一个文本文件中并读取输出到屏幕上。

import java.io.*;

public class App {
    public static void main(String[] args) {
        String fileName = "fibonacci.txt";
        int n = 20;

        writeFibonacci(fileName, n);

        readAndPrint(fileName);
    }

    public static void writeFibonacci(String fileName_in, int n) {
        PrintWriter out = null;
        try {
            out = new PrintWriter(new FileWriter(fileName_in));
            int a = 1, b = 1;
            for (int i = 0; i < n; i++) {
                out.println(a);
                int next = a + b;
                a = b;
                b = next;
            }
            System.out.println("Fibonacci 序列已写入文本文件: " + fileName_in);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (out != null)
                out.close();
        }
    }

    public static void readAndPrint(String fileName_in) {
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(fileName_in));
            String line;
            System.out.println("从文件读取的内容如下：");
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
