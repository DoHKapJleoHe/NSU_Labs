package ru.vartazaryan.springprog;

import java.util.ArrayList;
import java.util.List;

public class Player
{
    private List<Music> musicList = new ArrayList<>();

    private String name;
    private int volume;

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public int getVolume()
    {
        return volume;
    }

    public void setVolume(int volume)
    {
        this.volume = volume;
    }

    // IoC
    public Player(List<Music> newMusicList)
    {
        this.musicList = newMusicList;
    }

    public Player() {}

    public void setMusic(List<Music> musicList)
    {
        this.musicList = musicList;
    }

    public void playMusic()
    {
        for (Music music : musicList) {
            System.out.println("Playing: " + music.getSong());
        }
    }
}
