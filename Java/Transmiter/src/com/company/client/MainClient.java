package com.company.client;

import java.io.IOException;

public class MainClient
{
    public static void main(String[] args) throws IOException
    {
        int port = 8081;
        String path = args[1];//"C:\\Users\\eduar\\Desktop\\Themen Aktuell 1 - Kursbuch.pdf";

        Client client = new Client(path, port);
        client.run();
    }
}
