package com.company;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client
{
    private String path;
    private int serverPort;
    private byte[] buf;

    public Client(String path, int serverPort)
    {
        this.serverPort = serverPort;
        this.path = path;
    }

    public void run() throws IOException
    {
        Socket clientSocket = new Socket("127.0.0.1", 8081);

        Scanner in = new Scanner(clientSocket.getInputStream()); // to send smth
        //PrintWriter out = new PrintWriter(clientSocket.getOutputStream()); // to get smth
        OutputStream out = clientSocket.getOutputStream();

        File file = new File(path);
        String textToSend = readFromFile(file);

        buf = textToSend.getBytes(StandardCharsets.UTF_8);
        out.write(buf);
    }

    private String readFromFile(File file) throws IOException
    {
        String text = "";

        FileReader reader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(reader);

        String curText = bufferedReader.readLine();
        while(curText != null)
        {
            text = text; //+ " " + curText;

            curText = bufferedReader.readLine();
        }

        return text;
    }

}
