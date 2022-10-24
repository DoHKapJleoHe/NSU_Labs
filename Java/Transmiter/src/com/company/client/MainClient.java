package com.company.client;

import java.io.IOException;

public class MainClient
{
    public static void main(String[] args) throws IOException
    {
        String path = args[0];
        int port = Integer.parseInt(args[1]);
        Client client = new Client(path, port);
        client.run();
    }
}
