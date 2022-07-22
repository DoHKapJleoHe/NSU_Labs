import javax.swing.*;

public class Main
{
    public static void main(String[] args)
    {
        UserView newFrame = new UserView();
        SwingUtilities.invokeLater(() -> {
            newFrame.init();
        }); // this gives an opportunity to framework with graphical interface to include our program to its stream when it is more comfortable to framework


    }
}
