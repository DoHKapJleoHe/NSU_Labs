package ru.nsu.ccfit.Vartazaryan.Lab2.Calculator;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;
import ru.nsu.ccfit.Vartazaryan.Lab2.Factory.ComFac;
import ru.nsu.ccfit.Vartazaryan.Lab2.commands.Command;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;
import java.util.Scanner;

public class FileCalculator
{
    public FileCalculator() {} //Constructor

    public static void Run(String path)
    {
        Scanner scanner = new Scanner(path); // i will use it to read file
        CalcStack ctx = new CalcStack();
        ComFac Factory = new ComFac();

        Properties prop = new Properties();
        FileInputStream stream;
        try
        {
            stream = new FileInputStream("commands.properties");
            prop.load(stream);
        } catch(IOException e)
        {
            e.printStackTrace();
        }

        Command newCom = null;
        while (scanner.hasNext()) // reading file
        {
            String command_line = scanner.nextLine(); // put first command line here
            String[] com_var_val = command_line.split(" "); // splitting words in line by space. 1 - command, 2 - variable, 3 - value

            try
            {
                newCom = Factory.getCommand(prop.getProperty(com_var_val[0]));
                newCom.execute(com_var_val);

            }
            catch (ClassNotFoundException | NoSuchMethodException | InstantiationException | InvocationTargetException | IllegalAccessException e)
            {
                e.printStackTrace();
            }
        }
    }
}
