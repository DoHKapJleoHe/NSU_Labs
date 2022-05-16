package ru.nsu.ccfit.Vartazaryan.Lab2.Calculator;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class CalcStack
{
    private int varNumber;
    private Stack<Double> numberStack = new Stack<>();
    private Map<String, Double> valuesOfVariables = new HashMap<>(); // Here i contain values of variables, that were defined by #DEFINE command

    public CalcStack(){}; // Constructor

    public void push(String arg)
    {
        /*if(!isNumber(arg))
        {
            numberStack.push(valuesOfVariables.get(arg));// if argument is a letter
        }
        else {
            numberStack.push(Double.parseDouble(arg));//if argument is number
        }*/
        numberStack.push(valuesOfVariables.get(arg));
    }

    public void push(double arg)
    {
        numberStack.push(arg);
    }

    public double pop()
    {
        return numberStack.pop();
    }

    /*public boolean isNumber(String str)
    {
        if (str == null || str.isEmpty())
            return false;
        for (int i = 0; i < str.length(); i++)
        {
            if (!Character.isDigit(str.charAt(i)))
                return false;
        }
        return true;
    }*/

    public double peek()
    {
        return numberStack.peek();
    }

    public void addVar(String variable, Double value)
    {
        valuesOfVariables.put(variable, value);
    }
}


