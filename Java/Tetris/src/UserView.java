import javax.swing.*;
import java.awt.*;

public class UserView extends JFrame // this class will inherit all functions of JFrame
{
    private JButton startButton = new JButton("Start");
    private JLabel gameName = new JLabel("TETRIS");

    public UserView()
    {
        super("TETRIS"); // referencing the base class to change frame's name
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // this operation will close created frame
    }

    public void init()
    {
        this.setBounds(100, 100, 250, 250);
        Container container = this.getContentPane();
        // container is an entity that will contain our objects such as buttons, labels etc.
        // this.getContentPane() means that container will contain objects of our frame
    }
}
