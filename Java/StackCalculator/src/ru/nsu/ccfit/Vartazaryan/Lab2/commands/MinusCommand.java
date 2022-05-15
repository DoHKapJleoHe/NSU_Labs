package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class MinusCommand implements Command
{
//    void MINUS()
//    {
//        double num1 = CalcStack.pop();
//        double num2 = CalcStack.pop();
//        double num3 = num1 - num2;
//        CalcStack.push(num3);
//    }

    @Override
    public void execute(String[] com_var_val)
    {
        double num1 = CalcStack.pop();
        double num2 = CalcStack.pop();
        double num3 = num2 - num1; // num2 lays under num1, so maybe it is correct to write num1 - num2

        CalcStack.push(Double.toString(num3));
    }
}
