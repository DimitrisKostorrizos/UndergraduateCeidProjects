public class MarriedPerson extends Person 
{
private int children;

public MarriedPerson(String lastname, String firstname, int age, float
salary, int sex, int children) 
{
super(lastname, firstname, age, true, salary, sex);
this.children = children;
}

public int getNoOfChildren() 
{ 
    return children; 
}

public void setMarried(boolean married) 
{ 
    super.setMarried(true); 
}
public void setSalary(MarriedPerson spouse)
{
    if (spouse.getSex()!=getSex())
    {
        super.setSalary(getSalary()+spouse.getSalary());
    }
}  
public void setNoOfClilderen(int children)
{
    this.children=children;
}
public void printInfo()
{
    super.printInfo();
    System.out.println("with "+getNoOfChildren() + " children.");
}
}
