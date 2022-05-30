package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CalcStack;

public interface Command
{
    public void execute(CalcStack ctx, String[] args);
}
