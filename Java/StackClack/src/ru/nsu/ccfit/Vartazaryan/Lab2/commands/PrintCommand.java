package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CalcStack;

public class PrintCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] com_var_val)
    {
        System.out.println(ctx.peek());
    }

}
