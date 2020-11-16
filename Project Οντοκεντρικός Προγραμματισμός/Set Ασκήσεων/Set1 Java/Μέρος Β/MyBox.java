 public class MyBox extends Box
{    
// Constructors
public MyBox (double length, double width, double height)
{
super(length, width, height);    
int equal1=Double.compare(length,width);
int equal2=Double.compare(length,height);    
if(equal1==0 && equal2==0)
{
System.out.println("The cube was created successfully.");
}
else
{
System.out.println("Error,invalid dimensions.The cube wasn't created successfully");
}
}
// Methods
public double calculate(double length)
{
return 6 * (length*length) ;
}
public double volume(double length)
{
return length*length*length;
}    
public String toString()
{
return "Cube Calculation " + calculate() + ", Volume " + volume();
}
}