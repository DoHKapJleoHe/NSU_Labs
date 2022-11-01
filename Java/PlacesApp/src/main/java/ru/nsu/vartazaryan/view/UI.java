package ru.nsu.vartazaryan.view;

import ru.nsu.vartazaryan.controller.Controller;
import ru.nsu.vartazaryan.controller.Place;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class UI
{
    private static final Controller controller = new Controller();

    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        frame.setBounds(300, 0, 1000, 800);
        frame.getContentPane().setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        JButton findButton = new JButton("Find!");
        findButton.setBounds(30, 30, 100, 25);
        findButton.setVisible(true);
        frame.add(findButton);

        JTextField textField = new JTextField("Write here text...");
        textField.setVisible(true);
        textField.setBounds(160, 30, 300, 25);
        frame.add(textField);

        DefaultListModel<String> placeModel = new DefaultListModel<>();
        JList<String> placeJList = new JList(placeModel);
        placeJList.setVisible(true);
        placeJList.setBounds(480, 40, 400, 400);
        placeJList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        frame.add(placeJList);

        findButton.addActionListener(e -> {
            List<Place> placeList;
            try
            {
                placeList = controller.findPlaces(textField.getText());
                for (Place place : placeList)
                {
                    String ful;
                    ful = place.getName() + place.getLat() + place.getLng();
                    placeModel.addElement(place.getName() + " " + place.getLat() + " " + place.getLng());
                }
            } catch (ExecutionException | InterruptedException ex) {
                System.out.println("Error while getting list of places!");
                ex.printStackTrace();
            }
        });

        placeJList.addListSelectionListener(e -> {
            if(e.getValueIsAdjusting())
            {
                int index = e.getLastIndex();
                String lat, lng, place;

                place = placeModel.getElementAt(index);
                System.out.println("Place"+"="+place);
            }
        });
    }
}
