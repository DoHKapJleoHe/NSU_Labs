package ru.nsu.vartazaryan.controller;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class Controller
{
    //CompletableFuture<List<String>>
    public List<Place> findPlaces(String text) throws ExecutionException, InterruptedException {
        HttpClient client = HttpClient.newHttpClient();

        var stringURI_places = String.format("https://graphhopper.com/api/1/geocode?q=%s&locale=en&key=55da9d34-cfc0-4f3e-82bb-48eb0cd9ef38", text);
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_places))
                .build();

        CompletableFuture<List<Place>> places = new CompletableFuture<List<Place>>();
        places = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parsePlace);

        List<Place> finalList = places.get();

        return finalList;
    }

    private List<Place> parsePlace(String response)
    {
        List<Place> placeList = new ArrayList<>();

        JsonObject json = JsonParser.parseString(response).getAsJsonObject();
        JsonArray arr = json.get("hits").getAsJsonArray();

        String name, lng, lat;
        for(int i = 0; i < arr.size(); i++)
        {
            name = arr.get(i).getAsJsonObject().get("name").toString();
            lng = arr.get(i).getAsJsonObject().get("point").getAsJsonObject().get("lng").toString();
            lat = arr.get(i).getAsJsonObject().get("point").getAsJsonObject().get("lat").toString();

            placeList.add(new Place(lat, lng, name));
        }

        return placeList;
    }

    public Weather findWeather(String lat, String lng) throws ExecutionException, InterruptedException {
        var stringURI_weather = String.format("http://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=936235de21b90aa0788fb20ec5efe8fa", lat, lng);

        HttpClient client = HttpClient.newHttpClient();
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_weather))
                .build();
        CompletableFuture<Weather> placeWeather = new CompletableFuture<>();

        placeWeather = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parseWeather);

        return placeWeather.get();
    }

    private Weather parseWeather(String response)
    {


        JsonObject json = JsonParser.parseString(response).getAsJsonObject();
        JsonArray arr = json.get("weather").getAsJsonArray();

        String main, descr;
        main = arr.get(0).getAsJsonObject().get("main").toString();
        descr = arr.get(0).getAsJsonObject().get("description").toString();

        Weather weather = new Weather(main, descr);

        return weather;
    }
}