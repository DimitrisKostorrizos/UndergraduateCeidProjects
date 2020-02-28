function Output = serial_pcg(p,A,b)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 21/12/2019
    I = eye(size(A));
    z = roots(p);
    d = length(z);
    Term = 1;
    for index = 1 : d
        Coefficient = A - z(index) * I;
        Term = Coefficient * Term;
    end
    Output = pcg(Term,b,1e-7,50);
end