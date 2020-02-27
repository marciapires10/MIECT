import java.util.Scanner;
import java.io.*;

public class ex4
{
	public static Scanner sc = new Scanner (System.in);
	public static void main (String []args) throws IOException
	{
		String f = new String();
		System.out.print("File name: ");
		f=sc.nextLine();
		File fin = new File(f);
		Scanner kb = new Scanner(fin);
		while (kb.hasNextLine())
		{
			String t = new String();
			t=kb.nextLine();
			if (t.length()!=0)
			{	
				for(int i = 0 ; i < t.length() ; i++){
					char c = t.charAt(i);
					if(c == 'r' || c == 'R')
					{
						System.out.print("");
					}
					else if(c == 'l')
					{
						System.out.print("u");
					}
					else if(c == 'L')
					{
						System.out.print("U");
					}
					else
					{
						System.out.print(c);
					}
				}
			}else System.exit(1);
			System.out.println("");
		}
		kb.close();
	}
}
