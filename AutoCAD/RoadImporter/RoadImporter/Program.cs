using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Configuration;
using System.Linq;

namespace RoadImporter
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main(string[] aParams)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            if (aParams.Count() == 0)
                _Settings = GetSettings();
            else
                _Settings = new ImporterSettings(aParams);

            if (_Settings.Operation == ImporterOperation.ToXML)
                Application.Run(new FrmMoveToXML());
            else
                Application.Run(new FrmMoveToDB());
        }

        private static ImporterSettings _Settings;
        public static ImporterSettings GetSettings()
        { 
            if (_Settings == null)
                _Settings = new ImporterSettings(
                    ConfigurationManager.ConnectionStrings["DBConnection"].ConnectionString,
                    490,
                    4083,
                    ConfigurationManager.AppSettings["Operation"]
                );

            return _Settings;
        }
    }
}
