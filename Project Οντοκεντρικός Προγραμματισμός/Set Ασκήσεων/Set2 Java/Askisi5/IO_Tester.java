import java.io.*;

public class IO_Tester
{
public static int readInt()
{
byte b[] = new byte[16];
String str;
try {
System.in.read(b);
str = (new String(b)).trim();
return Integer.parseInt(str);
} catch (IOException e) 
{
System.out.println("Exception: " + e.toString());
return 0;
} catch (NumberFormatException e) {
System.out.println("Exception: " + e.toString() + "\nReturned value: -1");
return -1;
}
}
public static float readFloat() {
byte b[] = new byte[16];
String str;
try {
System.in.read(b);
str = (new String(b)).trim();
return Float.parseFloat(str);
} catch (IOException e) 
{
System.out.println("Exception: " + e.toString());
return 0;
} catch (NumberFormatException e)
{
    System.out.println("Exception: " +e.toString() + "\nReturned Value: -1.0");
    return -1;
}
}
public static String readString() {
byte b[] = new byte[32];
String str;
try {
System.in.read(b);
str = (new String(b)).trim();
return str;
} catch (IOException e) {
System.out.println("Exception: " + e.toString());
return "";
}
}
public static boolean readBoolean() {
byte b[] = new byte[16];
String str;
try {
System.in.read(b);
str = (new String(b)).trim();
Boolean bool = new Boolean(str);
return bool.booleanValue();
} catch (IOException e) {
System.out.println("Exception: " + e.toString());
return false;
}
}
public static void main(String args[])
{
System.out.println("Dwste enan akeraio:");
int i = readInt();
System.out.println("Dwste enan float:");
float f = readFloat();
System.out.println("Dwste ena string:");
String s = readString();
System.out.println("Dwste mia boolean:");
boolean b = readBoolean();
System.out.println("i="+i+"\tf="+f+"\ts="+s+"\tb="+b);
try {
FileOutputStream fil = new FileOutputStream(s);
BufferedOutputStream buf = new BufferedOutputStream(fil);
DataOutputStream dat = new DataOutputStream(buf);
dat.writeInt(i);
dat.writeFloat(f);
dat.writeBoolean(b);
dat.close();
} catch (FileNotFoundException e) {}
catch (IOException e) {}
try {
FileInputStream fil = new FileInputStream(s);
BufferedInputStream buf = new BufferedInputStream(fil);
DataInputStream dat = new DataInputStream(buf);
i+=dat.readInt();
f*=dat.readFloat();
b=!dat.readBoolean();
dat.close();
} catch (FileNotFoundException e) {}
catch (IOException e) {}
System.out.println("i="+i+"\tf="+f+"\ts="+s+"\tb="+b);
try {
FileWriter fw = new FileWriter(s);
BufferedWriter bw = new BufferedWriter(fw);
bw.write(Integer.toString(i), 0, Integer.toString(i).length());
bw.write(Float.toString(f), 0, Float.toString(f).length());
bw.write(s.concat(s), 0, s.concat(s).length());
bw.write(Boolean.toString(b), 0, Boolean.toString(b).length());
bw.close();
} catch(IOException e) { System.out.println(e.toString()); }
}
}