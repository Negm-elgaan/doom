using System.Reflection.Emit;

namespace ConsoleApp5
{
    class recarea
    {
        int x;
        int y;
        public void getlength(int l)
        {
            x = l;
        }
        public void getwidth(int w)
        {
            y = w;
        }
        public int returnarea()
        {
            return x * y;
        }
    };
    internal class Program
    {
        
        static void cubeorcuboid(int x,int y,int z)
        {
            if (x == y && x == z)
                Console.WriteLine("cube");
            else
                Console.WriteLine("cuboid");
        }
        static void Main(string[] args)
        {
            recarea a = new recarea();
            a.getlength(5);
            a.getwidth(4);
            Console.WriteLine(a.returnarea()); 
           /* double mx = 0;
            int g = 0;
            int[] x = new int[50];
            double[] y = new double[50];
            for (int i = 0; i < 5; i++)
            {
                x[i] = int.Parse(Console.ReadLine());
                y[i] = double.Parse(Console.ReadLine());
                if (y[i] < 50)
                    y[i] += 5;
                if (mx < y[i])
                {
                    mx = y[i];
                    g = x[i];
                }
            }
            Console.WriteLine(g);
            /*for (int j = 1; j <=5; j++)
            {
                for (int k = 0; k < j; k++)
                {
                    Console.Write(j);
                }
                Console.WriteLine("");
            }
            /*int[] x = new int[50];
            for (int i = 0; i < 50; i++)
            {
                x[i] = int.Parse(Console.ReadLine());
            }
            for (int i = 0; i < 50; i++)
            {
                y += x[i];
            }
            Console.WriteLine(y/50);
            
            /*int[] j = new int[x];
            while (i < x)
            {
                j[i] = int.Parse(Console.ReadLine());
                i++;
            }
            i = 0;
            while (i < x)
            {
                Console.WriteLine(j[i]);
                i++;   
            }*/
          /*if ( x >= 90)
            {
                Console.WriteLine('A');
            }
          else if (x >= 75)
            {
                Console.WriteLine('B');
            }
          else if (x >= 60)
            {
                Console.WriteLine('C');
            }
          else
            {
                Console.WriteLine("fail");
            }
            */
        }
    }
}
