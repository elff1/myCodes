Program Ex2;

  Const
    Int = 'build.in';
    Out = 'build.out';

  Var a : Array[0..9] Of Longint;
      b : Array[0..9 , 0..9] Of Boolean;
      c : Array[1..30] Of Byte;
      n : Longint;
      m , len : Integer;

  Procedure Init;
    Var i , j , k : Integer;
        st : String;
    Begin
      Assign(Input , Int);
      ReSet(Input);
      ReadLn(N);
      ReadLn(m);
      Str(n , st);
      len := Length(st);
      For i := 1 To Length(st) Do
        c[i] := Ord(st[i]) - 48;
      Fillchar(b , sizeof(b) , false);
      foR I := 1 To m Do
        Begin
          ReadLn(j , k);
          b[j , k] := true;
        End;
     For k := 0 To 9 Do
       For i := 0 To 9 Do
         For j := 0 To 9 Do
           b[i , j] := b[i , j] Or (b[i , k] And b[k , j]);
      Fillchar(a , sizeof(a) , 0);
      For i := 0 To 9 Do b[i , i] := true;
      For i := 0 To 9 Do
        For j := 0 To 9 Do
          Inc(a[i] , Ord(b[i , j]));
      Close(Input);
    End;

  Procedure Print;
    Var i , s , t , j , k  , maxlen : Integer;
        ans : Int64;
    Begin
      ans := 1;
      For k := 1 To len Do
        ans := ans * a[c[k]];
      Assign(Output , Out);
      ReWrite(Output);
      Write(ans);
      Close(Output);
    End;

Begin
  Init;
  Print;
End.
