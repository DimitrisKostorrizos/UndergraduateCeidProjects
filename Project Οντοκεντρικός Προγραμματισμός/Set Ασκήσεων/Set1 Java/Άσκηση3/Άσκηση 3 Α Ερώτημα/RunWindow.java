class Window
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
class MWindow extends Window
{
private String message = "No message";
protected int size = 7;
public MWindow(String message)
{
size = 2;
this.message = message;
System.out.println ("Window message = " + message);
}
public MWindow(int size, String message)
{
super(size);
this.message = message;
System.out.println ("Window message = " + message);
}
public void setSize1(int y)
{size = y;}
public void setSize2(int z)
{super.setSize (z);}
public void printSize()
{System.out.println ("MSize="+size);}
public void printSize1()
{System.out.println(((Window)this).size);}
public void printSize2()
{((Window)this).printSize();}
}
public class RunWindow
{
public static void main (String args[])
{
Window w1=new Window();
Window w2=new Window(2);
System.out.println(w1.size);
System.out.println(w2.size);
MWindow mw1=new MWindow("First MWindow");
MWindow mw2=new MWindow(3, "Second MWindow");
System.out.println(mw1.size);
System.out.println(mw2.size);
mw1.setSize1(4);
System.out.println(mw1.size);
mw1.setSize2(2);
System.out.println(mw1.size);
mw1.setSize(2);
System.out.println(mw1.size);
w1.printSize();
mw1.printSize();
mw1.printSize1();
mw1.printSize2();
}
}