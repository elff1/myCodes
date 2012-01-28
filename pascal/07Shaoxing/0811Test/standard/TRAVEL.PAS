Program Ex1;

  Const
    Int ='travel.in';
    Out ='travel.out';

  Var total , i , m : Longint;
      pre , last : String;

  Procedure Init;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(pre);
      ReadLn(last);
      Close(Input);
    End;

  Procedure Main;
    Begin
      total := 1;
      For i := 1 To Length(pre) - 1 Do
        Begin
          m := Pos(pre[i] , last);
          If (m > 1) and (pre[i + 1] = last[m - 1]) Then total := total * 2;
        End;
    End;

  Procedure Print;
    Begin
      Assign(Output , Out);
      ReWrite(Output);
      WriteLn(total);
      Close(Output);
    End;

Begin
  Init;
  Main;
  Print;
End. 	
	
