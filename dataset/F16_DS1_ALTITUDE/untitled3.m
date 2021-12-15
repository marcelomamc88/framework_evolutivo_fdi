factor = 100;

y = output_arr(:,1).';

read_1 = decimate(output_arr(:,1), factor,'fir');
%read_1 = nanmean(reshape([y(:); nan(mod(-numel(y),factor),1)],factor,[])).';

output_reduced = zeros(size(read_1, 1), 25);
output_reduced(:,1) = read_1;

for i=2:size(output_arr,2)
    output_reduced(:,i) = decimate(output_arr(:,i), factor,'fir');
    %y = output_arr(:,i).';
    %output_reduced(:,i) = nanmean(reshape([y(:); nan(mod(-numel(y),factor),1)],factor,[])).';
end
