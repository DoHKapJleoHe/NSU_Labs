package ru.nsu.ccfit.Vartazaryan.Lab2;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CommandLineCalculator;
import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.FileCalculator;

import java.io.FileNotFoundException;

public class Main
{
    public static void main(String[] args) throws FileNotFoundException
    {
        //"C:/Users/eduar/Desktop/CommandList.txt"
        int length = args.length;
        if(length != 0) // reading from file
        {
            FileCalculator calculator = new FileCalculator();
            String path = args[0];
            calculator.run(path);
        }
        else //reading from console
        {
            CommandLineCalculator commandLineCalculator = new CommandLineCalculator();
            commandLineCalculator.run();
        }
    }
}
