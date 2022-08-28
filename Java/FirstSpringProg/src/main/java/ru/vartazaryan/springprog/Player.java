package ru.vartazaryan.springprog;

public class Player
{
    private Music music;

    // IoC
    public Player(Music newMusic)
    {
        this.music = newMusic;
    }

    public void playMusic()
    {
        System.out.println("Playing: " + music.getSong());
    }
}
