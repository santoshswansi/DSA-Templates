//Find factorial using BigInteger class

import java.math.BigInteger;
import java.util.*;

public class factorialBigInteger
{

  static BigInteger factorial(int number)
  {
      BigInteger fact = new BigInteger("1");

      for(int i = 2; i <= number; ++i)
      {
          fact = fact.multiply(BigInteger.valueOf(i));
      }

      return fact;
  }  
  public static void main(String args[])
  {
    int number; 
    Scanner scanner = new Scanner(System.in);

    System.out.print("Enter a number : ");
    number = scanner.nextInt();

    System.out.print("\nFactorial of "+ number +" is "+ factorial(number));

    scanner.close();
  }
}