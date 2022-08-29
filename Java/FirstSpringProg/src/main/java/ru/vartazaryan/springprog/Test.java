package ru.vartazaryan.springprog;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test
{
    public static void main(String[] args)
    {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
                "applicationContext.xml"
        );

        //Music bean = context.getBean("musicBean", Music.class);
        //Player newPlayer = new Player(bean);

        Player newPlayer = context.getBean("player", Player.class); // dependency injection
        System.out.println("Player name: " + newPlayer.getName());
        System.out.println("Volume: " + newPlayer.getVolume());
        newPlayer.playMusic();

        context.close();
    }
}
