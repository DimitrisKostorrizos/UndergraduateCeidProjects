function [dflag ,discrC,discrR] = dd_check(A)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 10/12/2019
    discrR = zeros(1, size(A,1));
    discrC = zeros(1, size(A,1));
    for i = 1 : size(A,1)
        discrR(i) = 2 * abs(A(i,i)) - sum(abs(A(i,:)));
        discrC(i) = 2 * abs(A(i,i)) - sum(abs(A(:,i)));
    end
    mdiscrR = min(discrR);
    mdiscrC = min(discrC);
    discrR = max([0, mdiscrR]);
    discrC = max([0, mdiscrC]);
    if(mdiscrR >= 0 && mdiscrC >= 0)
        dflag = 1;
    else
        dflag = 0;
    end
end