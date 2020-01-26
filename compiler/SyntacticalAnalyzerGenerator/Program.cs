using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Lekser;
using SyntacticalAnalyzerGenerator.InsertActionsInSyntax;
using SyntacticalAnalyzerGenerator.MSILGenerator;
using SyntacticalAnalyzerGenerator.Utils;
using SyntacticalAnalyzerGenerator.Words;

namespace SyntacticalAnalyzerGenerator
{
    class Program
    {
        private const string PathToLangFiles = "./LangFiles";
        private const string LangFileName = "./LangFiles/lang.txt";
        private const string LlOneLangFileName = "./InsertActionsInSyntax/llOneLang.txt";
        private const string LlOneVisualizerFileName = "./LangFiles/table.html";
        private const string LangSourceCodeFileName = "./LangFiles/input.txt";
        private const string SyntaxTableOutputFileName = "./LangFiles//table.txt";

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

        private static async Task RunAsync( )
        {
            List<Expression> expressions = LangParser.Parse( LlOneLangFileName );
            var generator = new SyntacticalAnalyzerGenerator( expressions, expressions.First().NoTerm.Name );
            List<ResultTableRow> rows = generator.Generate();

            /*using ( TextWriter tw = new StreamWriter( LlOneVisualizerFileName ) )
            {
                LlTableToHtmlVisualizer.Write( tw, rows );
            }*/

            using ( TextReader tr = new StreamReader( LangSourceCodeFileName ) )
            {
                ProgramLekser programLexer = new ProgramLekser( tr );
                var runner = new Runner(
                    programLexer,
                    new VariablesTableController(),
                    new TypeController(),
                    new AriphmeticalOperationsController(),
                    rows
                );

                var astTrees = await runner.GetTrees();
                var aSTConverter = new ASTConverter();
                var msilConstructions = aSTConverter.GenerateMSILConstructions( astTrees );

                var msilGenerator = new Generator();
                msilGenerator.Generate( msilConstructions );
                Console.WriteLine( "Ok" );
            }

            using ( TextWriter tw = new StreamWriter( SyntaxTableOutputFileName ) )
            {
                foreach ( ResultTableRow row in rows )
                {
                    tw.WriteLine( row.ToString() );
                }
            }
        }
    }
}
