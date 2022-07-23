import Controller.MenuController;
import Model.MenuModel;
import View.MenuView;

import javax.swing.*;

public class Main
{
    public static void main(String[] args)
    {
        MenuModel model = new MenuModel();
        MenuController controller = new MenuController(model);
        MenuView newFrame = new MenuView(controller);

        SwingUtilities.invokeLater(() -> {
            newFrame.initStartScreen();
        }); // this gives an opportunity to framework with graphical interface to include our program to its stream when it is more comfortable to framework


    }
}
