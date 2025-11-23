package lab06.$2_lightControl;

import java.awt.*;
import java.awt.event.*;

//TODO:要求用两种方法实现：1.一般方法;2.内部类的方法
//很想问内部类的意义是？既然都解耦了为什么还要耦合回去，感觉怪怪的


class Main {
    public static void main(String[] args) {
        Lamp lp = new Lamp();
        Deal d = new Deal();
        lp.setDeal(d);
        d.setService(lp);
        new Lamp_inner();

    }
}

class Lamp extends Frame  {
    Label lb1,lb2;
    Button b_open,b_close;
    Deal d;
    public void setDeal(Deal d1){
        this.d=d1;
        b_close.addActionListener(d);
        b_open.addActionListener(d);
        this.addWindowListener(d);
    }
    public Lamp(){
        this.setSize(300,100);
        this.setLocation(300,300);
        this.setLayout(new FlowLayout());
        this.setTitle("一般方法");
        Font f=new Font("宋体",Font.PLAIN,16);
        lb1=new Label("灯状态:");
        lb1.setFont(f);
        this.add(lb1);
        lb2=new Label("    ");
        lb2.setBackground(Color.black);
        this.add(lb2);
        b_open=new Button("open");
        this.add(b_open);
        b_close=new Button("close");
        b_close.setEnabled(false);
        this.add(b_close);

        this.setVisible(true);
    }
}
class Deal implements ActionListener,WindowListener{
    Lamp lp;
    public  void setService(Lamp lp)
    { this.lp=lp;     }
    public void windowOpened(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {System.exit(0); }
    public void windowClosed(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void actionPerformed(ActionEvent e){
        if(e.getSource()== lp.b_open){
            lp.lb2.setBackground(Color.red);
            lp.b_open.setEnabled(false);
            lp.b_close.setEnabled(true);
        }
        if(e.getSource()== lp.b_close){
            lp.lb2.setBackground(Color.black);
            lp.b_close.setEnabled(false);
            lp.b_open.setEnabled(true);
        }
    }
}


class Lamp_inner extends Frame{
    private Label lb1, lb2;
    private Button b_open, b_close;
    private Font f;
    public Lamp_inner() {
        this.setSize(300, 100);
        this.setLocation(800, 300);
        this.setLayout(new FlowLayout());
        this.setTitle("内部类方法");
        Font f = new Font("宋体", Font.PLAIN, 16);
        lb1 = new Label("灯状态:");
        lb1.setFont(f);
        this.add(lb1);

        lb2 = new Label("    ");
        lb2.setBackground(Color.black);
        this.add(lb2);

        b_open = new Button("open");
        this.add(b_open);

        b_close = new Button("close");
        b_close.setEnabled(false);
        this.add(b_close);

        this.setVisible(true);


        Deal_inner dealInner = new Deal_inner();
        b_open.addActionListener(dealInner);
        b_close.addActionListener(dealInner);
        this.addWindowListener(dealInner);
    }

    class Deal_inner implements ActionListener, WindowListener {
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == b_open) {
                lb2.setBackground(Color.red);
                b_open.setEnabled(false);
                b_close.setEnabled(true);
            }
            if (e.getSource() == b_close) {
                lb2.setBackground(Color.black);
                b_close.setEnabled(false);
                b_open.setEnabled(true);
            }
        }

        public void windowOpened(WindowEvent e) {}
        public void windowClosing(WindowEvent e) { System.exit(0); }
        public void windowClosed(WindowEvent e) {}
        public void windowIconified(WindowEvent e) {}
        public void windowDeiconified(WindowEvent e) {}
        public void windowActivated(WindowEvent e) {}
        public void windowDeactivated(WindowEvent e) {}
    }
    

}