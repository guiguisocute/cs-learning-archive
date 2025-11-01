/*
TODO:写一个圆柱体类,包含一个内部类圆.要求圆的面积和周长,圆柱体的表面积和体积.
输出结果为：
该圆柱体的体积为：37.68
 */

package xuexitong_test.week_9.p1;


public class Ci_Cy {
    public static void main(String[] args) {
        Cylinder cy1=new Cylinder(2.0,3.0);
        cy1.disVol();
    }
}

class Cylinder{
    double high;
    double Vol;
    double SurfaceArea;
    Circle circle;

    Cylinder(double Circle_r_in, double Cylinder_high_in){
        circle = new Circle(Circle_r_in);
        high = Cylinder_high_in;
        Vol = high * circle.Area;
    }
    void disVol(){
        System.out.println("该圆柱体的体积为：" + Vol);
    }
    void disSurfaceArea(){
        System.out.println("该圆柱体的表面积为：" + SurfaceArea);
    }


    class Circle{
        double r;
        double Perimeter;
        double Area;

        Circle(double Circle_r_in){
            r = Circle_r_in;
            Perimeter = r * 2 * 3.14;
            Area = r * r * 3.14;
        }
        void disPerimeter(){
            System.out.println("该圆柱里的圆周长为：" + Perimeter);
        }

        void disArea(){
            System.out.println("该圆柱里的圆面积为：" + Area);
        }

    }
}


