Program Ex11;

  Const
    Int = 'encode.in';
    Out = 'encode.out';

  Var word : String[7];
      i , j , len , ans : Longint;

  Function jisuan(n : Longint;r : Longint) : Longint;
    Var i , t : Longint;
    Begin
      t := 1;
      For i := 1 To r Do
        t := t * (n + 1 - i) Div i;
      jisuan := t;
    End;

  Procedure Init;
    Begin
      Assign(Input , Int);
      Assign(Output , Out);
      ReSet(Input);
      ReWrite(Output);
      ReadLn(Word);
      Close(Input);
    End;

  Procedure main;
    Begin
      word := pred('a') + word;
      len := Length(word) - 1;
      ans := 1;
      For i := 2 To len Do
        ans := ans + jisuan(26 , i - 1);
      For i := 2 To len + 1 Do
        If (word[i] > Word[i - 1]) Then
          For j := Ord(Word[i - 1]) + 1 To Ord(Word[i]) - 1 Do
            ans := ans + jisuan(26 - j + Ord(word[1]) , len - i + 1)
	Else Begin
	       ans := 0;
               Break;
             End;
      WriteLn(ans);
      Close(Output);
    End;

Begin
  Init;
  Main;
End.
