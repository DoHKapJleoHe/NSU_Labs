package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        char[] symb = new char[500];
        int[] freq = new int[500];
        FileReader reader = new FileReader("C:/Users/eduar/Desktop/Kekw.txt");
        while(reader.ready())
        {
            int symbol = reader.read();
            freq[symbol] += 1;
        }

        for(int i = 0; i < freq.length; i++)
        {
            if(freq[i] != 0)
            {
                System.out.println((char)i + " " + freq[i]);
            }
        }
    }
}
