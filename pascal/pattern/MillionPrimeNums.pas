PROGRAM PRIME; //����100��֮��������

const N100 : longint = 1000000;

var a0 : array [0 .. 100000] of longint;

procedure p1;
var a1 : array [1 .. 15625] of longint; // (15625 = 1000000 div 2 div 32)
    c1 : longint; //ͳ�Ʊ�ɸ��(��)���ĸ���
    n1 : longint; //�μ�ɸѡ������
    n2 : longint; //��ɸ��(��)��
    n3 : longint; //������������
    i1 : longint; //n1 div 2(n1�������������±���)
    i2 : longint; //n2 div 2(n2�������������±���)
    site : integer;//n1��n2������a1�е��±���
    mask : longint;//a1[site]������ n1��n2ʵ�ʶ�Ӧa1�е�ĳһ������λ
begin
  for i1 := 1 to 15625 do
    a1[i1] := 0;
  c1 := 0;
  n1 := 3;
  i1 := n1 shr 1;
  while n1 < 1000 do
  begin
    n2 := n1 * n1;
    n3 := n1;
    while n2 < N100 do
    begin
      i2 := n2 shr 1;
      site := i2 shr 5 + 1;
      mask := $00000001 shl (i2 and $0000001F);
      if (a1[site] and mask) = 0 then
      begin
        a1[site] := a1[site] or mask ;
        c1 := c1 + 1;
      end;
      n3 := n3 + 2;
      n2 := n3 * n1;
    end;
    repeat
    begin
      i1 := i1 + 1;
      n1 := 2 * i1 + 1;
      site := i1 shr 5 + 1;
      mask := $00000001 shl (i1 and $0000001F);
    end;
    until (a1[site] and mask) = 0;
  end;

  a0[1] := 2;
  i2 := 2;
  for i1 := 1 to 15625 do
    for site := 0 to 31 do
      if (i1 = 1) and  (site = 0) then
        continue
      else
      begin
        mask := $00000001 shl site;
        if (a1[i1] and mask) = 0 then
        begin
          a0[i2] := ((i1 - 1) shl 6) + (site shl 1) + 1;
          i2 := i2 + 1;
        end;
      end;
  a0[0] := i2 - 1;//��ȷ�����78498
end;

procedure d1;
var i1 : longint;
    f1 : text;
begin
  assign(f1,'PRIME.TXT');
  rewrite(f1);
  writeln(f1,'================100��֮��������================');
  for i1 := 1 to a0[0] do
  begin
    write(f1,a0[i1]:8);
    if i1 mod 10 = 0 then
      writeln(f1);
  end;
  writeln(f1);
  write(f1,'TOTAL:');
  writeln(f1,a0[0]);
  close(f1);
end;

BEGIN
  p1;
  d1;
END.
