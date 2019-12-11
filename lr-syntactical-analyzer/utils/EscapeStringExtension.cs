using System.Web;

namespace lr_syntactical_analyzer.Utils
{
    public static class EscapeStringExtension
    {
        public static string GetEscaped( this string text )
        {
            return HttpUtility.HtmlEncode( text );

        }
    }
}
