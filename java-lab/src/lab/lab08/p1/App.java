package lab.lab08.p1;

//TODO: 实现普通文件的复制，要求缓冲区设为 1024 字节，不考虑各类异常情形。

import java.io.*;

public class App {
    public static void main(String[] args) {
        String source = "source.txt";
        String dest = "dest.txt";

        try {
            FileOutputStream fos = new FileOutputStream(source);
            fos.write("测试文件复制MD5=00010110000".getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        copyFile(source, dest);
        System.out.println("文件复制完成！");
    }

    public static void copyFile(String srcPath_in, String destPath_in) {
        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(srcPath_in);
            fos = new FileOutputStream(destPath_in);

            byte[] buffer = new byte[1024];
            int len;

            while ((len = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, len);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {

            try {
                if (fis != null)
                    fis.close();
                if (fos != null)
                    fos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
