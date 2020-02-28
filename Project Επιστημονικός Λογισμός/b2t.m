function T = b2t(M,n,m)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 13/12/2019
    VerticalIndex = 1;
    T = zeros(m,m,n,n);
    for g = 1:n
        HorizontalIndex = 1;
        for i = 1:n
            CurrentVerticalIndex = VerticalIndex;
            for j = 1:m
                CurrentHorizontalIndex = HorizontalIndex;
                for k = 1:m
                    T(k,j,i,g) = M(CurrentHorizontalIndex,CurrentVerticalIndex);
                    CurrentHorizontalIndex = CurrentHorizontalIndex + 1;
                end
                CurrentVerticalIndex = CurrentVerticalIndex + 1;
            end
            HorizontalIndex = HorizontalIndex + m;
        end
        VerticalIndex = VerticalIndex + m;
    end
    T = tensor(T);
end