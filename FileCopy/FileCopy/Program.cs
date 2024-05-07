using System.IO;
using static System.Net.WebRequestMethods;
namespace FileCopy
{
    internal class Program
    {
        static void FILECOPY(FileStream File1 ,FileStream File2)
        {
            StreamWriter sw1 = new StreamWriter(File1);
            StreamWriter sw2 = new StreamWriter(File2);
            StreamReader sr1 = new StreamReader(File1);
            StreamReader sr2 = new StreamReader(File2);
            string Line;
            while (true)
            {
                Line = Console.ReadLine();
                sw1.WriteLine(Line);
                sw1.Flush();
                Console.WriteLine("Do you want to add another entry?\nyes/no?\n");
                string choice = Console.ReadLine();
                if (choice.ToUpper() == "NO")
                    break;
            }
            File1.Seek(0, SeekOrigin.Begin);
            while (true)
            {
                Line = sr1.ReadLine();
                if (Line == null)
                    break;
                Console.WriteLine(Line);
                
            }
            File1.Seek(0,SeekOrigin.Begin);
            while (true)
            {
                Line = sr1.ReadLine();
                if (Line == null) break; 
                sw2.WriteLine(Line);
                sw2.Flush();
            }
            File2.Seek(0, SeekOrigin.Begin);
            while (true)
            {
                Line = sr2.ReadLine();
                if (Line == null) break;
                Console.WriteLine(Line);
            }
            sw1.Close();
            sr1.Close();
            sw2.Close();
            sr2.Close();
            File1.Close();
            File2.Close();
        }
    
        static void Main(string[] args)
        {
            FileStream File1 = new FileStream("Text1.txt" , FileMode.Create , FileAccess.ReadWrite);
            FileStream File2 = new FileStream("Text2.txt", FileMode.Create, FileAccess.ReadWrite);
            FILECOPY(File1 , File2);
        }
    }
}
