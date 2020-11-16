public class Box
{
// Instance Variables
private double length ;
private double width ;
private double height ;
// Constructors
public Box ( double side )
{
width = side ;
height = side ;
length = side ;
}
public Box (double length, double width, double height)
{
this.length=length;
this.width=width;
this.height=height;
}
// Methods
public double calculate()
{
return 2 * ( width * height + width * length + height * length ) ;
}
public double volume()
{
return (length*width*height);
} 
public String toString()
{
return "Calculation " + calculate() + ", Volume " + volume();
}
}