package View;

public class Figure
{
    enum Shapes // all variations of figures in the game
    {
        Noshape(new int[][]{ {0,0}, {0,0}, {0,0}, {0,0} }),
        Zshape(new int[][]{ {0,-1}, {0,0}, {-1,0}, {-1,1} }),
        Sshape(new int[][]{ {0,-1}, {0,0}, {1,0}, {1,1} }),
        Lineshape(new int[][]{ {0,-1}, {0,0}, {0,1}, {0,2} }),
        Tshape(new int[][]{ {-1,0}, {0,0}, {1,0}, {0,1} }),
        Squareshape(new int[][]{ {0,0}, {1,0}, {0,1}, {1,1} }),
        Lshape(new int[][]{ {-1,-1}, {0,-1}, {0,0}, {0,1} }),
        MirroredLshape(new int[][]{ {1,-1}, {0,-1}, {0,0}, {0,1} });

        public int coords[][]; // this is coordinates for figures

        private Shapes(int[][] coords)
        {
            this.coords = coords;
        }
    }

    private int[][] coordinates; // coordinates of any figure. they will be given below by setFigure function
    private Shapes figure;

    public Figure() // constructor of this class
    {
        coordinates = new int[4][2];
    }

    public void setFigure(Shapes shape)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++) // ??
            {
                coordinates[i][j] = shape.coords[i][j]; // taking coordinates from given figure(shape)
            }
        }

        figure = shape;
    }

    public Shapes getFigure()
    {
        return figure;
    }

    public int pieceX(int index)
    {
        // taking "x" coordinate of each piece of figure(each figure consists of 4 pieces)
        // i use "index" to choose a piece of figure; 0 means that i need "x" coordinate of that piece
        return coordinates[index][0];
    }

    public int pieceY(int index)
    {
        // taking "y" coordinate of each piece of figure(each figure consists of 4 pieces)
        // i use "index" to choose a piece of figure; 1 means that i need "y" coordinate of that piece
        return coordinates[index][1];
    }

}
