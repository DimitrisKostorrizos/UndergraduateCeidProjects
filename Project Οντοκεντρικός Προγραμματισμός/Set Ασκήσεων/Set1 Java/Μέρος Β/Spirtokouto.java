public class Spirtokouto extends Box
{
// Instance Variables
private double weight;
// Constructors    
public Spirtokouto (double length, double width, double height,double weight)
{
super(length,width,height);
this.weight=weight;
}
// Methods   
public String toString()
{
return "MatchBox Calculation " + calculate() + ", Volume " + volume() + ", Weight " + weight;
}
}