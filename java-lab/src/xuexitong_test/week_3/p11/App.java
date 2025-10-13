package p11;
/*
编程实现带头结点的单链表，实现如下操作：
头插法创建链表且以数组作为参数;尾插法创建链表且数据由键盘输入并以-1结束输入;删除所有值为x的数 据;打印；有序单链表合并为升序表。

要求：
链表h1由尾插法创建, 链表h2由头插法创建。

输入：
2 4 8 11 -1

输出结果：

输出h1:
2 4 8 11
输出h2:
1 2 2 2 3 5 7 9 10 12
删除h2所有值为2的结点后：1 3 5 7 9 10 12
将两个升序链表h1，h2合并到h1中，结果为：1 2 3 4 5 7 8 9 10 11 12

 */
import java.util.Scanner;

public class App{

    public static void main(String[] args){

        LinkedList h1=new LinkedList(0);
        LinkedList h2=new LinkedList(0);

        int[] a={12,10,9,7,5,3,2,2,2,1};

        h1.append();
        System.out.println("输出h1:");
        h1.show();

        h2.insert(a);
        System.out.println("输出h2:");
        h2.show();

        System.out.print("删除h2所有值为2的结点后：");
        h2.deleAllX(2);
        h2.show();

        h1.mergeup(h2);
        System.out.print("将两个升序链表h1，h2合并到h1中，结果为：");
        h1.show();
        

    }

}

class LinkedList{//带头结点的单链表

    int data;
    LinkedList next;    //引用类型
    LinkedList(int x){ data = x; next = null; }     //是本类的构造方法，初始化，用了java的语法糖不需要写this
    

    void insert(int[] a){   //头插
        for(int i : a){
            LinkedList t = new LinkedList(i);
            t.next = this.next;
            this.next = t;
        }
    }

    void append(){          //尾插(注意无传参)
        Scanner in = new Scanner(System.in);
        int x;
        LinkedList r = this;    //尾指针
        while (true) {
            x = in.nextInt();
            if(x == -1){
                break;
            }
            LinkedList t = new LinkedList(x);
            r.next = t;
            r = t;
        }
        in.close();
    }

    void show(){        //打印
        LinkedList r = this.next;
        while (r != null) {
            System.out.print(r.data + " ");
            r = r.next;
        }
        System.out.println();
    }

    void deleAllX(int x){   //删除所有值为x的结点
        LinkedList r = this.next;
        LinkedList pre = this;
        while (r != null) {
            if(r.data == x){
                pre.next = r.next;
                r = r.next;
            }else{
                pre = r;
                r = r.next;
            }
            
            //好像写得一般只用一个指针就够了？算了好久没写链表太生疏了
        }
    }

    void mergeup(LinkedList h2){ //有序单链表合并为升序表
        LinkedList r1 = this.next;
        LinkedList r2 = h2.next;
        LinkedList r = this;
        while (r1 != null && r2 != null) {
            if(r1.data <= r2.data){
                r.next = r1;
                r1 = r1.next;
            }else{
                r.next = r2;
                r2 = r2.next;
            }
            r = r.next;
        }
        if (r1 != null) {
            r.next = r1;
        }
        if (r2 != null) {
            r.next = r2;
        }
    }

//补充完整

}
