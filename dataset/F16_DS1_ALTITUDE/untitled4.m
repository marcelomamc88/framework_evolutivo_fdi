tiledlayout(2,1)

nexttile
plot(output_arr(:,12))
title('Original')

nexttile
plot(output_reduced(:,12))
title('With Decimate')