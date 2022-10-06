package com.company.client;

import java.io.IOException;

public class MainClient
{
    public static void main(String[] args) throws IOException
    {
        int port = 8081;
        String path = "C:\\Users\\eduar\\Desktop\\Проекты\\GIT\\NSU_Labs\\Java\\Transmiter\\out\\production\\Transmiter\\com\\company\\client\\MonkeyFlip.gif";

        Client client = new Client(path, port);
        client.run();
    }
}
