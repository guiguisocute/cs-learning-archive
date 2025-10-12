package p1;

/*
一、构造顺序表，并满足如下要求：
1、可以在创建顺序表对象时指定容量；若未指定容量，则按默认容量 10 创建顺序表；
2、编写方法 void append()，在顺序表末尾增加一组元素（数量未知）。当顺序表满时，
则自动扩容 1/2。如原容量 10，满时新容量为 15;
3、编写方法 void show()，输出表信息；
4、实现允许直接打印顺序表对象，即输出顺序表的所有元素；【重写父类toString()方法；】
5、编写方法 void merge(y)：若调用 x.merge(y)，效果为：将 y 中所有元素插入到 x 的首
部。

如：
假设 x 中有 5 个元素，依次为：1、2、3、4、5；y 中有 3 个元素，依次为：6、7、8，
执行 x.merge(y)后，x 中的数据为：6、7、8、1、2、3、4、5

要求：
在测试类 main 中必须对每个方法进行测试，且有相关的提示信息
 */
public class App {

    public static void main(String[] args) {

        SeqList x;
        SeqList y;
        int[] a = { 1, 2, 3, 4, 5 };
        int[] b = {6,7,8,9};
        x = new SeqList(5, a);
        y = new SeqList(b);
        x.show("x");
        y.show("y");
        SeqList xpy = new SeqList(5,a);
        xpy.append(b);
        xpy.show("append x + y后");

        x.merge(y);
        x.show("x merge y 后");


        // 补充完整

    }

}

class SeqList { // 顺序表结构=数组+表长

    int[] a;
    int len;

    SeqList(int size, int[] b) {
        a = new int[size];
        len = b.length;

        System.arraycopy(b, 0, a, 0, len);
    }

    SeqList(int[] b) {
        len = 10;
        a = new int[10];
        len = b.length;

        System.arraycopy(b, 0, a, 0, len);
    }


    void show(String s) {
        System.out.println(s + "顺序表数据为：" + this +"; 表长为：" + len + "; 实际容量为" + a.length);
    }

    @Override
    public String toString(){
        String res = "";
        int j = 0;
        for(int i : this.a){
            if(j < len)
                res += i + " ";         //这个其实并不完美，因为字符串的加法（即连接），其实并不能操作容器，实质上是加完之后再自动new了一个string再转引用，所以如果数组很大，这个方法会炸堆
                j++;
        }
        return res;
    }


    void append(int[] add){
        int newlength = a.length;
        while(a.length + add.length > newlength){
            newlength = (int)(newlength * 1.5);
        }

        int[] b = new int[newlength];
        System.arraycopy(a, 0,b,0 ,len);
        for(int i : add){
            b[len] = i;
            len++;
        }
        a = b;
    }

    void merge(SeqList y){
        int[] c = new int[len + y.len];
        int j = 0;
        for(int i : y.a){
            if(j < y.len){
                c[j] = i;
                j++;
            }

        } 
        for(int i : a){
            if (j < len + y.len) {
                c[j] = i;
                j++;
            }

        }
        a = c;
        len = j;
    }

}

