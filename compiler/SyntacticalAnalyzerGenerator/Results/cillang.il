//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.0.30319.1

// Metadata version: v4.0.30319
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
.assembly program
{
  .custom instance void [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = ( 01 00 08 00 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                             63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.
  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
.module program.exe
// MVID: {304BE092-B12B-479A-A5B9-68902DA41433}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000001    //  ILONLY
// Image base: 0x04B30000
.method static void main()
{
.entrypoint
.locals init (int32 lhs)
.locals init (int32 rhs)
ldc.i4 10
stloc lhs
ldc.i4 20
stloc rhs
ldloc lhs
ldloc rhs
add
stloc lhs
ldloc lhs
call void [mscorlib]System.Console::WriteLine(int32)

ret
}
