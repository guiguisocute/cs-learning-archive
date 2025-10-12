```java
package temp;

public class Main {
    public static void main(String[] args) {
        int[] b = {1,2,3,4,5,6};
        S_L a = new S_L(6,b);
        System.out.println(a);
        int [] c = {5,6,7,8};
        a.append(c);
        System.out.println(a);

    }
}

class S_L{
    int[] arr;
    int len;

    S_L(int size,int[] in){
        arr = new int[size];
        len = in.length;
        System.arraycopy(in, 0, arr, 0, len);
    }

    @Override
    public String toString(){
        String res = "";
        int j = 0;
        for(int i : arr){
            if(j < len){
            res += i + " ";
            j++;
            }
            

        }
        return res;
    }

    void append(int[] add){
        int newlength = arr.length;
        while(arr.length + add.length > newlength){
            newlength = (int)(newlength * 1.5);
        }

        int[] b = new int[newlength];
        System.arraycopy(arr, 0,b,0 ,len);
        for(int i : add){
            b[len] = i;
            len++;
        }
        arr = b;
    }


}
```

```java
package temp;


public class Main {
    public static void main(String[] args) {
        int[] b = {1,2,3,4,5,6};
        S_L a = new S_L(6,b);
        System.out.println(a);
        int [] c = {5,6,7,8};
        a.append(c);
        System.out.println(a);

    }
}

class S_L{
    int[] arr;
    int len;

    S_L(int size,int[] b){
        arr = new int[size];
        len = b.length;
        System.arraycopy(b,0,arr,0,len);
    }

    @Override
    public String toString(){
        // String res = "";
        StringBuilder res2 = new StringBuilder(1024);           //初始容量为16，传参自定义
        int j = 0;
        for(int i : arr){
            if(j < len){
                // res += i + " ";     // 浪费内存，还会影响GC效率。
                res2.append(i);     //apend直接在末尾插传参只有一个而且可以为任意值，insert可以在第一个传参中定义偏移量（插入位置）
                res2.append(" ");
                j++;
            }
        }
        return res2.toString();
    }  

    void append(int[] in){
        int newsize = arr.length;
        while (newsize < arr.length + in.length) {
            newsize = (int)(newsize * 1.5);
        }
        int[] b = new int[newsize];
        System.arraycopy(arr,0,b,0,len);
        for(int i : in){
            b[len] = i;
            len++;
        } 
        arr = b;
    }

}
``