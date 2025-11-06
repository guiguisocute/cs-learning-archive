package Quickverify.p1;

import java.util.Scanner;

//异常处理比static约束限制实例的新建的优势的实践
public class Student {
    static int AGE_UPPER_BOUND = 150;
    static int AGE_LOWER_BOUND = 0;
    private String name;
    private int age;
    private int grade;

    void Set_name(String name){
        this.name = name;
    }

    void Set_age_range(int age){
        try{
            if(age < 0 || age > 150){
                throw new Exception("Invalid age");
            }
        } catch (Exception e){
            System.out.println(e.getMessage());
            return;
        }
        this.age = age;
    }

    void Set_grade(int grade){
        try{
            if(grade < 0 || grade > 100){
                throw new StudentScoreException("Invalid grade");
            }
        } catch (Exception e){
            System.out.println(e.getMessage());
            return;
        }
        this.grade = grade;
    }

    private Student(String name, int age, int grade){
        this.name = name;
        this.age = age;
        this.grade = grade;
    }

    public static Student Create_student(String name, int age, int grade){
        try{
            if(age < AGE_LOWER_BOUND || age > AGE_UPPER_BOUND){
                throw new StudentAgeException("Invalid age");
            }
        } catch (Exception e){
            System.out.println(e.getMessage());
            return null;
        }
        Student student = new Student(name, age, grade);
        return student;
    }

    
}

class StudentScoreException extends Exception {
    public StudentScoreException(String message){
        super(message);
    }
}

class StudentAgeException extends Exception {
    public StudentAgeException(String message){
        super(message);
    }
}


class Test{
    public static void main(String[] args) {
        System.out.println("Please set student information:");
        Scanner scanner = new Scanner(System.in);
        
        
        System.out.print("Name: ");
        String name = scanner.nextLine();

        System.out.print("Age: ");
        int age = scanner.nextInt();

        System.out.print("Grade: ");
        int grade = scanner.nextInt();

        Student student = Student.Create_student(name, age, grade);
        if(student != null){
            System.out.println("Student created successfully");
        }
    }
}
