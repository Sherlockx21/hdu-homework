function [sig_noise,fs_sig,ref_noise]=sig_plus_noise(sigfile,noisefile)

% [ref_sig,fs_sig,nbits_sig]=audioread(sigfile); % Read the pure signal to be added
[ref_sig,fs_sig]=audioread(sigfile,[1,73113]); 

% [ref_noise,fs_noise,nbits_noise]=audioread(noisefile); % Read the reference noise
[ref_noise,fs_noise]=audioread(noisefile,[1,73113]); % Read the reference noise
%%% ref_noise = randn(size(ref_noise));
h=[0.2 0.5 -0.7 0.9 1 1.5 2 1.3 5];
%h=input('Enter the h[n] for generating noise: '); % Get the h[n] from user
add_noise=gennoise(ref_noise,h,fs_noise);

sig_noise_len=min(length(add_noise),length(ref_sig)); % Get the length of the larger of the two files to be mixed
sig_noise=zeros(sig_noise_len,1); % Put place-holder zeros
sig_noise= (ref_sig(1:sig_noise_len)+ add_noise(1:sig_noise_len)); %Mix the two files
% wavwrite(sig_noise,fs_sig,nbits_sig,'sig_noise.wav'); % Write signal mixed with noise output to the music file
audiowrite('sig_noise.wav',sig_noise,fs_sig); 
