package lab06.$1_login;

import java.awt.*;
import java.awt.event.*;


class Main {
    public static void main(String[] args) {
        new UserFrame();
        UserFrame_ex uf = new UserFrame_ex();
        Deal deal = new Deal();
        uf.setDeal(deal);
        deal.setService(uf);
    }
}

class UserFrame extends Frame implements ActionListener, WindowListener {
    TextField t_user, t_ps;
    Button b_ok, b_exit;
    Label tl;

    public UserFrame() {
        this.setTitle("一般实现方法");
        setSize(400, 100);
        setLocation(400, 200);
        this.setBackground(Color.lightGray);
        this.setLayout(new FlowLayout());
        this.add(new Label("用户名"));          //改中文标签一开始乱码了，解决过程还挺有意思的，学到了很多新东西，我会写在实验报告里的
        t_user = new TextField("unknow");
        this.add(t_user);
        this.add(new Label("密码"));
        t_ps = new TextField(5);
        this.add(t_ps);

        b_ok = new Button("OK");
        b_exit = new Button("EXIT");
        this.add(b_ok);
        this.add(b_exit);
        tl = new Label("   ");
        this.add(tl);
        b_exit.addActionListener(this);
        b_ok.addActionListener(this);
        this.addWindowListener(this);
        this.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == this.b_exit) {
            System.exit(0);
        }
        if (e.getActionCommand() == "OK") {
            if (this.t_user.getText().equals("abc") && (this.t_ps.getText().equals("1234")))
                this.tl.setText("welcome,abc!");
            else
                this.tl.setText("username or password is wrong!");
            this.setVisible(true);
        }
    }

    public void windowOpened(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }
}

class UserFrame_ex extends Frame {
    TextField t_user, t_ps;
    Button b_ok, b_exit;
    Label tl;
    Deal deal;

    void setDeal(Deal deal) {
        this.deal = deal;
        b_ok.addActionListener(this.deal);
        b_exit.addActionListener(this.deal);
        this.addWindowListener(this.deal);
    }

    public UserFrame_ex() {
        this.setTitle("分离实现方法");
        setSize(400, 100);
        setLocation(1000, 200);
        this.setBackground(Color.lightGray);
        this.setLayout(new FlowLayout());
        this.add(new Label("用户名"));
        t_user = new TextField("unknow");
        this.add(t_user);
        this.add(new Label("密码"));
        t_ps = new TextField(5);
        this.add(t_ps);

        b_ok = new Button("OK");
        b_exit = new Button("EXIT");
        this.add(b_ok);
        this.add(b_exit);
        tl = new Label("   ");
        this.add(tl);
        this.setVisible(true);
    }
}

class Deal implements ActionListener, WindowListener {
    UserFrame_ex uf;

    void setService(UserFrame_ex uf) {
        this.uf = uf;
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == uf.b_exit) {
            System.exit(0);
        }
        if (e.getActionCommand() == "OK") {
            if (uf.t_user.getText().equals("abc") && (uf.t_ps.getText().equals("1234")))
                uf.tl.setText("welcome,abc!");
            else
                uf.tl.setText("username or password is wrong!");
            uf.setVisible(true);
        }
    }

    public void windowOpened(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }
}


