public class Age
{
public static void main(String args[])
{
if (args.length == 2 && args[0] == "-")
{
System.out.println("You are " + args[1] + " years old.");
}
else if (args.length == 1)
{
System.out.println("You forgot to give your age.");
}
else
{
System.out.println(args[0] + " is " + args[1] + " years old.");
}
}
}
