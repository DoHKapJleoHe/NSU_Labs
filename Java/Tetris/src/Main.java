import javax.swing.*;

public class Main
{
    public static void main(String[] args)
    {
        Model model = new Model();
        Controller controller = new Controller();
        UserView newFrame = new UserView(controller);

        SwingUtilities.invokeLater(() -> {
            newFrame.initStartScreen();
        }); // this gives an opportunity to framework with graphical interface to include our program to its stream when it is more comfortable to framework


    }
}
