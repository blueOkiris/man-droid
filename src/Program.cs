using System;
using System.Diagnostics;
using Google.Cloud.Speech.V1;

namespace mandroid {
    class Program {
        static void Main(string[] args) {
            if(args.Length < 1) {
                Console.WriteLine(
                    "This application requires Google's Speech to Text API"
                );
                Console.WriteLine(
                    "Please provide the JSON file with your credentials as"
                    + " and argument"
                );
            } else if(args.Length > 1) {
                Console.WriteLine("Too many arguments provided!");
            }

            var credentiaFileName = args[0];
            Process.Start(
                "export GOOGLE_APPLICATION_CREDENTIALS=" + credentiaFileName
            );

            var speech = SpeechClient.Create();
        }
    }
}
