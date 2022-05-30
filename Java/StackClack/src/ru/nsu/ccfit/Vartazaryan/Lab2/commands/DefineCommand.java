package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CalcStack;

public class DefineCommand implements Command
{

    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        // args[0] = command, args[1] = variable, args[2] = value

        ctx.addVar(args[1], Double.parseDouble(args[2]));
    }
}
