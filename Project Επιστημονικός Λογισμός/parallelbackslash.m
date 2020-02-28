function Output = parallelbackslash(p,A,b)
    I = eye(size(A));
    z = roots(p);
    d = length(z);
    [ar,~,~] = residue(1,p);
    Term = 0;
    for index = 1 : d
        s = A - z(index) * I;
        Term = Term + (ar(index) * s )\ b;
    end
    Output = Term;
end