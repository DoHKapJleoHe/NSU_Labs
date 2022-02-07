package com.company;

import java.util.Random;
import java.util.Scanner;

public class Main 
{

    public static void main(String[] args)
    {
        System.out.println("Hi");
        Random randNum = new Random();

        Integer number = randNum.nextInt(10);
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            if(scanner.nextInt() == number)
            {
                System.out.println("You won!!!");
                break;
            }
            else
            {
                System.out.println("No!!!");
            }

        }
    }
}
