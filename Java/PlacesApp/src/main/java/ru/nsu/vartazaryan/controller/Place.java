package ru.nsu.vartazaryan.controller;

public class Place
{
    private String lat;
    private String lng;
    private String name;

    public Place(String lat, String lng, String name)
    {
        this.lat = lat;
        this.lng = lng;
        this.name = name;
    }

    public String getProp()
    {
        return name+" "+"lat="+" "+lat+" "+"lng="+" "+lng;
    }

    public String getLat() {
        return lat;
    }

    public String getLng() {
        return lng;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString()
    {
        return this.name + " (lat: " + this.lat + " lng: " + this.lng + ")" +"\n";
    }
}
