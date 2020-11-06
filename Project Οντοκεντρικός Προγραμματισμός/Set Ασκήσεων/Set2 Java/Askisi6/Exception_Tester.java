public class Exception_Tester 
{
public static void main(String args[]) 
{
Exception_Tester et = new Exception_Tester();
int x1;
int x2;
x1 = 5;
x2 = 0;
try{
et.printResults(x1, x2);
}
catch (DivideByZeroException dbz) 
{
System.out.println(dbz.toString());
dbz.printStackTrace();
}
finally 
{
System.out.println("The numbers are: "+x1+" "+x2);
}
}
void printResults(int a, int b) throws DivideByZeroException
{
System.out.println("Add: "+(a+b));
System.out.println("Sub: "+(a-b));
System.out.println("Mul: "+(a*b));
try {
System.out.println("Div: "+(a/b));
}
catch (ArithmeticException ae) {
throw new DivideByZeroException(ae.toString());
}
}
}
