public class Person 
{
private String lastname;
private String firstname;
private int age;
private boolean married;
private float salary;
public static final int MALE = 0;
public static final int FEMALE = 1;
private int sex;

public Person (String lastname, String firstname, int age, boolean married,
float salary, int sex)
{
this.lastname = new String(lastname);
this.firstname = new String(firstname);
this.age = age;
this.married = married;
this.salary = salary;
this.sex = sex;
}

public String getLastName() 
{ 
    return lastname;
}
public String getFirstName() 
{ 
    return firstname; 
}
public int getAge() 
{ 
    return age; 
}
public boolean isMarried() 
{ 
    return married; 
}
public float getSalary() 
{
    return salary; 
}
public int getSex()
{
    return sex;
}

public void setLastName(String lastname) 
{ 
    this.lastname=lastname;
}
public void setFirstName(String firstname) 
{ 
    this.firstname=firstname;
}
public void setAge(int age) 
{ 
    this.age=age; 
}
public void setMarried(boolean married) 
{ 
    this.married=married; 
}
public void setSalary(float salary) 
{
    this.salary=salary; 
}
public void setSex(int sex)
{
    this.sex=sex;
}
public void printInfo()
{
if(getSex()==1)
{
System.out.print(getFirstName()+" "+getLastName()+" is "
+getAge()+" years old and female, gets a "+getSalary()
+" Euros salary and is");
}
if(getSex()==0)
{
System.out.print(getFirstName()+" "+getLastName()+" is "
+getAge()+" years old and male, gets a "+getSalary()
+" Euros salary and is");
}
if (isMarried() == false)
{
System.out.println(" not married.");
}
else
{
System.out.println( " married,");    
}
}
}