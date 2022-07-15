package Tasks.MemDefragmentator

import java.util.Arrays;
import java.util.Objects;

/* 
  I have an array with null's inside. I have to move null's to the end of the array.
*/

public class Memory
{
    public static void executeDefragmentation(String[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            if(array[i] == null)
            {
               int j = i + 1;
               
               while(j < array.length)
               {
                   if(array[j] != null)
                   {
                        array[i] = array[j];
                        array[j] = null;
                        
                        break;
                   }
                   
                   j++;
               }
               
               j = 0;
            }
            
        }
    }

    public static void main(String[] args) 
    {
        String[] memory = {"First", null, null, "Second", null, null, null, "Third", null, "Fourth"};
        executeDefragmentation(memory);
        System.out.println(Arrays.toString(memory));
    }

    
}
