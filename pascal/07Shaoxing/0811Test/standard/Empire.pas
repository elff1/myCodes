Program Ex;

  Const
    Int = 'Empire.in';
    Out = 'Empire.out';

  Var i , j , k , n , l , s : Longint;
      f : Array[1..200 , 1..200] Of Longint;

  Function Make(p : Longint) : Longint;
    Begin
      If odd(p) Then Make := p Else make := p - 1;
    End;

  Procedure Init;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(n , k);
      Close(Input);
      Assign(Output , Out);
      ReWrite(Output);
    End;

  Procedure Main;
    Begin
      If k = 0 Then Begin WriteLn(1);Close(Output);Halt;End;
      If k >= 2 * n - 1 Then Begin WriteLn(0);Close(Output);Halt;End;
      For i := 1 To 2 * n - 1 Do
        If odd(i) Then f[i , 1] := i Else f[i , 1] := i - 1;
      For i := 1 To 2 * n - 1 Do
        For j := 2 To i Do
          For l := 1 To i - j + 1 Do
            f[i , j] := (f[i , j] + f[i - l , j - 1] * (make(i) - j + 1)) mod 504;
    End;

  Procedure Print;
    Begin
      i := 2 * n - 1;
      If k = 1 Then
        Begin
          WriteLn((i * (i + 1) Div 2 - i div 2) mod 504);
          Close(Output);
          Halt;
        End
      Else For i := k To 2 * n - 1 Do Inc(s , f[i , k]);
      WriteLn(s mod 504);
      Close(Output);
    End;

Begin
  Init;
  Main;
  Print;
End.
