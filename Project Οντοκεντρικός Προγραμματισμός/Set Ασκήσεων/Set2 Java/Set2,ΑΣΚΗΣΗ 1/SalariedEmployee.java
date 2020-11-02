public class SalariedEmployee extends Employee
{
    private int salary=0;
    SalariedEmployee()
    {
        super();
    }
    SalariedEmployee(String name,String afm,int salary)
    {
        super(name,afm);
        this.salary=salary;
    }
    public void setSalary(int s)
    {
        salary=s;
    }
    public int payment()
    {
        return salary;
    }
}
