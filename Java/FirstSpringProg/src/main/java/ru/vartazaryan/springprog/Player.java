package ru.vartazaryan.springprog;

public class Player
{
    private Music music;
    private String name;
    private int volume;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getVolume() {
        return volume;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    // IoC
    public Player(Music newMusic)
    {
        this.music = newMusic;
    }

    public Player() {}

    public void setMusic(Music music)
    {
        this.music = music;
    }

    public void playMusic()
    {
        System.out.println("Playing: " + music.getSong());
    }
}
