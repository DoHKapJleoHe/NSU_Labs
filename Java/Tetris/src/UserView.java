import javax.swing.*;
import java.awt.*;

public class UserView extends JFrame // this class will inherit all functions of JFrame
{
    private JButton startButton;
    private JLabel gameName;
    private Controller controller;

    public UserView(Controller controller)
    {
        super("TETRIS"); // referencing the base class to change frame's name
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // this operation will close created frame
    }

    public void initStartScreen()
    {
        this.setBounds(100, 100, 250, 250);
        this.setVisible(true);

        // parameters of button
        startButton = new JButton("Start");
        startButton.setSize(100, 30);
        startButton.setLocation(20, 50);

        // parameters of label
        gameName = new JLabel("TETRIS");
        gameName.setSize(100, 30);
        gameName.setLocation(50, 20);

        this.getContentPane().setLayout(null); // so that the elements do not stretch to full frame
        this.add(startButton); // adding button to frame
        this.add(gameName); // adding label to frame

        startButton.addActionListener(e -> {
            //controller.
        });
    }
}
