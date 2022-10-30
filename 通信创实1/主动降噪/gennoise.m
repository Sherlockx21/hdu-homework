function noiseout = gennoise(noisein,h,fs)
% This fucntion takes in the reference noise sample, and the h[n] to
% generate a synthesized version of noise. This noise could be realistic as to what could get added in practice
% compared to just the reference noise.
noiseout=conv(noisein, h); % Generate a synthetic noise
noiseout1=noiseout/max(abs(max(noiseout)),abs(min(noiseout))); %Normalize the magnitudes %标准化数值
audiowrite('addnoise.wav',noiseout1,fs); % Write the synthetic noise into a .wav file