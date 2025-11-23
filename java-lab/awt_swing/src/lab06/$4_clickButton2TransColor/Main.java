package lab06.$4_clickButton2TransColor;

/*
TODO:实现如图(图在项目根目录的referPic里)所示的功能。（事件处理用两种方式实现，其中一种必须采用内部类方式）
    (1)点击 Red 按钮后背景色变为红色，下面的标签变为"this is Red"
    (2)当鼠标放在 Red 按钮上时按钮变红，鼠标离开时恢复原来的颜色
    (3)Green 和 blue 按钮实现相同的功能。
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


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
        red_Button = createStyledButton("Red");
        green_Button = createStyledButton("GREEN");
        blue_Button = createStyledButton("Blue");
        buttonPanel.add(red_Button);
        buttonPanel.add(green_Button);
        buttonPanel.add(blue_Button);
        buttonPanel.setOpaque(false);       //这个透明度的属性也很呃呃，panel默认不透明，但button默认透明，什么审美啊！

        JPanel labelPanel = new JPanel(new FlowLayout());
        label = new JLabel("");
        Font f=new Font("宋体",Font.PLAIN,16);
        label.setFont(f);
        labelPanel.add(label);



        this.add(buttonPanel,BorderLayout.CENTER);
        this.add(labelPanel,BorderLayout.SOUTH);

        this.setVisible(true);
    }

    private JButton createStyledButton(String text) {
        JButton btn = new JButton(text);
        btn.setFocusPainted(false); //隐藏焦点框，毕竟button这种设计就不是让你用Tab去操作的，但其实我也想搞懂一下Windows的界面是如何实现焦点和点击共存的
        btn.setOpaque(true); // 不知道为什么swing默认按钮式透明的，这明显不符合直觉啊
        btn.setBackground(Color.LIGHT_GRAY); // swing的默认背景渐变蓝真的丑得我想死……
        return btn;
    }

    private void initListener(){
        MouseAdapter mouseAdapter = new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                JButton btn = (JButton) e.getSource();
                if(btn == red_Button){
                    btn.setBackground(Color.red);
                }else if(btn == green_Button){
                    btn.setBackground(Color.green);
                }else if(btn == blue_Button){
                    btn.setBackground(Color.blue);
                }
            }

            @Override
            public void mouseExited(MouseEvent e) {
                JButton btn = (JButton) e.getSource();
                btn.setBackground(Color.LIGHT_GRAY);
            }
        };
        red_Button.addMouseListener(mouseAdapter);
        green_Button.addMouseListener(mouseAdapter);
        blue_Button.addMouseListener(mouseAdapter);
    }
    private void initListener(Deal_click deal_click_mouseEntered){
        red_Button.addActionListener(deal_click_mouseEntered);
        blue_Button.addActionListener(deal_click_mouseEntered);
        green_Button.addActionListener(deal_click_mouseEntered);
    }
}
class Deal_click implements ActionListener {
    ColorFrame sourceFrame;



    public void setSourceFrame(ColorFrame sourceFrame) {
        this.sourceFrame = sourceFrame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Container contentPane = sourceFrame.getContentPane();
        if(sourceFrame == null){
            return;
        }
        if(e.getActionCommand().equals("Red") ){
            contentPane.setBackground(Color.RED);
            sourceFrame.label.setText("这是红色");
        }
        if(e.getSource() == sourceFrame.green_Button){
            contentPane.setBackground(Color.GREEN);
            sourceFrame.label.setText("这是绿色");
        }
        if(e.getSource() == sourceFrame.blue_Button){
            contentPane.setBackground(Color.BLUE);
            sourceFrame.label.setText("这是蓝色");
        }
    }
}

