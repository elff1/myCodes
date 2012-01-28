Program Ex;

  Const
    Int = 'bracket.in';
    Out = 'bracket.out';

  Var a : Array[1..100] of Integer;
      st : String;
      n : Integer;

  Procedure Init;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(st);
      Close(Input);
    End;

  Procedure Main;
    Var i , j : Integer;
    Begin
      n := Length(st);
      For i := 1 To n Do
        a[i] := pos(st[i] , '([.])') - 3;
      j := 1;
      For i := 1 To n Do
        If (a[i]>0) Then
          If a[i] + a[j] = 0 Then
            Begin
              a[i] := 0;a[j] := 0;
              While (j > 0) And (a[j] >= 0) Do Dec(j);
            End
          Else
        Else j := i;
    End;

  Procedure Print;
    Var i : Integer;
    Begin
      Assign(Output , Out);
      ReWrite(Output);
      For i := 1 To n Do
        If a[i] = 0 Then Write(st[i])
                    Else
                      Case a[i] Of
                        -1 , 1 : Write('[]');
                        -2 , 2 : Write('()');
                      End;
      Close(Output);
    End;

Begin
  Init;
  Main;
  Print;
End.

