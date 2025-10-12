package p13;

import java.util.Scanner;
/*
 实现顺序表的基本操作(创建顺序表、某个位置插入数据、 打印)，两个升序表合并为一个新的升序表；并加以测试。
 */

/*
要求：
测试类中生成两个顺序表对象，其中La通过有参构造函数生成表且数据由数组赋值，Lb通过参构造函数有生成且数据通过键盘输入。

输入为：
2 4 7 11 21 0

输出结果：
La=1 3 5 6 9
Lb=2 4 7 11 21
在La的第4个位置插入8后的结果为：
1 3 5 6 8 9
将La、Lb合并成升序表，结果放在La中。La=1 2 3 4 5 6 7 8 9 11 21
 */

public class App{

    public static void main (String[] args) {

       SeqList La,Lb;
       int a[]={1,3,5,6,9};
       La=new SeqList(100,a); Lb=new SeqList(100);
       System.out.print("La=");
         La.printa();
         System.out.print("Lb=");
         Lb.printa();
         System.out.println("在La的第4个位置插入8后的结果为：");
         La.insert(4, 8);
         La.printa();
         La.merge(Lb);
         System.out.print("将La、Lb合并成升序表，结果放在La中。La=");
         La.printa();

    }

}

class SeqList{          //顺序表结构=数组+表长

   int []a;   int len;

   SeqList(int size,int[] b){  
       a = new int[size];
       len = b.length;

       for(int i = 0;i < len;i++){
           a[i] = b[i];
       }
    }

    SeqList(int size){          
         a = new int[size];
         len = 0;

        Scanner in = new Scanner(System.in);
        int x = in.nextInt();
        int i = 0;
        while (x != 0) {
            a[i] = x;
            x = in.nextInt();
            i++;
            len++;
        }
        in.close();
    }

    void printa(){
        for(int i = 0; i < len; i++){
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }
    

    void insert(int pos, int value){
        for(int i = len; i > pos; i--){
            a[i] = a[i-1];
        }
        a[pos] = value;
        len++;
    }


    void merge(SeqList other){
        int[] temp = new int[len + other.len];
        int i = 0, j = 0, k = 0;
        
        while(i < len && j < other.len){
            if(a[i] <= other.a[j]){
                temp[k++] = a[i++];
            } else {
                temp[k++] = other.a[j++];
            }
        }
        
        while(i < len){
            temp[k++] = a[i++];
        }
        
        while(j < other.len){
            temp[k++] = other.a[j++];
        }
        
        for(int m = 0; m < k; m++){
            a[m] = temp[m];
        }
        len = k;
    }




    //补充完整

}