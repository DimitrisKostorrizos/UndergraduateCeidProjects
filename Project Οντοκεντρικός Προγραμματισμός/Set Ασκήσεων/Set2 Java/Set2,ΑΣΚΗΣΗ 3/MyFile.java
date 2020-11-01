import java.io.*;
import java.util.*;
public class MyFile
{
    static String sin="src.txt";
    static String sout="output.txt";
    public static void main(String args[])
    {
        FileReader inputStream = null;
        FileWriter outputStream = null;
        int spaceCounter=0;
        try {
            inputStream = new FileReader(sin);
            outputStream = new FileWriter(sout);
            System.out.println("The size in bytes for file "+ sin + " before opening is: " + new File(sin).length());
            System.out.println("The size in bytes for file "+ sout + " before opening is: " + new File(sout).length());
            
            }catch (FileNotFoundException fnfe){
             {
                 System.err.println("Exception:"+fnfe.toString());
                 System.exit(0);
             }
             }catch (IOException ioe1 ){
             {
                 System.err.println("Exception:"+ioe1.toString());
             }
            }
            int c; 
            try{
            while ((c = inputStream.read()) != -1) 
            {
                if (c == ' ') 
                {
                    spaceCounter++;
                    c='@';
                }
                else if (c == '\n')
                {
                    outputStream.write('\n');
                }
                outputStream.write(c);
            }
            }catch (IOException ioe2 ){
             {
                 System.err.println("Exception:"+ioe2.toString());
             }
        } finally 
        {
            try {
            if (inputStream != null) {
                inputStream.close();
                 }
                }catch (IOException ioe3 ){
             {
                 System.err.println("Exception:"+ioe3.toString());
             }
            }
            try{
            if (outputStream != null) {
                outputStream.close();
            }
            }catch (IOException ioe4 ){
             {
                 System.err.println("Exception:"+ioe4.toString());
             }
            }
             }
             System.out.println("The size in bytes for file "+ sin + " after closing is: " + new File(sin).length());
             System.out.println("The size in bytes for file "+ sout + " after closing is: " + new File(sout).length());
             System.out.println("The number of spaces that changed to @ is: "+ spaceCounter);
        }
    }   