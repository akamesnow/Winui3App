using ConsoleApp1;
using static ConsoleApp1.Class1;

// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
Class1 testc = new Class1();
Class1 githubFileManager = new Class1();
await githubFileManager.CheckAndDownloadFiles();
