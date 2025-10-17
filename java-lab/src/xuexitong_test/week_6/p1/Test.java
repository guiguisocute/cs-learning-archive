package xuexitong_test.week_6.p1;



/*
输出结果为：

普通三角形的边为：x=2.0,y=3.0,z=4.0
普通三角形的边为：x=3.0,y=3.0,z=5.0
普通三角形的边为：x=3.0,y=3.0,z=3.0
直角三角形的边为：x=3.0,y=4.0,z=5.0
等边三角形的面积为：3.897114317029974
直角三角形的面积为：6.0
 */
public class Test {

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

class Triangle{
    double area;
    double long_1;
    double long_2;
    double long_3;
    Triangle(double long_1_in, double long_2_in, double long_3_in){
        long_1 = long_1_in;
        long_2 = long_2_in;
        long_3 = long_3_in;
    }
    Triangle(double long_1_in, double long_2_in){
        this(long_1_in,long_1_in,long_2_in);
    }
    Triangle(double long_1_in){
        this(long_1_in,long_1_in,long_1_in);
    }


    public String toString(){
        return "普通三角形的边为：x=" + long_1 + ",y=" + long_2 + ",z=" + long_3;
    }
    void disp(){
        System.out.println(this);
    }
    double area(){
        double p = (long_1 + long_2 + long_3) / 2;
        return Math.sqrt(p * (p - long_1) * (p - long_2) * (p - long_3));
    }
}

class Rt_Triangle extends Triangle{
    Rt_Triangle(double long_1_in, double long_2_in){
        super(long_1_in,long_2_in,Math.sqrt(long_1_in * long_1_in + long_2_in * long_2_in));
    }

    public String toString(){
        return "直角三角形的边为：x=" + long_1 + ",y=" + long_2 + ",z=" + long_3;
    }
}