package ru.nsu.vartazaryan.view;

import ru.nsu.vartazaryan.controller.Controller;
import ru.nsu.vartazaryan.controller.Place;
import ru.nsu.vartazaryan.controller.Weather;

import javax.swing.*;
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
        placeJList.setBounds(480, 30, 400, 300);
        placeJList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        frame.add(placeJList);

        JLabel weatherLabel = new JLabel("Weather");
        weatherLabel.setBounds(480, 340, 400, 15);
        weatherLabel.setVisible(true);
        frame.add(weatherLabel);

        findButton.addActionListener(e -> {
            try
            {
                controller.findPlaces(textField.getText()).thenAccept(places -> SwingUtilities.invokeLater(() -> {
                    for (Place place : places)
                    {
                        String ful;
                        ful = place.getProp();
                        placeModel.addElement(ful);
                    }
                }));
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
                String[] cords = new String[3];

                place = placeModel.getElementAt(index);
                int lngInd = place.indexOf("lng");
                int latInd = place.indexOf("lat");

                lat = place.substring(latInd + 5, lngInd - 1); //+5 to pass lat= , -1 to avoid " " before lng
                lng = place.substring(lngInd + 5); //+5 to pass lng=

                try
                {
                    controller.findWeather(lat, lng).thenAccept(weather -> SwingUtilities.invokeLater(() ->{
                        weatherLabel.setText(weather.getMain() + " " + weather.getDescription());
                    }));

                }
                catch (ExecutionException | InterruptedException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}
