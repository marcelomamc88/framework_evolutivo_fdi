w = ans.simout_arr(:,1);
w_hat_cheb = decimate(w, 100);
w_hat_ham = decimate(w, 100, 'fir');

tiledlayout(3,1)

nexttile
plot(w)
title('Original')

nexttile
plot(w_hat_cheb)
title('With Decimate - lowpass Chebyshev Type I - infinite impulse response (IIR)')

nexttile
plot(w_hat_ham)
title('With Decimate - Hamming window -  finite impulse response (FIR)')
