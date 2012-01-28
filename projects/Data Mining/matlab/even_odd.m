function result=even_odd(b)
    str=num2str(b);
    len=length(str);
    last=str(len)-48;
    result=mod(last,2);
end