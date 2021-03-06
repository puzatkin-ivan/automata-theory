﻿using System.Collections.Generic;
using Lekser.Enums;

namespace SyntacticalAnalyzerGenerator.Words
{
    public partial class Word
    {
        public const string Epsilant = "[EPS]";
        public const string Identifier = "#IDENTIFIER#";
        public const string End = "[END]";
        public const string DecimalWholeNumber = "#DecimalWholeNumber#";
        public const string BinaryWholeNumber = "#BinaryWholeNumber#";
        public const string DecimalFixedPointNumber = "#DecimalFixedPointNumber#";
    }

    public partial class Word
    {
        public string Name { get; set; }
        public string ActionName { get; set; }
        public TermType? TermType { get; set; } = null;
        public WordType Type { get; set; }
        public HashSet<TermType> DirectingSet { get; set; }
    }
}
