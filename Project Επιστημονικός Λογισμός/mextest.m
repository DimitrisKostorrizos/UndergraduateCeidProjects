function C = mextest
    m = 100;
    n = 100;
    C = kron(eye(n),toeplitz ([30 -16 1 zeros(1,m - 3)])) + kron(toeplitz ([24 -12 zeros(1,n-2)]),eye(m));
%     n = 1000;
%     C = zeros(n);
%     theta = 0.5;
%     for i = 1:n
%         for j = 1:n
%             if i == j
%                C(i,j) = 1 + i ^ theta;
%             else
%                 C(i,j) = 1/(abs(i - j) ^ 2);
%             end
%         end
%     end
end