Program Ex4;

  Const
    Int = 'stack.in';
    Out = 'stack.out';

  Var a : Array[1..10000] Of Longint;
      n , i , j , k , top , t : Longint;

  Procedure Init;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(n);
      Close(Input);
    End;

  Procedure Main;
    Begin
      Fillchar(a , sizeof(a) , 0);
      a[1] := 1;top := 1;
      For i := 2 * n Downto n + 2 Do
        Begin
          For j := 1 To top Do
            a[j] := a[j] * i;
          For j := 1 To top + 4 Do
            Begin
              a[j + 1] := a[j + 1] + a[j] div 10;
              a[j] := a[j]  mod 10;
            End;
          top := top + 5;
          While a[top] = 0 Do Dec(top);
        End;
        For i := n Downto 2 Do
          Begin
            t := 0;
            For j := top Downto 1 Do
              Begin
                k := a[j];
                a[j] := (k + t * 10) Div i;
                t := (k + t * 10) mod i;
              End;
            While a[top] = 0 Do Dec(top);
          End;
    End;

  Procedure Print;
    Begin
      Assign(Output , Out);
      ReWrite(Output);
      For i := top Downto 1 Do Write(a[i]);
      WriteLn;
      Close(Output);
    End;

Begin
  Init;
  Main;
  Print;
End.