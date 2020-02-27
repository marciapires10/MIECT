import java.util.Scanner;

public class ex2{

	public static Scanner sc = new Scanner(System.in);
	public static void main (String args []){
		double aitp1, aip, aitp2, apf;
		while(true) {
			System.out.print("AITP1: ");
			aitp1=sc.nextDouble();
			if (aitp1<0 || aitp1>20){
				System.out.println("Invalid!");
				continue;
			}
			break;
		}
		while(true) {
			System.out.print("AIP: ");
			aip=sc.nextDouble();
			if (aip<0 || aip>20){
				System.out.println("Invalid!");
				continue;
			}
			break;
		} 
		while(true) {
			System.out.print("AITP2: ");
			aitp2=sc.nextDouble();
			if (aitp2<0 || aitp2>20){
				System.out.println("Invalid!");
				continue;
			}
			break;
		} 
		while(true) {
			System.out.print("APF: ");
			apf=sc.nextDouble();
			if (apf<0 || apf>20){
				System.out.println("Invalid!");
				continue;
			}
			break;
		}
		
		double media;
		media=(aitp1 + aitp2 + aip + apf)/4;
		System.out.println("The final grade is " + media);
		if (media>=9.5)
		System.out.println("Aproved!");
		else System.out.println("Reproved!");
	}
}
