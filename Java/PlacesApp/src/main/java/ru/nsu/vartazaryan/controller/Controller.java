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
    public CompletableFuture<List<Place>> findPlaces(String text) throws ExecutionException, InterruptedException {
        HttpClient client = HttpClient.newHttpClient();

        var stringURI_places = String.format("https://graphhopper.com/api/1/geocode?q=%s&locale=en&key=55da9d34-cfc0-4f3e-82bb-48eb0cd9ef38", text);
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_places))
                .build();

        //System.out.println(request);

        CompletableFuture<List<Place>> places = new CompletableFuture<List<Place>>();
        places = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parsePlace);

        return places;
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

    public CompletableFuture<Weather>  findWeather(String lat, String lng) throws ExecutionException, InterruptedException
    {
        HttpClient client = HttpClient.newHttpClient();

        var stringURI_weather = String.format("http://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=936235de21b90aa0788fb20ec5efe8fa", lat, lng);
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_weather))
                .build();

        CompletableFuture<Weather> placeWeather = new CompletableFuture<>();
        placeWeather = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parseWeather);

        return placeWeather;
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

    public CompletableFuture<List<InterestingPlaces>> getInterestingPlaces(String lat, String lng)
    {
        HttpClient client = HttpClient.newHttpClient();

        var stringURI_interestingPlaces = String.format("http://api.opentripmap.com/0.1/ru/places/radius?lang=ru&radius=100000&lon=%s&lat=%s&format=json&limit=2&apikey=5ae2e3f221c38a28845f05b6d9e0b6fa8c894ce4eef74f7b2e15830c", lng, lat);
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_interestingPlaces))
                .build();

        System.out.println(request);

        CompletableFuture<List<InterestingPlaces>> interestingPlaces = new CompletableFuture<>();
        interestingPlaces = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parseInterestingPlaces);

        return interestingPlaces;
    }

    public List<InterestingPlaces> parseInterestingPlaces(String response)
    {
        List<InterestingPlaces> places = new ArrayList<>();

        String name, id;
        JsonArray json = JsonParser.parseString(response).getAsJsonArray();

        for(int i = 0; i < json.size(); i++)
        {
            name = json.get(i).getAsJsonObject().get("name").toString();
            id = json.get(i).getAsJsonObject().get("xid").toString();

            places.add(new InterestingPlaces(name, id));
        }

        return places;
    }

    public CompletableFuture<String> getPlaceInfoById(String xid)
    {
        HttpClient client = HttpClient.newHttpClient();

        var stringURI_info = String.format("http://api.opentripmap.com/0.1/ru/places/xid/%s?apikey=5ae2e3f221c38a28845f05b6d9e0b6fa8c894ce4eef74f7b2e15830c", xid);
        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI_info))
                .build();

        System.out.println(request);

        CompletableFuture<String> info = new CompletableFuture<>();
        info = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parseInfo);

        return info;
    }

    // TODO: Correct this parsing method
    private String parseInfo(String request)
    {
        System.out.println(request);
        JsonObject obj = JsonParser.parseString(request).getAsJsonObject();
        String info = obj.get("info").getAsJsonObject().get("descr").toString();

        return info;
    }
}