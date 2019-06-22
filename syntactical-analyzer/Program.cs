using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Lekser;
using SyntacticalAnalyzerGenerator.Words;

namespace SyntacticalAnalyzerGenerator
{
    class Program
    {
        private const string LangFileName = "lang.txt";

        static void Main( string[] args )
        {
            try
            {
                RunAsync().Wait();
            }
            catch ( Exception ex )
            {
                Console.WriteLine( ex.Message );
            }
        }

        private static async Task RunAsync()
        {
            List<Expression> expressions = LangParser.Parse( LangFileName );
            var generator = new SyntacticalAnalyzerGenerator( expressions, expressions.First().NoTerm.Name );
            List<ResultTableRow> rows = generator.Generate();

            using ( TextReader tr = new StreamReader( "in.txt" ) )
            {
                var programLexer = new ProgramLekser( tr );
                var runner = new Runner( programLexer );
                var result = await runner.IsCorrectSentenceAsync( rows );
                Console.WriteLine( result );
            }

            using ( TextWriter tw = new StreamWriter( "table.txt" ) )
            {
                tw.WriteLine(String.Format("| {0,3} | {1,13} | {2,40} | {3, 5} | {4,7} | {5,5} | {6,5} | {7,5} |", "Num", "Name", "Set", "Shift", "OnError", "Stack", "GoTo", "IsEnd"));
                tw.WriteLine("------------------------------------------------------------------------------------------------------------");
                foreach ( ResultTableRow row in rows )
                {
                    tw.WriteLine( row.ToString() );
                }
            }
        }
    }
}
