public class HourlyEmployee extends Employee
{
    private int hoursWorked=0;
    private int hourlyPayment=0;
    
    HourlyEmployee()
    {
        super();
    }
    HourlyEmployee(String name,String afm,int hoursWorked,int hourlyPayment)
    {
        super(name,afm);
        this.hoursWorked=hoursWorked;
        this.hourlyPayment=hourlyPayment;
    }
    public void setHoursWorked(int hw)
    {
        hoursWorked=hw;
    }
    public int getHoursWorked()
    {
        return hoursWorked;
    }
    public void setHourlyPayment(int hp)
    {
        hourlyPayment=hp;
    }
    public int getHourlyPayment()
    {
        return hourlyPayment;
    }
    public int payment()
    {
        return hoursWorked*hourlyPayment;
    }
}