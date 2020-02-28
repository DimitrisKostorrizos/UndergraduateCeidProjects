function Output = explicit(p,A,b)
    b = polyval_MV(p,A,b);
    C = polyval(p,A);
    Output = C \ b;
end