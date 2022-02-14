package ru.nsu.ccfit.vartazaryan.lab1;

import java.io.*;
import java.util.*;
import java.util.stream.Stream;

public class Main
{

    public static void main(String[] args)
    {
        HashMap<String, Integer> words = new HashMap<String, Integer>(); // here i will store the number of occurrences of words in a file
        Reader reader = null;
        StringBuilder build_word = new StringBuilder(15);

        int numberOfWords = 0; // the number of words in  the whole file
        String cur_word;

        try
        {
            reader = new InputStreamReader(new FileInputStream("C:/Users/eduar/Desktop/Kekw.txt"));
            while (reader.ready())
            {
                char symb = (char)reader.read(); // reading symbol
                while(Character.isLetterOrDigit(symb)) // here i check symbol to find "space"
                {
                    build_word.append(symb); // adding symbol to the word
                    symb = (char)reader.read(); // reading symbol
                }
                if(symb == '\n')
                {
                    build_word.setLength(0);
                    continue;
                }
                numberOfWords++; //increasing the number of words
                cur_word = build_word.toString();
                if(words.get(cur_word) == null) // if there is no Value for Key
                {
                    words.put(cur_word, 0);
                    words.put(cur_word, words.get(cur_word) + 1);// put in map the word. second parameter is the number of words of that type
                }
                else
                {
                    words.put(cur_word, words.get(cur_word) + 1);// put in map the word. second parameter is the number of words of that type
                }
                build_word.setLength(0); // "deleting" word by zeroing its length
                cur_word = "";
            }
        }
        catch (IOException e)
        {
            System.err.println("Error while reading file: " + e.getLocalizedMessage());
        }

        final Integer numOfWords = numberOfWords;

        try (FileWriter writer = new FileWriter("C:/Users/eduar/Desktop/out.csv");)
        {
            Set<HashMap.Entry<String, Integer>> set = words.entrySet(); // converted HashMap into Set, which elements are <String, Integer>
            Stream<HashMap.Entry<String, Integer>> stream = set.stream();
            stream
                    .sorted(Map.Entry.comparingByValue())
                    .forEach(el -> {
                        try {
                            writer.write(el.getKey()); // typing Key from Map
                            writer.write(';'); // changing column
                            String freq = el.getValue().toString(); //converting Value from Map to String because writer can't work with Integer
                            writer.write(freq); //typing freq
                            writer.write(';'); //changing column
                            Integer Value = el.getValue();
                            double Freq = (double)Value / (double)numOfWords;
                            Double finFreq = Freq * (double) 100;
                            Integer finFreq2 = finFreq.intValue();
                            String freqInPercents = Integer.toString(finFreq2);
                            writer.write(freqInPercents);
                            writer.write('\n');
                            }
                        catch (IOException e)
                        {
                            e.printStackTrace();
                        }
                    });
        }
        catch(IOException e)
        {
            System.err.println("Error while writing file: " + e.getLocalizedMessage());
        }
    }
}
