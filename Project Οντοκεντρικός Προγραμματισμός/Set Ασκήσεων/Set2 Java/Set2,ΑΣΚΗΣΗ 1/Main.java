import java.util.*;
public class Main
{
   public static void main(String args[])
   {
       ArrayList<Employee> eList = new ArrayList<Employee>();
       SalariedEmployee se1 = new SalariedEmployee();
       HourlyEmployee he1 = new HourlyEmployee();
       eList.add(se1);
       eList.add(he1);
       se1.setName("Tzortzis");
       se1.setAfm("72340002");
       se1.setSalary(3000);
       he1.setName("Zina");
       he1.setAfm("8145821");
       he1.setHoursWorked(210);
       he1.setHourlyPayment(20);
       for(int counter=0;counter<eList.size();counter++)
       {
          System.out.println("Employee ID: " + eList.get(counter).getEmpID());
          System.out.println("Employee Name: " + eList.get(counter).getName());
          System.out.println("Employee AFM: " + eList.get(counter).getAfm());
          System.out.println("Employee Payment: " + eList.get(counter).payment() + "\n");
          
       }
   }
}