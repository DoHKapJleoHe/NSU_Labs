package ru.nsu.vartazaryan.controller;

import com.google.gson.Gson;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;

public class Controller
{
    public CompletableFuture<List<String>> find(String text)
    {
        CompletableFuture<String> response = new CompletableFuture<String>();
        var stringURI = String.format("https://graphhopper.com/api/1/geocode?q=%s&locale=en&key=55da9d34-cfc0-4f3e-82bb-48eb0cd9ef38"
                                            ,text);
        HttpClient client = HttpClient.newHttpClient();

        var request = HttpRequest
                .newBuilder()
                .GET()
                .uri(URI.create(stringURI))
                .build();

        response = client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                .thenApply(HttpResponse::body)
                .thenApply();


    }

    private void parser(String response)
    {
        //TODO: make class for coordinates and other stuff
        Gson gsonParser = new Gson();
        String lat;
        String lng;
        String name;

        name = gsonParser.fromJson(response, );
    }
}