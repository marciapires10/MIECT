import java.util.Scanner;

public class ex6
{
	public static Scanner sc = new Scanner (System.in);
	public static void main (String[] args)
	{
		System.out.println("Guess the number!");
		System.out.println("The computer is choosing a number 
				    between 0-100...");
		int n;
		n=(int)(Math.random()*(100+1));
		System.out.println("Done!");
		int x, cont=0;
		do
		{	
			System.out.print("Guess: ");
			x = sc.nextInt();
			if (x>n)
			    System.out.println("The correct number is lower!");
			else if (x<n)
				 System.out.println("The correct number 
						     is higher!");
			cont++;		
		}while (x!=n);
		System.out.printf("Congratulations! You got the number right. 
				   You got %d points (lower is better).: ", 
				   cont);
	}
}
