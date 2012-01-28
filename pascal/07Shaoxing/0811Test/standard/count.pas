Program Ex;

  Const
    Int = 'count.in';
    Out = 'count.out';

  Var n : Longint;
      len , i : Integer;
      a  , c : Array[0..9] Of Longint;
      b : Array[1..9] Of Byte;

  Procedure Init;
    Var st : String;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(n);
      Str(n , st);
      len := Length(st);
      For i := 1 To len Do
        b[len - i + 1] := Ord(st[i]) - Ord('0');
      Close(Input);
    End;

  Procedure Main;
    Var i , j , k : Longint;
    Begin
      Fillchar(a , sizeof(a) , 0);
      c[0] := 0;c[1] := 1;
      For i := 2 To 9 Do c[i] := c[i - 1] * 10;
      For i := len Downto 1 Do
        Begin
          For j := 0 To 9 Do
            a[j] := a[j] + c[i - 1] * (i - 1) * b[i];
          For j := 0 To b[i] - 1 Do
            a[j] := a[j] + c[i];
          a[b[i]] := a[b[i]] + n mod c[i] + 1;
        End;
      For i := 1 To Len Do a[0] := a[0] - c[i];
    End;

  Procedure Print;
    Begin
      Assign(Output , Out);
      ReWrite(Output);
      For i := 0 To 9 Do WriteLn(a[i]);
      Close(Output);
    End;

Begin
  Init;
  Main;
  Print;
End.
