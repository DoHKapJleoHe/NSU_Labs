package com.company.server;

import java.io.IOException;

public class MainServer
{
    public static void main(String[] args) throws IOException {
        int port = 8081;

        Server server = new Server(port);
        server.run();
    }
}
