﻿
using System;
using System.Collections.Generic;
using System.Linq;
using Lekser.Enums;

namespace SyntacticalAnalyzerGenerator.Words
{
    public class ResultTableRow
    {
        public int N { get; set; }
        public string Name { get; set; }
        public TermType? TermType { get; set; }
        public HashSet<TermType> DirectingSet { get; set; }
        public bool IsShift { get; set; } = false;
        public int ShiftOnError { get; set; } = -1;
        public bool IsPushToStack { get; set; } = false;
        public int GoTo { get; set; }
        public bool IsEnd { get; set; } = false;

        public override string ToString()
        {
            return String.Format("| {0,3} | {1,13} | {2,40} | {3, 5} | {4,7} | {5,5} | {6,5} | {7,5} |", N, Name, SetToString(), IsShift, ShiftOnError, IsPushToStack, GoTo, IsEnd);
        }

        private string SetToString()
        {
            var result = "";
            foreach ( var direct in DirectingSet )
            {
                result += direct.ToString() + " ";
            }

            return string.Join( ", ", DirectingSet.ToArray() );
        }
    }
}
