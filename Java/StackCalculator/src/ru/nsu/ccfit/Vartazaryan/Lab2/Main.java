package ru.nsu.ccfit.Vartazaryan.Lab2;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.FileCalculator;

public class Main
{
    public static void main(String[] args)
    {
        if(args[0] != "") // reading from file
        {
            FileCalculator calculator = new FileCalculator();
            calculator.Run(args[0]);
        }
        else //reading from console
        {

        }
    }
}
