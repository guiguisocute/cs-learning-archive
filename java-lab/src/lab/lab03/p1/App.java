package lab.lab03.p1;
/*
TODO:
    1.设计一个三角形类，有如下约束：
        a.) 三角形只能有三条边；
        b.) 可根据三条边构造普通三角形对象， 或者根据腰和底构造等腰三角形，
        或者只输入一条边，构造等边三角形；
        c.) 三角形提供四项服务：
            计算周长、计算面积、 修改三条边的值、输出三条边的信息。
            注：面积计算的海伦公式为：
                Math.sqrt(p*(p-a)*(p-b)*(p-c))，
            其中 p 是半周长，a/b/c 是边,Math.sqrt()是开平方函数。
        d.) 设计直角三角形(即 Rt 三角)。
            直角三角拥有普通三角的全部服务，并有特色：
            可以根据三条边构造对象，
            也可以根据两条直角边，斜边自动算出构造对象。
            输出直角三角形的相关信息。
 */
public class App {
    public static void main(String[] args) {
        Triangle t1 = new Triangle(2, 3, 4);
        Triangle t2 = new Triangle(3, 5);
        Triangle t3 = new Triangle(3);

        t1.disp();
        t2.disp();
        t3.disp();

        Rt_Triangle r1 = new Rt_Triangle(3, 4);

        System.out.println(r1);
        System.out.println("等边三角形的面积为：" + t3.area());
        System.out.println("直角三角形的面积为：" + r1.area());

    }

}

class Triangle {
    double area;
    double long_1;
    double long_2;
    double long_3;

    Triangle(double long_1_in, double long_2_in, double long_3_in) {
        long_1 = long_1_in;
        long_2 = long_2_in;
        long_3 = long_3_in;
    }

    Triangle(double long_1_in, double long_2_in) {
        this(long_1_in, long_1_in, long_2_in);
    }

    Triangle(double long_1_in) {
        this(long_1_in, long_1_in, long_1_in);
    }

    public String toString() {
        return "普通三角形的边为：x=" + long_1 + ",y=" + long_2 + ",z=" + long_3;
    }

    void disp() {
        System.out.println(this);
    }

    double area() {
        double p = (long_1 + long_2 + long_3) / 2;
        return Math.sqrt(p * (p - long_1) * (p - long_2) * (p - long_3));
    }
}

class Rt_Triangle extends Triangle {
    Rt_Triangle(double long_1_in, double long_2_in) {
        super(long_1_in, long_2_in, Math.sqrt(long_1_in * long_1_in + long_2_in * long_2_in));
    }

    public String toString() {
        return "直角三角形的边为：x=" + long_1 + ",y=" + long_2 + ",z=" + long_3;
    }
}
