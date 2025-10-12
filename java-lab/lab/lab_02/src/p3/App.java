package p3;
/*
实现一个矩阵类，实现初始化矩阵，矩阵转置，矩阵加法及输出矩阵等功能。
矩阵元素可由随机数生成 100 以内的整数。
 */
import java.util.Random;
import java.util.Arrays;

public class App {
    public static void main(String[] args) {
        martrix m1 = new martrix(3, 4);
        martrix m2 = new martrix(3, 4);
        martrix m3 = new martrix(4, 3);
        martrix m4 = new martrix(3, 4);
        System.out.println("矩阵m1：");
        m1.show(m1);
        System.out.println("矩阵m2：");
        m2.show(m2);
        System.out.println("矩阵m1转置：");
        m3 = m1.transMartrix(m1);
        m3.show(m3);
        System.out.println("矩阵m1+m2：");
        m4 = m4.add(m1, m2);
        m4.show(m4);
        
    }
}

class martrix{
    private int row;
    private int col;
    private int[][] a;

    martrix(int r,int c){
        row = r;
        col = c;
        a = new int[row][col];
        Random data = new Random();
        for(int i = 0; i < row;i++){
            for(int j = 0; j < col; j++){
                a[i][j] = data.nextInt(100);
            }
        }
    }

    martrix transMartrix(martrix inputM){
        martrix t = new martrix(inputM.col, inputM.row);
        t.col = inputM.row;
        t.row = inputM.col;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                t.a[j][i] = inputM.a[i][j];
            }
        }
        return t;
    }

    martrix add(martrix inputM1, martrix inputM2){
        martrix t = new martrix(inputM1.row, inputM1.col);
        for(int i = 0; i < row;i++){
            for(int j = 0; j < col; j++){
                t.a[i][j] = inputM1.a[i][j] + inputM2.a[i][j];
            }
        }
        return t;
    }

    void show(martrix in){
        // System.out.println(Arrays.deepToString(in.a));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                System.out.printf("%4d",in.a[i][j]);
            }
            System.out.println();
        }
    }
}
