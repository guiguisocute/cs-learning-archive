package p1;

/*
创建Point类，

要求：1.三个构造方法分别为有参构造方法，无参构造方法，拷贝构造方法。

2.实现方法chang(int intervalX，int intervalY)用于是改变坐标，如原坐标为（2，3），intervalX=3,interval=-2,则改变后坐标为（5,1）.

3.实现toString()和equals() 方法，输出方法。

4.main函数中采用三种方式生成三个Point实例，最后输出结果。

输出结果：

点的坐标为:(0,0)

点的坐标为:(2,3)

点的坐标为:(2,3)

true

p2改变坐标后为:点的坐标为:(5,1)

false
 */
class Point_ks {

    public static void main(String[] args){

        Point p1=new Point();

        System.out.println(p1);

        Point p2=new Point(2,3);

        System.out.println(p2);

        Point p3=new Point(p2);

        System.out.println(p3);

        System.out.println(p2.equals(p3));

        p2.change(3,-2);

        System.out.print("p2改变坐标后为:");

        System.out.println(p2);

        System.out.println(p2.equals(p3));

    }

}

class Point{//补充完整
    int x;
    int y;
    Point(){
        x = 0;
        y = 0;
    }//无参

    Point(int x_in,int y_in){
        x = x_in;
        y = y_in;
    }//有参

    Point(Point a){
        x = a.x;
        y = a.y;
    }

    void change(int intervalX,int intervalY){
        x += intervalX;
        y += intervalY;
    }

    @Override
    public String toString(){
        return "点的坐标为:(" + x +","+y+")";
    }

    public boolean equals(Point in){
        if(in.x == x && in.y == y){
            return true;
        }
        return false;
    }
}

