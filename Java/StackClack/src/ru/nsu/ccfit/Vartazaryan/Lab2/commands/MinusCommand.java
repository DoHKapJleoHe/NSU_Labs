package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class MinusCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] com_var_val)
    {
        double num1 = ctx.pop();
        double num2 = ctx.pop();
        double num3 = num2 - num1; // num2 lays under num1, so maybe it is correct to write num1 - num2

        ctx.push(Double.toString(num3));
    }
}
