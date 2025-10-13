package lab01;

public class lab1 {
    public static void main(String[] args) {
        System.out.println("\n----");
        System.out.println("test request 0:");
        H h = new H();
        h.hello();
        System.out.println("----\n");
        System.out.println("\n----");
        System.out.println("test request 1:");
        request1 p = new request1();
        p.func_print_all_alphabet();
        System.out.println("----\n");
        System.out.println("\n----");
        System.out.println("test request 2:");
        request2 q = new request2();
        q.print_9x9chart();
        System.out.println("----\n");
        System.out.println("\n----");
        System.out.println("test request 3:");
        request3 r = new request3();
        long[] fibo = r.print_fibo(20);
        int i = 0;
        for(long num : fibo){
            System.out.print("fibo[" + i + "] " + "= " + num + "\n");
            i++;
        }
        System.out.println("----\n");
        System.out.println("\n----");
        System.out.println("test request 4:");
        request4 s = new request4();
        s.print_yanghui_triangle(10);
        System.out.println("----\n");
        

    }
}

class H {
    public void hello(){
        System.out.println("Hello.java");
    }
}


class request1{
    public void func_print_all_alphabet (){
        for(char ch = 'A'; ch <= 'z'; ch++) {
            if(ch > 'Z' && ch < 'a') continue;
            System.out.print(ch + " ");
        }
        System.out.println();
    }
}

class request2{
    public void print_9x9chart() {
        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= i; j++){
                System.out.print(i + "*" + j + "=" + (i*j) + "\t");
            }
            System.out.println();
        }
    }
}

class request3{
    public long[] print_fibo(int n){
        long[] fibo = new long[n];
        fibo[0] = 1;
        fibo[1] = 1;
        for(int i = 2; i < n; i++){
            fibo[i] = fibo[i-1] + fibo[i-2];
        }
        return fibo;
    }
}

class request4{
    public void print_yanghui_triangle(int n){
        int[][] yh = new int [n][n];
        for(int i = 0; i < n; i++){
            yh[i][0] = 1;
            yh[i][i] = 1;
            for(int j = 1; j < i; j++){
                yh[i][j] = yh[i-1][j-1] + yh[i-1][j];
            }
        }

        for(int[] row : yh){
            for(int num : row){
                if(num != 0)
                    System.out.print(num + " ");
            }
            System.out.println();
        }
    }
}

