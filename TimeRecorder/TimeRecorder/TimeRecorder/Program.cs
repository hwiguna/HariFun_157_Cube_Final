using System;
using System.IO;

namespace TimeRecorder
{
    class Program
    {
        static void Main(string[] args)
        {
            string recording = string.Empty;
            DateTime beginningOfTime = DateTime.MinValue;
            bool letsQuit = false;
            do
            {
                var keyInfo = Console.ReadKey();
                if (keyInfo.Key == ConsoleKey.Escape)
                {
                    Console.Write("\nSave as filename: ");
                    string path = Console.ReadLine();
                    if (string.IsNullOrWhiteSpace(path)) path = "output";
                    if (!path.ToLower().EndsWith(".txt")) path += ".txt";
                    File.WriteAllText(path, recording);

                    letsQuit = true;
                }
                if (string.IsNullOrEmpty(recording))
                    beginningOfTime = DateTime.Now;

                // Each line is in this format: { timeStamp, char pressed },
                string line = $"{{{(long)(DateTime.Now - beginningOfTime).TotalMilliseconds},{(int)keyInfo.KeyChar}}},{Environment.NewLine}";

                var timeStamp = DateTime.Now;
                recording = string.Concat(recording, line);

            } while (!letsQuit);
        }
    }
}
