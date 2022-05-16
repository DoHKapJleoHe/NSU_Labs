package ru.nsu.ccfit.Vartazaryan.Lab2;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.FileCalculator;

import java.io.FileNotFoundException;

public class Main
{
    public static void main(String[] args) throws FileNotFoundException
    {
        if(args[0] != "") // reading from file
        {
            FileCalculator calculator = new FileCalculator();
            String path = args[0];
            calculator.Run(path);
        }
        else //reading from console
        {

        }
    }
}
