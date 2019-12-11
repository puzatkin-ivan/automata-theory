using System;
using System.IO;
using System.Text;
using lr_syntactical_analyzer.Table;
using lr_syntactical_analyzer.Utils;

namespace lr_syntactical_analyzer
{
    class Program
    {
        public static void Main( string[] args )
        {
            try
            {
                Run( args );
            }
            catch ( Exception ex )
            {
                Console.WriteLine( ex.Message );
            }
        }
        
        private static void Run( string[] args )
        {
            SentencesReader reader = null;
            using ( var streamReader = new StreamReader("lang.txt", Encoding.Default ) )
            {
                reader = new SentencesReader( streamReader );
            }
            if ( !reader.Sentences.IsValid() )
                throw new ApplicationException( "Cycles exist" );
        
            FirstCreator creator = new FirstCreator( reader.Sentences );
            var lexer = new ProgramLekser( new StreamReader( "input.txt" ) );
            var runner = new Runner.Runner( lexer, creator.TableOfFirsts, creator.Sentences );
            Console.WriteLine( runner.IsCorrectSentence().Result );
        
            using ( var writer = new StreamWriter( "slr_table.html" ) )
            {
                SlrTableToHtmlVisualizer.Write( writer, creator );
            }
        }
    }
}