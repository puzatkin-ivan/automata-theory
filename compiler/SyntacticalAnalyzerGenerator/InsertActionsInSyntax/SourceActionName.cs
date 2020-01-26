﻿namespace SyntacticalAnalyzerGenerator.InsertActionsInSyntax
{
    public static class SourceActionName
    {
        public const string VtcCreateTable = "CreateTable";
        public const string VtcDefineNewType = "DefineNewType";
        public const string VtcDefineIdentifier = "DefineIdentifier";
        public const string VtcDestroyLastTable = "DestroyLastTable";
        public const string VtcGetTerm = "GetVariable";

        public const string TcSaveLastTerm = "SaveLastTerm";
        public const string TcCheckLeftRight = "CheckLeftRight";
        public const string TcSaveLeftTerm = "SaveLeftTerm";
        public const string TcSaveRightTerm = "SaveRightTerm";
        public const string TcDefineArrElemType = "DefineArrElemType";

        public const string CommonIsIntIndex = "IsIntIndex";
        public const string CommonCheckRightValueDestination = "CheckRightValueDestination";

        public const string AoActionAfterNumber = "ActionAfterNumber";
        public const string AoActionAfterSign = "ActionAfterSign";
        public const string AoActionAfterOperation = "ActionAfterOperation";
        public const string AoCreateUnaryMinusNode = "ActionCreateUnaryMinusNode";
        public const string UnaryMinusFound = "UnaryMinusFoundAction";
        public const string AoOpenBracketFound = "OpenBracketFound";
        public const string AoClosedBracketFound = "ClosedBracketFound";

        public const string AoClear = "Clear";

        public const string EchoGenerateNode = "GenerateNode";
        public const string EchoSave = "Save";

        public const string ReadGenerateNode = "GenerateNode";
        public const string ReadSave = "Save";

        public const string BoActionAfterBoolValue = "ActionAfterBoolValue";
        public const string BoActionAfterCompOperation = "ActionAfterCompOperation";
        public const string BoActionAfterCompSign = "ActionAfterCompSign";
        public const string BoActionAfterLogicSign = "ActionAfterLogicSign";
        public const string BoUnaryNotSignFound = "UnaryNotSignFound";
        public const string BoOpenBracketFound = "OpenBracketFound";
        public const string BoClosedBracketFound = "ClosedBracketFound";

        public const string IFAddIfTerm = "AddIf";
        public const string IFAddThenBegin = "AddThenBegin";
        public const string IFAddThenEnd = "AddThenEnd";
        public const string IFAddElseBegin = "AddElseBegin";
        public const string IFAddElseEnd = "AddElseEnd";

        public const string WhileAddWhile = "AddWhile";
        public const string WhileAddWhileEnd = "AddWhileEnd";
    }
}
