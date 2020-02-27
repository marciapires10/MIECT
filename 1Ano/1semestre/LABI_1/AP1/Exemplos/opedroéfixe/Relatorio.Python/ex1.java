import java.util.Scanner;
import java.lang.Object;

public class ex1 {
	
	public static void main (String args[]) {
		Scanner faug = new Scanner(System.in);
		String conta = new String();
		System.out.println();
		System.out.print("Input:");
		conta = faug.nextLine();
		String[] parts = conta.split(" ");
		char op = parts[1].charAt(0);
		switch(op) {
case '+': System.out.printf("%s = %.2f\n", conta, 
	  Double.parseDouble(parts[0]) + 
	  Double.parseDouble(parts[2])); 
	  break;
case '-': System.out.printf("%s = %.2f\n", conta, 
	  Double.parseDouble(parts[0]) - 
	  Double.parseDouble(parts[2])); 
	  break;
case '*': System.out.printf("%s = %.2f\n", conta, 
	  Double.parseDouble(parts[0]) * 
	  Double.parseDouble(parts[2])); 
	  break;
case '/': System.out.printf("%s = %.2f\n", conta, 
	  Double.parseDouble(parts[0]) / 
	  Double.parseDouble(parts[2])); 
	  break;
default: System.out.println("Invalid input!");
		}
	}
}

