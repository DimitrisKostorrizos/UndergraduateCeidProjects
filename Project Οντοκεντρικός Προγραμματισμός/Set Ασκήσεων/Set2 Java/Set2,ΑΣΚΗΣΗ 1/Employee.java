public abstract class Employee
{
    private String name;
    private String afm;
    private  Long EmpID=0L;
    private static Long objectcounter=0L;
    
    Employee()
    {
       objectcounter++;
       EmpID=objectcounter;
    }
    Employee(String name,String afm)
    {
        this.name=name;
        this.afm=afm;
        this.EmpID=EmpID;
        objectcounter++;
        EmpID=objectcounter;
    }
    
    public void setName(String n)
    {
        name=n;
    }
    public String getName()
    {
        return name;
    }
    public void setAfm(String a)
    {
        afm=a;
    }
    public String getAfm()
    {
        return afm;
    }
    public long getEmpID()
    {
        return EmpID;
    }
    public abstract int payment();
}
