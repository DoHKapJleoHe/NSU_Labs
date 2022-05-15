package ru.nsu.ccfit.Vartazaryan.Lab2.Calculator;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class CalcStack
{
    private int varNumber;
    private static final Stack<Double> numberStack = new Stack<>();
    private static final Map<String, Double> valuesOfVariables = new HashMap<>(); // Here i contain values of variables, that were defined by #DEFINE command

    public CalcStack(){}; // Constructor

    public static void push(String arg)
    {
            if(!isNumber(arg))
            {
                numberStack.push(valuesOfVariables.get(arg));// if argument is a letter
            }
            else {
                numberStack.push(Double.parseDouble(arg));//if argument is number
            }

    }

    public static double pop()
    {
        return numberStack.pop();
    }

    public static boolean isNumber(String str)
    {
        if (str == null || str.isEmpty())
            return false;
        for (int i = 0; i < str.length(); i++)
        {
            if (!Character.isDigit(str.charAt(i)))
                return false;
        }
        return true;
    }

    public static double peek()
    {

        return numberStack.peek();
    }

    public static void addVar(String variable, Double value)
    {
        valuesOfVariables.put(variable, value);
    }
}


