package com.company.client;

import java.io.IOException;

public class MainClient
{
    public static void main(String[] args) throws IOException
    {
        int port = 8081;
        String path = "C:\\Users\\eduar\\Desktop\\MonkeyFlip\\MonkeyFlip.gif";

        Client client = new Client(path, port);
        client.run();
    }
}
