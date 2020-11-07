public class DivideByZeroException extends ArithmeticException 
{
public DivideByZeroException() {}
public DivideByZeroException(String msg) {super(msg);}
public String toString() 
{
return "DivideByZeroException: The denominator cannot be zero.";
}
}
