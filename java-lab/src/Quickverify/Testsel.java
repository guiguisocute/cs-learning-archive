package Quickverify;

import java.io.*;

public class Testsel {
    public static void main(String[] args) {
        // 创建处理斐波那契数列文件的对象
        FabniText fabniText = new FabniText("fabni.txt");

        // 调用写入方法
        fabniText.writeToText();

        // 为了验证，我们可以读取并打印出来 (可选)
        System.out.println("--- Reading file content ---");
        fabniText.readFromText();
    }
}

class FabniText {
    private String filename; // 文件名

    public FabniText(String filename) {
        this.filename = filename;
    }

    // 将斐波那契数列写入文件
    public void writeToText() {
        int f1 = 1;
        int f2 = 1;

        // 使用 try-with-resources 语法，自动关闭流，防止资源泄漏
        try (FileWriter fileWriter = new FileWriter(filename)) {
            // 写入前两个数
            fileWriter.write(f1 + "\n");
            fileWriter.write(f2 + "\n");

            int fn; // 声明 fn 变量
            // 循环计算接下来的数 (从第3个到第20个)
            for (int i = 3; i <= 20; i++) {
                fn = f1 + f2;
                // write方法需要字符串或int(作为char)，这里我们加 "\n" 转为字符串写入
                fileWriter.write(fn + "\n");
                f1 = f2;
                f2 = fn;
            }
            System.out.println("成功写入斐波那契数列到 " + filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 从文件读取内容
    public void readFromText() {
        // 使用 FileReader 读取字符流
        try (FileReader fileReader = new FileReader(filename)) {
            int data;
            // read() 返回读取的一个字符的整数编码，如果读到末尾返回 -1
            while ((data = fileReader.read()) != -1) {
                // 将整数编码强制转换为 char 显示
                System.out.print((char) data);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}