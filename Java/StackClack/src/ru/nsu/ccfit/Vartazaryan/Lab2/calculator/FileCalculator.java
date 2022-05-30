package ru.nsu.ccfit.Vartazaryan.Lab2.calculator;

import ru.nsu.ccfit.Vartazaryan.Lab2.factory.ComFac;
import ru.nsu.ccfit.Vartazaryan.Lab2.commands.Command;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.InvocationTargetException;
import java.util.Scanner;

public class FileCalculator
{
    public FileCalculator() {} //Constructor

    public void Run(String path) throws FileNotFoundException
    {
        File file = new File(path);
        Scanner scanner = new Scanner(file);
        CalcStack ctx = new CalcStack();
        ComFac Factory = new ComFac();

        Command newCom = null;
        while (scanner.hasNext()) // reading file
        {
            String command_line = scanner.nextLine(); // put first command line here
            String[] com_var_val = command_line.split(" "); // splitting words in line by space. 1 - command, 2 - variable, 3 - value

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
