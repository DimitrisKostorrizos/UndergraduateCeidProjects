public class Window
{
protected int size;
public Window()
{
size=1;
System.out.println("Window size="+size);
}
public Window(int size)
{
this.size=size;
System.out.println("Window size="+size);
}
public void setSize(int x)
{size += x;}
public void printSize()
{System.out.println("Size=" + size);}
}