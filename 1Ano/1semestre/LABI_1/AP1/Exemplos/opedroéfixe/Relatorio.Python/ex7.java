import java.util.Scanner;
import java.io.*;
public class ex7{

	public static Scanner kb = new Scanner(System.in);
	public static void main (String args []) throws IOException{
		File fin = new File(args[0]);
		File fout = new File(args[1]);
		

		if (!fin.exists())
		{
			System.out.println("ERROR: input file does not exist!");
			System.exit(1);
		}
		if (fin.isDirectory())
		{
			System.out.println("ERROR: input file is a directory!");
			System.exit(2);
		}
		if (!fin.canRead())
		{
			System.out.println("ERROR: cannot read from input file!");
			System.exit(3);
		}
		

		String resp=new String();
		while(true) {
			if (fout.exists())
			{
			   System.out.println("The file "+args[1]+" 
					      already exists. Would you like to 
					      overwrite it? (y/n)");
				resp=kb.nextLine();
				char r=resp.charAt(0);
				if (r=='n' || r=='N')
				{
					System.out.println("Bye!");
					System.exit(1);
				}
				if (r =='y' || r=='Y') {
					break;
				}
			}
		}
			
		Scanner sc = new Scanner(fin);
		PrintWriter pw = new PrintWriter(fout);
		
		if (!fout.canWrite())
		{
			System.out.println("ERROR: cannot write in the output 
					   file!");
			System.exit(4);
		}
		
		

		while (sc.hasNext())
		{
			String a = sc.nextLine();
			pw.println(a);
		}
		pw.close();
		sc.close();
		System.out.println("Copy completed!");
	}
}
