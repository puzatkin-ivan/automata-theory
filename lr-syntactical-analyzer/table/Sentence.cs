﻿using System.Collections.Generic;
using System.Linq;

namespace lr_syntactical_analyzer.Table
{
    public sealed class Sentence
    {
        /// <summary>
        /// left side of sentence
        /// </summary>
        public string MainToken { get; set; }

        /// <summary>
        /// right side of sentence
        /// </summary>
        public List<Token> Tokens { get; set; }

        public Sentence( string main, List<Token> tokens )
        {
            Tokens = tokens;
            MainToken = main;
        }

        public Sentence( string main, Token[] tokens )
        {
            Tokens = new List<Token>( tokens );
            MainToken = main;
        }

        public Token GetByIndexes(int i, int j)
        {
            return Tokens.FirstOrDefault( t => t.RowIndex == i && t.ColIndex == j );
        }

        public override string ToString()
        {
            return $"{MainToken} -> {TokensToString()}";
        }

        private string TokensToString()
        {
            return string.Join( " ", Tokens.Select( w => w.Value ) );
        }
    }
}
