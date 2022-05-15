package ru.nsu.ccfit.Vartazaryan.Lab2.Factory;

import ru.nsu.ccfit.Vartazaryan.Lab2.commands.Command;

import java.lang.reflect.InvocationTargetException;

public class ComFac
{
    /*Factory is a thing that creates commands by given name. Then you can use made command to some stuff.
      Class.forName("ru.nsu.ccfit.vartazaryan.lab2.someClass") - returns object of "class" class initialized by "someClass"
      getConstructor() - returns object of "constructor" class of class "someClass
      newInstance() - creates object of "someClass" class by constructor, taht was returned from getConstructor()"*/

    public ComFac() {}

    public Command getCommand(String name) throws ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException
    {
        return (Command) Class.forName(name).getConstructor().newInstance();
    }
}
