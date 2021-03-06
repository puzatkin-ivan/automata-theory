﻿namespace Lekser.Enums
{
    public enum TermType
    {
        Read = 0,
        Write = 1,
        Modificator = 2,
        If = 3,
        OpeningRoundBracket = 4,
        ClosingRoundBracket = 5,
        OpeningBrace = 6,
        ClosingBrace = 7,
        While = 8,
        Do = 9,
        For = 10,
        InstructionEnd = 11,
        Int = 12,
        Char = 13,
        Bool = 14,
        Double = 15,
        OneDimensionalArray = 16,
        TwoDimensionalArray = 16,
        ThreeDimensionalArray = 16,
        Identifier = 17,
        Void = 18,
        Point = 19,
        Error = 20,
        Undefined = 21,

        BinaryWholeNumber = 22,
        OctalWholeNumber = 23,
        HexadecimalWholeNumber = 24,
        BinaryFixedPointNumber = 25,
        OctalFixedPointNumber = 26,
        HexadecimalFixedPointNumber = 27,
        BinaryFloatingPointNumber = 28,
        OctalFloatingPointNumber = 29,
        HexadecimalFloatingPointNumber = 30,
        DecimalWholeNumber = 31,
        DecimalFixedPointNumber = 32,
        DecimalFloatingPointNumber = 33,

        Plus = 34,
        Minis = 35,
        Colon = 36,
        Var = 37,
        Float = 38,
        Comma = 39,
        End = 48,
        MainTerm = 49,

        Multiple = 50,
        True = 51,
        False = 52,
        List = 53,
        Tilda = 54,
        Equally = 55,
        More = 57,
        Less = 58,
        OpeningSquareBrace = 59,
        ClosingSquareBrace = 60,
        ExclamationMark = 61,
        String = 62,

        Main = 63,
        DEnd = 64,
        Array = 65,
        Dollar = 66,

        Echo = 67,
        Echoln = 68,

        BExp = 69,
        Else = 70,


        IntArray = 1012,

        Division = 1013,
        // bool operations
        And = 1014,
        Or = 1015,
        Not = 1016,
        MoreEqual = 1017,
        LessEqual = 1018,
        Equal = 1019,
        NotEqual = 1020
    }
}
