Program Ex;

  Const
    Int = 'sort.in';
    Out = 'sort.out';

  Var n , k : Longint;

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
    Var a : Array[0..31] Of Longint;
        b : Array[1..31] Of Integer;
        i , j : Longint;
    Begin
      a[n] := 1;a[0] := 1;
      For i := n - 1 Downto 1 Do
        a[i] := a[i + 1] * 2;
      i := 0;j := 1;
      While k > 1 Do
        Begin
          While (i <= n) And (k > a[i]) Do Begin
            k := k - a[i];
            i := i + 1;
          End;
          If j <> 1 Then Write(' ');
          j := j + 1;
          Write(i);
          a[i] := 1;
        End;
      If i = 0 Then WriteLn(0);
      Close(Output);
    End;

Begin
  Init;
  Main;
End.
