package lab.lab05.p1;

/*
 TODO:假定要为某个公司编写雇员工资支付程序。

     这个公司有各种类型的雇员，不同类型的雇员按不同的方式支付工资：
     经理每月获得一份固定工资；
     销售人员在基本工资的基础上每月还有销售额提成（10%）；
     一般工人则按它每月工作的天数计算工资。
     （抽象类的使用）
     再设计一个接口Add用于涨工资，销售人员基本工资一次能涨10%，一般工人日工资一次能涨10%，经理一次涨20%。

     还要设置一个日结工资的不用于涨工资的临时员工类



输出结果为：

涨工资前各雇员的工资：
kkk's salary is :8900.0
sss's salary is :7500.0
eee's salary is :6000.0
ttt's salary is :5000.0
涨工资后各雇员的工资：
kkk's salary is :10680.0
sss's salary is :7900.0
eee's salary is :6600.0
ttt's salary is :5000.0
 */
class App {

    public static void main(String[] args) {

        employee[] emp = { new manager("kkk", 8900), new saleMan("sss", 4000, 35000), new Worker("eee", 20, 300) , new TempWorker("ttt",25,200)};

        System.out.println("涨工资前各雇员的工资：");

        for (int i = 0; i < emp.length; i++)

        {

            System.out.println(emp[i].getName() + "'s salary is :" + emp[i].computeSalary());

        }

        for (int i = 0; i < emp.length; i++) {
            emp[i].addSalary();
        }

        System.out.println("涨工资后各雇员的工资：");

        for (int i = 0; i < emp.length; i++)

        {
            System.out.println(emp[i].getName() + "'s salary is :" + emp[i].computeSalary());

        }

    }
}

public interface Add {
    void addSalary();
}

abstract class employee implements Add {
    protected String id;
    protected double base_salary;

    String getName() {
        return id;
    }

    abstract double computeSalary();

}

class manager extends employee {
    manager(String id_in, double manager_baseSalary_in) {
        id = id_in;
        base_salary = manager_baseSalary_in;
    }

    @Override
    public void addSalary() {
        base_salary *= 1.2;

    }

    @Override
    double computeSalary() {
        return base_salary;
    }

}

class saleMan extends employee {
    double sale_money;

    saleMan(String id_in, double saleMan_baseSalary_in, double sale_money_in) {
        id = id_in;
        base_salary = saleMan_baseSalary_in;
        sale_money = sale_money_in;
    }

    @Override
    public void addSalary() {
        base_salary *= 1.1;
    }

    @Override
    double computeSalary() {
        return base_salary + (sale_money * 0.1);
    }
}

class Worker extends employee {
    private int work_day;

    Worker(String id_in, int work_day_in, double worker_daySalary_in) {
        id = id_in;
        work_day = work_day_in;
        base_salary = worker_daySalary_in;
    }

    @Override
    public void addSalary() {
        base_salary *= 1.1;
    }

    @Override
    double computeSalary() {
        return work_day * base_salary;
    }
}

class TempWorker extends employee {
    private int work_day;

    TempWorker(String id_in, int work_day_in, double worker_daySalary_in) {
        id = id_in;
        work_day = work_day_in;
        base_salary = worker_daySalary_in;
    }

    @Override
    public void addSalary() {
    }

    @Override
    double computeSalary() {
        return work_day * base_salary;
    }
}
