using System;
using System.IO;
using System.Linq;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace PDFBinder
{

    class Program
    {
        public static String logfile = "pdfbinder.log";
        public static String lineSeparator = "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";

        public static void Logger(String lines)
        {
            // Write the string to a file.append mode is enabled so that the log
            // lines get appended to  test.txt than wiping content and writing the log
            using (StreamWriter file = new StreamWriter(logfile, true))
            {
                file.WriteLine(lines);
                Console.WriteLine(lines);                
            }
        }

        static void Main(string[] args)
        {
            bool errorWas = false;
            Logger(lineSeparator);
            Logger("PDFBinder | mmailm@mail.ru");
            Logger("Запуск от " + DateTime.Now.ToString());
            Logger(lineSeparator);
            if (args.Length > 0)
            {
                Logger(String.Join(" ", args));
            }
            else
            {
                Logger("Запуск без параметров");
            }

            if (args.Length < 2)
            {
                errorWas = true;
                
                Logger("Формат ввода:\n" +
                       "\n    target_file source_file1 [source_file2 source_file3 ...]" +
                       "\n\nимена файлов рекомендуется передавать в \"кавычках\"");
                Logger(lineSeparator);
            } else {
                var targetPDF = args[0];

                using (FileStream stream = new FileStream(targetPDF, FileMode.Create))
                {
                    Document pdfDoc = new Document();
                    PdfCopy pdf = new PdfCopy(pdfDoc, stream);

                    pdfDoc.Open();

                    foreach (var fileName in args.Skip(1))
                    {
                        try
                        {
                            pdf.AddDocument(new PdfReader(fileName));
                        }
                        catch (Exception e)
                        {
                            errorWas = true;
                            Logger(lineSeparator);
                            Logger(e.Message);
                            Logger("StackTrace:");
                            Logger(e.StackTrace);
                            Logger(lineSeparator);
                        }
                    }

                    if (pdfDoc != null)
                    {
                        pdfDoc.Close();
                    }
                }

                if (!errorWas)
                {
                    // если не было ошибок удаляем лог файл
                    File.Delete(logfile);
                }
                else
                {
                    // а если были то не будем закрывать окно
                    // чтобы пользователь мог прочитать об ошибке
                    Console.ReadKey();
                }
            }
        }
    }
}
