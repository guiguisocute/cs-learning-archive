package lab.lab05.p2;

/*
TODO:写一个圆柱体类,包含一个内部类圆.要求圆的面积和周长,圆柱体的表面积和体积.
 */

public class App {
    public static void main(String[] args) {
        Cylinder cy1 = new Cylinder(3.0, 3.0);
        cy1.disVol();
        cy1.disSurfaceArea();
        cy1.circle.disArea();
        cy1.circle.disPerimeter();
    }
}

class Cylinder {
    double high;
    double Vol;
    double SurfaceArea;
    Circle circle;

    Cylinder(double Circle_r_in, double Cylinder_high_in) {
        circle = new Circle(Circle_r_in);
        high = Cylinder_high_in;
        Vol = high * circle.Area;
        SurfaceArea = 2 * circle.Area + circle.Perimeter * high;
    }

    void disVol() {
        System.out.printf("该圆柱体的体积为：%.2f\n", Vol);
    }

    void disSurfaceArea() {
        System.out.printf("该圆柱体的表面积为：%.2f\n", SurfaceArea);
    }

    class Circle {
        double r;
        double Perimeter;
        double Area;

        Circle(double Circle_r_in) {
            r = Circle_r_in;
            Perimeter = r * 2 * 3.14;
            Area = r * r * 3.14;
        }

        void disPerimeter() {
            System.out.printf("该圆柱里的圆周长为：%.2f\n", Perimeter);
        }

        void disArea() {
            System.out.printf("该圆柱里的圆面积为：%.2f\n", Area);
        }

    }
}
