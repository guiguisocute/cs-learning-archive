package xuexitong_test.week_6.p2;

/*
一般方法实现形状智能面积计算器。

要求：所有属性都设置为私有，Rectangle、Sanjiao 和Circle类中都必须实现toString（）方法用于返回成员的相关信息。若周长无法计算，显示为“无法计算”；如：若三角形有多个构造函数。若给出的是“底和高”，则周长识别结果为：只有底和高无法计算周长。
输出结果为：
类型：矩形面积为：6.0,周长为：10.0,属性为：高=2 宽=3
类型：圆形面积为：314.0,周长为：62.800000000000004,属性为：半径=10
类型：三角形面积为：3.0,周长为：只有底和高无法计算周长。属性为：底a=2.0,高ha=3.0
类型：三角形面积为：2.9047375096555625,周长为：9.0,属性为：三边为：a=2.0,b=3.0,c=4.0


 */
public class App {
    public final static double PI = 3.14;

    public static void main(String args[]) {

        Recognizer rcg = new Recognizer();

        Shape[] s = { new Rectangle(2, 3), new Circle(10), new SanJiao(2, 3), new SanJiao(2, 3, 4) };

        for (int i = 0; i < s.length; i++)
            rcg.showInfo(s[i]);

    }

}

class Recognizer { // 智能识别器类

    public void showInfo(Shape s) {// 输入出形状名，面积、周长和属性

        System.out.println("类型：" + s.type + "面积为：" + s.area + ",周长为：" + s.zhouchang_s + "属性为：" + s);
    }

}

class Shape {// 形状类

    // 补充完整}
    String type;
    double area;
    double zhouchang;
    String zhouchang_s;
    Shape(){
        area = -1;
        zhouchang = -1;
    }
}
    class Rectangle extends Shape { // 矩形类
        // 补充完整
        int rectangle_gao;
        int rectangle_kuan;
        Rectangle(int  rectangle_gao_in,int rectangle_kuan_in){
            type = "矩形";
            rectangle_gao = rectangle_gao_in;
            rectangle_kuan = rectangle_kuan_in;
            area = rectangle_gao * rectangle_kuan;
            zhouchang = 2.0 * rectangle_kuan + 2.0 * rectangle_gao;
            zhouchang_s = String.valueOf(zhouchang);
            zhouchang_s += ",";
        }

        @Override
        public String toString() {
            return "高="+ rectangle_gao +" 宽=" + rectangle_kuan;
        }
    }

    class Circle extends Shape {// 圆形类
        int circle_r;
        Circle(int circle_r_in){
            type = "圆形";
            circle_r = circle_r_in;
            area = circle_r * circle_r * App.PI;
            zhouchang = circle_r * 2.0 * App.PI;
            zhouchang_s = String.valueOf(zhouchang);
            zhouchang_s += ",";
        }

        @Override
        public String toString() {
            return "半径="+ circle_r;
        }
        // 补充完整
    }

class SanJiao extends Shape {//三角形

    //补充完整
    double Sanjiao_di;
    double Sanjiao_gao;
    double Sanjiao_lingwaiyibian;

    SanJiao(double Sanjiao_di_in, double Sanjiao_gao_in, double Sanjiao_lingwaiyibian_in){
        type = "三角形";
        Sanjiao_di = Sanjiao_di_in;
        Sanjiao_gao = Sanjiao_gao_in;
        Sanjiao_lingwaiyibian = Sanjiao_lingwaiyibian_in;
        double p = (Sanjiao_gao + Sanjiao_di + Sanjiao_lingwaiyibian) / 2;
        area = Math.sqrt(p * (p - Sanjiao_gao) *  (p - Sanjiao_di) * (p - Sanjiao_lingwaiyibian));
        zhouchang = Sanjiao_gao + Sanjiao_di +Sanjiao_lingwaiyibian;
        zhouchang_s = String.valueOf(zhouchang);
        zhouchang_s += ",";
    }
    SanJiao(double Sanjiao_gao_in, double Sanjiao_di_in){
        this(Sanjiao_gao_in,Sanjiao_di_in,Sanjiao_gao_in);
        zhouchang_s = "只有底和高无法计算周长。";
        area = Sanjiao_di * Sanjiao_gao / 2;

    }

    @Override
    public String toString() {
        if (Sanjiao_lingwaiyibian == Sanjiao_di){
            return "底a="+ Sanjiao_di + ",高ha=" + Sanjiao_gao;
        }else{
            return "三边为：a=" + Sanjiao_di + ",b=" + Sanjiao_gao + ",c=" + Sanjiao_lingwaiyibian;
        }

    }
}
