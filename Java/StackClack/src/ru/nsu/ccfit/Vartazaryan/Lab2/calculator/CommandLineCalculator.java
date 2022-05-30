package ru.nsu.ccfit.Vartazaryan.Lab2.calculator;

import ru.nsu.ccfit.Vartazaryan.Lab2.factory.ComFac;
import ru.nsu.ccfit.Vartazaryan.Lab2.commands.Command;

import java.lang.reflect.InvocationTargetException;
import java.util.Scanner;

public class CommandLineCalculator
{
    public void run()
    {
        Scanner scanner = new Scanner(System.in);
        ComFac Factory = new ComFac();
        String nextLine = " ";
        Command newCom = null;
        CalcStack ctx = new CalcStack();

        while (scanner.hasNextLine())
        {
            nextLine = scanner.nextLine();
            String[] com_var_val = nextLine.split(" ");

            try
            {
                newCom = Factory.getCommand(com_var_val[0]);
                newCom.execute(ctx, com_var_val);
            }
            catch (ClassNotFoundException | NoSuchMethodException | InstantiationException | InvocationTargetException | IllegalAccessException e)
            {
                e.printStackTrace();
            }
        }
    }
}
