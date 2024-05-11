using System.Formats.Tar;
using System.IO;
using System.IO.Pipes;
using static System.Net.WebRequestMethods;
namespace sheet1
{
    internal class Program
    {   
        static void Read10Lines(FileStream fs,String Readloc)
        {
            int x = 0;
            StreamWriter sw = new StreamWriter(fs);
            StreamReader sr = new StreamReader(fs);
            string Line = "";
            string[] TenLines = new string[10];
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
            fs.Seek(0, SeekOrigin.Begin);
            Console.WriteLine("enter begin to start at beginning of file or end to start at ending o file\n");
            Readloc = Console.ReadLine();
            if (Readloc == "Begin" || Readloc == "begin")
            {
                
                while (true)
                {
                    Line = sr.ReadLine();
                    if (Line == null)
                        break;
                    Console.WriteLine(Line);
                }
            }
            else
            {
                
                while (true)
                {
                    Line = sr.ReadLine();
                    if (Line == null)
                        break;
                    TenLines[x] = Line;
                    x++;
                    if (x > 9)
                        x = 0;
                }
                Console.WriteLine(x);
                for (int i = 0; i < x; i++)
                    Console.WriteLine(TenLines[i]);
            }
           

        }
        static void Count(FileStream fs)
        {
            int x = 0;
            int numofchars = 0 , numberofwords = 1 , numberoflines = -1 ;
            StreamWriter sw = new StreamWriter(fs);
            StreamReader sr = new StreamReader(fs);
            string Line = "";
            string[] TenLines = new string[10];
            while ((Line = sr.ReadLine() ) != null)
            {
                Console.WriteLine(Line);
                numberoflines++;
                TenLines[x] = Line ;
                numofchars += TenLines[x].Length;
                for (int i = 0; i < TenLines[x].Length; i++)
                {
                    if (!((TenLines[x][i] >= 65 && TenLines[x][i] <= 90) || (TenLines[x][i] >= 97 && TenLines[x][i] <= 122 )))
                        numberofwords++;
                }
                numberofwords++;
                x++;
                if (x > 9)
                    x = 0;

            }
            Console.WriteLine(numofchars);
            Console.WriteLine(numberofwords);
            Console.WriteLine(numberoflines);
           
        }
        static void SearchForWord(FileStream fs,string word)
        {
            int x = 0 , numberoflines = -1;
            StreamWriter sw = new StreamWriter(fs);
            StreamReader sr = new StreamReader(fs);
            string Line = "";
            string[] TenLines = new string[10];
            while ((Line = sr.ReadLine()) != null)
            {
                TenLines[x] = Line;
                for (int i = 0; i <= TenLines[x].Length; i++)
                {
                    if (((TenLines[x][i] >= 65 && TenLines[x][i] <= 90) || (TenLines[x][i] >= 97 && TenLines[x][i] <= 122)))

                }
            }
        static void Main(string[] args)
        {
            short x = 0;
            FileStream afile = new FileStream("myfile.txt",FileMode.Open,FileAccess.ReadWrite);
            string l = "";
            Count(afile);
            Read10Lines(afile,l);
            afile.Close();
        }
    }
}
