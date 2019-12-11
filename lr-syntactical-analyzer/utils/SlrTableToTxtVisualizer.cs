using System.IO;
using System.Text;
using lr_syntactical_analyzer.Table;

namespace lr_syntactical_analyzer.Utils
{
    public static class SlrTableToTxtVisualizer
    {
        public static void Write( TextWriter writer, FirstCreator firstCreator )
        {
            var result = GetBody( firstCreator );
            writer.Write( result );
        }

        private static string GetBody( FirstCreator firstCreator )
        {
            var tableOfFirsts = firstCreator.TableOfFirsts;
            var resultBuilder = new StringBuilder();

            foreach ( Sentence item in firstCreator.Sentences )
            {
                resultBuilder.Append(item.ToString().GetEscaped());
                resultBuilder.Append("\n");
            }

            foreach ( var str in tableOfFirsts.Column )
            {
                resultBuilder.Append( $"| { str.GetEscaped() }" );
            }
            resultBuilder.Append( "|" );

            resultBuilder.Append( '\n' );

            for ( var i = 0; i < tableOfFirsts.Row.Count; ++i )
            {
                resultBuilder.Append( "<tr>" );
                resultBuilder.Append( "<td style=\"border:1px solid;\">" );
                foreach ( var x in tableOfFirsts.Row[ i ].Values )
                {
                    resultBuilder.Append( $"{ x.Value.GetEscaped() }<span style=\"font-size: 10px;\">{x.RowIndex},{x.ColIndex}</span> " );
                }
                resultBuilder.Append( "</td>" );
                foreach ( var item in tableOfFirsts.Table[ i ] )
                {
                    resultBuilder.Append( "<td style=\"border:1px solid;\">" );
                    if ( item != null )
                    {
                        foreach ( var token in item.Values )
                        {
                            resultBuilder.Append( $"{ token.Value.GetEscaped() }<span style=\"font-size: 10px;\">{token.RowIndex},{token.ColIndex}</span> " );
                        }
                    }

                    resultBuilder.Append( "</td>" );
                }

                resultBuilder.Append( "</tr>" );
            }

            resultBuilder.Append( "</table>\n" );
            resultBuilder.Append( "</body>\n" );
            return resultBuilder.ToString();
        }
    }
}
