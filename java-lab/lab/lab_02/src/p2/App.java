package p2;
/*
二、输入一组数创建带头结点的单链表（头插法）、在第 i 个位置插入值为 x 的结点、删除、
打印等操作，两个升序单链表合并为新的升序表。
如：
假设 L1 中有 5 个元素，依次为：1、2、3、4、5；L2 中有 3 个元素，依次为：6、7、8，
执行 L1.merge(L2)后，新表 L3 中的数据为： 1、2、3、4、5、6、7、8；

要求：在测试类 main 中必须对每个方法进行测试，且有相关的提示信息。

提高题：带头结点的单链表中的头结点信息为链表的结点个数，对上述功能加以修改。

 */
public class App {
    //不知道那个删除x是要删全部还是指定位置？都写吧
    public static void main(String[] args) {
        int[] a = { 5,4,3,3,3,2,3,1 };
        int[] b = { 8, 7,7, 6 };
        LinkedList L1 = new LinkedList();
        L1.insert(a);
        LinkedList L2 = new LinkedList();
        L2.insert(b);

        System.out.println("L1中的数据为：");
        L1.show();
        L1.delesingleX_order(3, 1);
        System.out.println("L1删除第1个3后：");
        L1.show();
        L1.deleAllX(3);
        System.out.println("L1删除所有3后：");
        L1.show();
        L1.insertX_orderi(20, 8);
        System.out.println("L1在第8个位置后插入20后：");
        L1.show();
        System.out.println("L2中的数据为：");
        L2.show();
        System.out.println("L1和L2合并为L3后：");
        L1.mergeup(L2);
        L1.show();
        L2.show();
        
    }
}


class LinkedList {// 带头结点的单链表

    int data;
    LinkedList next; // 引用类型

    LinkedList() {
        data = 0;
        next = null;
    } // 是本类的构造方法，初始化，用了java的语法糖不需要写this

    void insert(int[] a) { // 头插
        for (int i : a) {
            LinkedList t = new LinkedList();
            t.data = i;
            t.next = this.next;
            this.next = t;
            this.data++;
        }
    }


    void show() { // 打印
        LinkedList r = this.next;
        while (r != null) {
            System.out.print(r.data + " ");
            r = r.next;
        }
        System.out.println(" 链表长度为：" + this.data);
    }

    void deleAllX(int x) { // 删除所有值为x的结点
        LinkedList r = this.next;
        LinkedList pre = this;
        while (r != null) {
            if (r.data == x) {
                this.data--;
                pre.next = r.next;
                r = r.next;
            } else {
                pre = r;
                r = r.next;
            }

            // 好像写得一般只用一个指针就够了？算了好久没写链表太生疏了
        }
    }

    void delesingleX_order(int x, int n){      //删除第n个值为x的节点
        LinkedList pre = this;
        LinkedList r = this.next;
        int count = 0;
        while (r != null){
            if(r.data == x){
                count++;
                if(count == n){
                    this.data--;
                    pre.next = r.next;
                    break;
                }
            }
            pre = r;
            r = r.next;
        }
    }

    void insertX_orderi(int x, int i){    //在第i个结点后插入值为x的节点
        LinkedList r = this;
        int count = 0;
        while (r.next != null && count < i) {
            r = r.next;
            count++;
        }
        LinkedList t = new LinkedList();
        t.data = x;
        this.data++;
        t.next = r.next;
        r.next = t;
    }

    void mergeup(LinkedList h2) { // 有序单链表合并为升序表
        LinkedList r1 = this.next;
        LinkedList r2 = h2.next;
        LinkedList r = this;
        r.data += h2.data;
        while (r1 != null && r2 != null) {
            if (r1.data <= r2.data) {
                r.next = r1;
                r1 = r1.next;
            }
             else {
                LinkedList temp = new LinkedList();
                temp.data = r2.data;
                r.next = temp;
                r2 = r2.next;       //不想破坏L2的结构，所以又new了一个新节点
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

    // 补充完整

}