Program Peng;

  Const
    Int = 'hanoi.in';
    Out = 'hanoi.out';
    s : String[3]='ABC';

  Type
    arr = Array[1..64] of Byte;

  Var sou,tar : arr;
      n : Byte;
      count : Longint;


  Procedure Init;
  Var
      i,j,k,x : Longint;

    Begin
      Assign(Input , Int);
      ReSet(Input);
      Readln(n);
      For i := 1 To 3 Do
        Begin
  	  Read(k);
  	  For j := 1 To k Do
    	    Begin
  	      Read(x);
	      sou[x]:=i;
	    End;
	End;
      For i := 1 To 3 Do
        Begin
          Read(k);
          For j := 1 To k Do
            Begin
 	      Read(x);
	      tar[x]:=i;
            End;
        End;
      Close(Input);
    End;


  Procedure Move(k : Longint;  w : Byte);
  Var
      i,j : Longint;
    Begin
      If sou[k]=w then Exit;
      j:=6 - sou[k] - w;
      For i := k - 1 Downto 1 Do Move(i,j);
      Writeln('move ',k,' from ',s[sou[k]],' to ',s[w]);
      sou[k]:=w;
      Inc(count);
    End;

  Procedure Main;
  Var
    i : Longint;
   Begin
     Assign(Output , Out);
     ReWrite(Output);
     For i:=n Downto 1 Do
       Move(i,tar[i]);
     Writeln(count);
     Close(Output);
   End;

Begin
  Init;
  Main;
End.

