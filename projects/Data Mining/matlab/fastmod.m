function result=fastmod(a,b,c)
    if b==0
        result=1;
    else if b==1
            result=mod(a,c);
        end      
    end
    if b>=2
        if mod(b,2)==1
            b1=floor(b/2);
            b2=b-b1;
            result=fastmod(a,b1,c)*fastmod(a,b2,c);
            result=mod(result,c);
        else 
            result=fastmod(a,b/2,c)*fastmod(a,b/2,c);
            result=mod(result,c);
        end
    end
    
end