package ru.nsu.vartazaryan.controller;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;

public class Controller
{
    //CompletableFuture<List<String>>
    public void find(String text)
    {
        //CompletableFuture<Void> response = new CompletableFuture<>();
        var stringURI = String.format("https://graphhopper.com/api/1/geocode?q=%s&locale=en&key=55da9d34-cfc0-4f3e-82bb-48eb0cd9ef38"
                                            ,text);
        HttpClient client = HttpClient.newHttpClient();

        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI))
                .build();

        client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply(this::parsePlace)
                .thenAccept(System.out::println);

       // Place place = parsePlace(response);
    }

    private List<Place> parsePlace(String response)
    {
        List<Place> placeList = new ArrayList<>();
        Gson gsonParser = new Gson();
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
        //Place place = gsonParser.fromJson(json.getAsString(), Place.class);

        return placeList;
    }
}