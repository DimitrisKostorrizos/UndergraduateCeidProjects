function Output = serial_backslash(p,A,b)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 17/12/2019
    I = eye(size(A));
    z = roots(p);
    d = length(z);
    Term = 1;
    for index = 1 : d
        Coefficient = A - z(index) * I;
        Term = Coefficient * Term;
    end
    Output = Term \ b;
end