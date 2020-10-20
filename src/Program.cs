using System;

namespace mandroid {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Initializing the Mandroid...");

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

            Console.WriteLine("Testing pwm...");
            var light = new PwmPin(PinName.PwmP9_22, 500000000, 1000000000);
            light.Init();
            light.On();
            Console.Write("Press enter to end...");
            light.DeInit();
        }
    }
}
