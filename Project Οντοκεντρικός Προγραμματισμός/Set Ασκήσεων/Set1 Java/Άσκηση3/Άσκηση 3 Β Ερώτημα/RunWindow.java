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