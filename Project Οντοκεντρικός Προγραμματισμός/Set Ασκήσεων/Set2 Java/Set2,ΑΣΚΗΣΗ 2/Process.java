import java.io.*;
public class Process
{
static float fxyz;
public static void main(String args[])
{
    try{
    InputStreamReader stdin = new InputStreamReader(System.in);
        BufferedReader console = new BufferedReader(stdin);
        int x,y,z;
        String str1, str2, str3;
    
            System.out.println("Enter the first integer.");
            str1 = console.readLine();
            x = Integer.parseInt(str1);
            System.out.println("Enter the second integer.");
            str2 = console.readLine();
            y = Integer.parseInt(str2);
            System.out.println("Enter the third integer.");
            str3 = console.readLine();
            z = Integer.parseInt(str3);
            fxyz=(3*(x-1)*y)/(x-2*z);
        } catch(IOException ioe){
        {
            System.out.println("Input error.Exception: " + ioe.toString());
            System.exit(0);
        }
        }catch(NumberFormatException nfe){
        {
            System.out.println("Different number format than integer.Exception: " + nfe.toString());
            System.exit(0);
        }
        }catch (ArithmeticException ae)
        {
            System.out.println("The denominator cannot be 0.Exception: "+ae.toString());
            System.exit(0);
        }
        finally
        {
            System.out.println("f(x,y,z)=(3*(x-1)*y)/(x-2*z)=" + fxyz);
        }
}
}