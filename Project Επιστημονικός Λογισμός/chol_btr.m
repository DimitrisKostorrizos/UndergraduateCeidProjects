function Output = chol_btr(p,A,b)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 24/12/2019
    I = eye(size(A));
    z = roots(p);
    d = length(z);
    Term = 1;
    for index = 1 : d
        Coefficient = A - z(index) * I;
        Term = Coefficient * Term;
    end
    Coefficient = chol(Term);
    Output = Coefficient \ (Coefficient' \ b);
end