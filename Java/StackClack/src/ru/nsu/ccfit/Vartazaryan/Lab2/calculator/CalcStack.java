package ru.nsu.ccfit.Vartazaryan.Lab2.calculator;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class CalcStack
{
    private int varNumber;
    private Stack<Double> numberStack = new Stack<>();
    private Map<String, Double> valuesOfVariables = new HashMap<>(); // Here i contain values of variables, that were defined by #DEFINE command

    public CalcStack(){}; // Constructor

    public void push(String arg) {
        //System.out.println("Pushing string");

        if(!isNumber(arg))
        {
            numberStack.push(valuesOfVariables.get(arg));// if argument is a letter
        }
        else {
            numberStack.push(Double.parseDouble(arg));//if argument is number
        }
    }

    public boolean isNumber(String str)
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

    public void push(double arg)
    {
        //System.out.println("Pushing num");
        numberStack.push(arg);
    }

    public double pop() { return numberStack.pop(); }

    public double peek() {
        try {
            return numberStack.peek();
        }
        catch (Exception e) {
            System.out.println("Exception :(");
        }
        return 0;
    }

    public void addVar(String variable, Double value){ valuesOfVariables.put(variable, value);}
}


