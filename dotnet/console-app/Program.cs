using System;

namespace console_app
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Hello World!");
			var result = PopplerNative.testingStrings("hellp");
			Console.WriteLine(result);
			return;
		}
	}
}
