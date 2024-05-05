using System.IO;
namespace filetest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            FileStream myfile = new FileStream("File1.txt", FileMode.Create, FileAccess.ReadWrite);
            StreamWriter sw = new StreamWriter(myfile);
            StreamReader sr = new StreamReader(myfile);
            string Line;
            while (true)
            {
                Line = Console.ReadLine();
                sw.WriteLine(Line);
                sw.Flush();
                Console.WriteLine("Do you want to add another entry?\nyes/no?\n");
                string choice = Console.ReadLine();
                if (choice.ToUpper() == "NO")
                    break;
            }
            myfile.Seek(0, SeekOrigin.Begin);
            string Line2;
            while (true)
            {
                Line2 = sr.ReadLine(); 
                if (Line2 == null) 
                    break;
                Console.WriteLine(Line2);
            }
            sw.Close();
            sr.Close(); 
            myfile.Close();
        }  
    }
}
