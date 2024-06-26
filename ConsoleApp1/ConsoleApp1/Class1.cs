﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public class Class1
    {
        public async Task CheckAndDownloadFiles()
        {
            string githubUrl = "https://github.com/akamesnow/Winui3App/blob/main/ConsoleApp1/ConsoleApp1/bin/Release/net7.0/ConsoleApp1.exe"; // Remplacez les valeurs par les vôtres
            Version requiredVersion = new Version(1, 0, 0, 0); // Version requise

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    HttpResponseMessage response = await client.GetAsync(githubUrl);

                    if (response.IsSuccessStatusCode)
                    {
                        byte[] fileBytes = await response.Content.ReadAsByteArrayAsync();

                        // Récupération des informations de version du fichier .exe
                        FileVersionInfo versionInfo = FileVersionInfo.GetVersionInfo("ConsoleApp1.exe");
                        Version fileVersion = new Version(versionInfo.FileVersion);

                        // Comparaison de la version requise avec la version du fichier .exe
                        if (fileVersion >= requiredVersion)
                        {
                            // Télécharger d'autres fichiers ou effectuer d'autres actions
                            Console.WriteLine("La version du fichier .exe est conforme aux exigences.");
                        }
                        else
                        {
                            Console.WriteLine("La version du fichier .exe ne répond pas aux exigences.");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Erreur lors de la récupération du fichier. Statut de réponse : {response.StatusCode}");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Une erreur s'est produite : {ex.Message}");
                }
            }
        }
    }
}
