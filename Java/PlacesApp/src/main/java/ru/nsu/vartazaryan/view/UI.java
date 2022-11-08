package ru.nsu.vartazaryan.view;

import ru.nsu.vartazaryan.controller.Controller;
import ru.nsu.vartazaryan.controller.InterestingPlaces;
import ru.nsu.vartazaryan.controller.Place;

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

        DefaultListModel<String> interestingPlacesModel = new DefaultListModel<>();
        JList<String> interestingPlacesJList = new JList<>(interestingPlacesModel);
        interestingPlacesJList.setVisible(true);
        interestingPlacesJList.setBounds(480, 380, 400, 300);
        frame.add(interestingPlacesJList);

        JLabel infoAboutPlace = new JLabel("info");
        infoAboutPlace.setBounds(50, 380, 400, 100);
        infoAboutPlace.setVisible(true);
        frame.add(infoAboutPlace);

        frame.setVisible(true);

        findButton.addActionListener(e -> {
            try
            {
                controller.findPlaces(textField.getText()).thenAccept(places -> SwingUtilities.invokeLater(() -> {
                    placeModel.clear(); // clear list from the previous request
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

                    controller.getInterestingPlaces(lat, lng).thenAccept(interestingPlaces -> SwingUtilities.invokeLater(() -> {
                        for(InterestingPlaces places : interestingPlaces)
                        {
                            interestingPlacesModel.clear();
                            String ful;
                            ful = places.getName() + " " + "id" + " "+ places.getId();
                            interestingPlacesModel.addElement(ful);
                        }
                    }));

                }
                catch (ExecutionException | InterruptedException ex)
                {
                    System.out.println("Error while getting weather!");
                    ex.printStackTrace();
                }


            }
        });

        interestingPlacesJList.addListSelectionListener(e -> {
            if(e.getValueIsAdjusting())
            {
                int index = e.getLastIndex();
                String place = interestingPlacesModel.getElementAt(index);
                int idIndex = place.indexOf("id");
                String id = place.substring(idIndex + 4, place.length() - 1);
                //System.out.println(id);

                controller.getPlaceInfoById(id).thenAccept(info -> SwingUtilities.invokeLater(() -> {
                    System.out.println("info");
                    infoAboutPlace.setText(info);
                }));
            }
        });
    }
}
