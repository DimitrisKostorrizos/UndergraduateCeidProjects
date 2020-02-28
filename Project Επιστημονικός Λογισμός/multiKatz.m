function [katzCentrality] = multiKatz(A,alpha,mth,pcg_params)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 29/12/2019
    amax = 0.04;
    I = eye(size(A,1));
    e = ones(size(A,1),1);
    index = 0;
    a = alpha(1);
    katzCentrality = zeros(size(A,1),size(alpha,2));
    if(mth == "pcg" && length(pcg_params) ~= 4)
        pcg_params = [pcg_params, cell(1,4 - length(pcg_params))];
    end
    while (a <= amax && index < length(alpha))
        index = index + 1;
        a = alpha(index);
        if (mth == "direct")       
            katzCentrality(:,index) = (I - a * A) \ e;
        else
            if(mth == "pcg")
                katzCentrality(:,index) = pcg((I - a * A),e,pcg_params{1},pcg_params{2},pcg_params{3},pcg_params{4});
            else
                error("Invalid mth. Value of mth must be either direct or pcg.");
            end
        end
    end
end