import java.util.Scanner;
public class ex5
{
	public static Scanner sc = new Scanner (System.in);
	public static void main (String[] args)
	{
		double n, x=0, c=0;
		do{
			System.out.println("Input(0 to stop): ");
			n=sc.nextDouble();
			if (n!=0)
			{	
				x=x+n;
				c++;
			}
			else break;
		}while(n!=0);
		double m;
		if (c!=0)
		{
			m=x/c;
			System.out.printf("The sum of the values is %.1f and the average is %.1f\n", x, c);
		}
		else
			System.out.print("The sum is 0 and is not possible to determine the average.");
	}
}
