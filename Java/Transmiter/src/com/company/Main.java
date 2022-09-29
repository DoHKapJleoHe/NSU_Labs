package com.company;

import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        int port = 8081;
        String path = "";


        Server server = new Server(port);
        server.run();
        Client client = new Client(path);
        client.run();
    }
}
