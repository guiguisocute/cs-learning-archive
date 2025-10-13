package p14;
import java.util.Scanner;
//编写方法 void append()，在顺序表末尾增加一组元素（数量未知）。当顺序表满时， 则自动扩容 1/2。

/*
输入为：
8 4 3 0

输出结果：
La=1 3 5 6 9
在末尾所加后，La=1 3 5 6 9 8 4 3
 */
public class App{

    public static void main (String[] args) {

        SeqList La;
        int a[]={1,3,5,6,9};
        La=new SeqList(5,a);
        System.out.print("La=");
        La.printa();
        La.append();

        //补充完整

    }

}

class SeqList{          //顺序表结构=数组+表长

    int []a;   int len;

    SeqList(int size, int[] b) {
        a = new int[size];
        len = b.length;

        for (int i = 0; i < len; i++) {
            a[i] = b[i];
        }
    }

    void printa(){
        for(int i = 0; i < len; i++){
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }

    void append(){
        Scanner in = new Scanner(System.in);
        int x;
        while(true){
            x = in.nextInt();
            if(x == 0) {
                break;
            }

            if(len == a.length){
                int[] b = new int[a.length + a.length / 2];
                for(int i = 0; i < a.length; i++){
                    b[i] = a[i];
                }
                a = b;
            }
            
            a[len] = x;
            len++;
        }
        in.close();
        System.out.print("在末尾所加后，La=");
        printa();
    }

}