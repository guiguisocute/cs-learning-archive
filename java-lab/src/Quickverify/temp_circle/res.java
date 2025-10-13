package temp_circle;

import java.util.*;
public class res {
    public static void main(String[] args) {

    }
}

class circle {
    protected  double r;
    static final double pi = 3.14159;

    double getC(){
        return  2*r*pi;
    }

    double getS(){
        return r*r*r*pi;
    }

    public circle(){
        Random a = new Random();
        r = a.nextDouble();
    }
    public circle(double in){
        r = in;
    }
    public circle(circle a){
        this(a.r);
    }


    @Override
    public  String toString(){
        return "r = " + r + '\n' + "c = " + this.getC() + '\n' + "s = " + this.getS() + '\n';

    }

    boolean equal(circle in){
        return in.r == r;
    }
}

class circle_col_i{
    circle a;
    protected  double h;

    circle_col_i(){
        a = new circle(0);
        h = 0;
    }

    circle_col_i(circle in_r,double in_h){
        h = in_h;
        a = in_r;
    }

    double solvC(){

    }
}

class circle_col_e extends circle{
    double h;

    circle_col_e(double in_r,double in_h){
        super(in_r);
        this.h = in_h;
    }

    circle_col_e(){
        this(0,0);
    }
}