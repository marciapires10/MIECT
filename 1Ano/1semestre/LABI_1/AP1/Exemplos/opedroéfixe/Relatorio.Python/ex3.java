import java.util.Scanner;

public class ex3 {
	
	public static void main (String args[]) {
		Scanner faug = new Scanner(System.in);
		System.out.print("Input: ");
		int n = faug.nextInt();
		boolean primo = true;
		for(int i=2; i<=n/2; i++) {
			if (n%i == 0) {
				primo = false;
			}
		}
		if(primo == true) {
			System.out.println("The number is prime.");
		}
		else {
			System.out.println("The number is not prime.");
		}
	}
}
