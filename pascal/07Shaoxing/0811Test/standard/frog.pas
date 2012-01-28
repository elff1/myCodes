Program Ex;

  Const
    Int = 'frog.in';
    Out = 'frog.out';

  Var a : Int64;
      h , k , i : Integer;

Begin
  Assign(Input , Int);
  ReSet(Input);
  Assign(Output , Out);
  ReWrite(Output);
  ReadLn(h , k);
  a := 1;
  For i := 1 To h Do
    a := a * 2;
  a := a * (k + 1);
  WriteLn(a);
  Close(Input);
  Close(Output);
End.