package lab06.$4_clickButton2TransColor;

/*
TODO:实现如图(图在项目根目录的referPic里)所示的功能。（事件处理用两种方式实现，其中一种必须采用内部类方式）
    (1)点击 Red 按钮后背景色变为红色，下面的标签变为"this is Red"
    (2)当鼠标放在 Red 按钮上时按钮变红，鼠标离开时恢复原来的颜色
    (3)Green 和 blue 按钮实现相同的功能。
 */

import javax.swing.*;
import java.awt.*;


public class Main {
    public static void main(String[] args) {
        Deal_click dealClick = new Deal_click();
        ColorFrame c =  new ColorFrame(dealClick);
        dealClick.setSourceFrame(c);
    }
}

//点击事件用Deal分离的方法做，悬浮事件用内部匿名类去做
class ColorFrame extends JFrame{
    JButton red_Button,green_Button,blue_Button;
    JLabel label;
    Deal_click deal_click_mouseEntered;


    public ColorFrame(Deal_click deal_click_mouseEntered){
        initUI();
        initListener();
        initListener(deal_click_mouseEntered);
    }

    void initUI(){
        this.setLayout(new BorderLayout());
        this.setSize(300,100);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel buttonPanel = new JPanel(new FlowLayout());
        red_Button = new JButton("Red");
        green_Button = new JButton("GREEN");
        blue_Button = new JButton("blue");
        buttonPanel.add(red_Button);
        buttonPanel.add(green_Button);
        buttonPanel.add(blue_Button);

        JPanel labelPanel = new JPanel(new FlowLayout());
        label = new JLabel("测试红色");
        Font f=new Font("宋体",Font.PLAIN,16);
        label.setFont(f);
        labelPanel.add(label);



        this.add(buttonPanel,BorderLayout.CENTER);
        this.add(labelPanel,BorderLayout.SOUTH);

        this.setVisible(true);
    }
    void initListener(){

    }
    void initListener(Deal_click deal_click_mouseEntered){

    }
}
class Deal_click {
    ColorFrame sourceFrame;

    public void setSourceFrame(ColorFrame sourceFrame) {
        this.sourceFrame = sourceFrame;
    }
}

