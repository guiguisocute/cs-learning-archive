package lab06.$3_calculate;
/*
TODO:做一个简单的计算器，[1][+][2]【=】 3
    其中[]表示文本框，【=】表示按钮，点击按钮后计算出结果。
    3 是文本框（enable(false)）[个人认为这个不怎么好用，不如] 要求：
    （1）当产生除零错、数据格式不正确时，借助标签显示出错信息；
    （2）自定义异常类 NullTextFieldException，当第一个文本框为空或第二个文本框为空时抛出此异常，并借助标签显示出错信息
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;    //这次想用swing去做一下看看有什么不同,毕竟swing开发出来就是为了替换awt的，老掉牙的东西还是少用



public class Main {
    public static void main(String[] args) {
        new CalculatorFrame();
    }
}

class CalculatorFrame extends JFrame {

    JTextField num1Field, num2Field, resultField;
    JComboBox<String> operatorBox; // 利用一下swing的下拉框，雀食直观好看一点
    JButton calcButton;
    JLabel errorLabel;

    public CalculatorFrame() {
        super("简易计算器,仅能保留两位小数的浮点数结果，精度有限，不要盲信");
        initUI();
        initListener();
    }

    private void initUI() {
        this.setLayout(new BorderLayout());
        this.setSize(400, 100);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Swing特有的方便关闭方式

        JPanel inputPanel = new JPanel(new FlowLayout());
        num1Field = new JTextField(5);
        num2Field = new JTextField(5);

        resultField = new JTextField(10);
        resultField.setEditable(false);
//      resultField.setEnabled(false);

        String[] ops = { "+", "-", "×", "÷" };
        operatorBox = new JComboBox<>(ops);
        calcButton = new JButton(" = ");

        inputPanel.add(num1Field);
        inputPanel.add(operatorBox);
        inputPanel.add(num2Field);
        inputPanel.add(calcButton);
        inputPanel.add(resultField);
        

        JPanel errorPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        errorLabel = new JLabel(" ");
        errorLabel.setForeground(Color.RED);
        JLabel tipTitle = new JLabel("错误提示: ");     // 你看用swing的Label就不用去考虑编码问题了，伟大无需多言！
        errorPanel.add(tipTitle);
        errorPanel.add(errorLabel);

        this.add(inputPanel, BorderLayout.CENTER);
        this.add(errorPanel, BorderLayout.SOUTH);
        this.setVisible(true);
    }

    private void initListener() {
        calcButton.addActionListener(new ActionListener() {         //是定义了一个实现了AL接口的匿名类，并且通过new实例化该匿名类，然后转型为AL，不过好像Java8对于这种只有一个方法的接口（函数式接口）可以用Lambda表达式"->"，指针味好浓哦，学到了一点
//现在终于体会到匿名类的意义了……调框架确实很刚需啊
            @Override
            public void actionPerformed(ActionEvent e) {
                errorLabel.setText("");
                resultField.setText("");

                try {
                    String str1 = num1Field.getText().trim();
                    String str2 = num2Field.getText().trim();
                    String op = (String) operatorBox.getSelectedItem();  //这个函数返回值是Object啊，还好有文档看，差点卡死我了

                    if (str1.isEmpty() || str2.isEmpty()) {
                        throw new NullTextFieldException("输入框不能为空！");
                    }

                    double n1 = Double.parseDouble(str1);
                    double n2 = Double.parseDouble(str2);
                    double result = 0;

                    // 4. 计算逻辑
                    switch (op) {
                        case "+":
                            result = n1 + n2;
                            break;
                        case "-":
                            result = n1 - n2;
                            break;
                        case "×":
                            result = n1 * n2;
                            break;
                        case "÷":
                            if (Math.abs(n2) < 1e-6) { // 浮点数判0的方法，总之不能直接用 n2 == 0，而且也不能不抛，浮点数除0不会直接捕获ArithmeticException的
                                throw new ArithmeticException("除数不能为0");
                            }
                            result = n1 / n2;
                            break;
                    }
                String formattedResult = String.format("%.2f", result);
                resultField.setText(formattedResult);
                errorLabel.setForeground(Color.GREEN);
                errorLabel.setText("还好，一切如愿以偿");

                } catch (NullTextFieldException ex) {
                    errorLabel.setText(ex.getMessage());
                } catch (NumberFormatException ex) {
                    errorLabel.setText("格式错误: 请输入有效的数字");
                } catch (ArithmeticException ex) {
                    errorLabel.setText("算术错误: " + ex.getMessage());
                //简单兜个底
                } catch (Exception ex) {
                    errorLabel.setText("未知错误: " + ex.toString());
                }
            }
        });
    }
}


class NullTextFieldException extends Exception {
    public NullTextFieldException(String message) {
        super(message);
    }
}

