% Two Channel implementation of the LMS algorithm
clear all;close all;
sigfile='music.wav';%'audio_s.wav'; % Read the recorded signal
noisefile='noise0.wav'; % Read the recorded noise
[sig_noise,fs_sig,refnoise]=sig_plus_noise(sigfile,noisefile); % Generate a synthetic noise from this reference noise,
                                                                         % mix it with signal, and return the mixed file
file_len=length(sig_noise); % Length of the file
L=10;
e=zeros(file_len,1); % Put place-holder zeros for error vector
w=zeros(L,1); % Put place-holder zeros for weight vector
eta=0.001;
for i=L+1:file_len
e(i)=sig_noise(i)-refnoise(i-L+1:i)'*w; % Calculation of Error vector
w=w+2*eta*e(i)*refnoise(i-L+1:i); % Calculation of the Weight vector
end
subplot(411);
[ref_sig,fs_sig]=audioread(sigfile); 
plot(ref_sig); title('Signale');
axis([0 80000 -1 1]);
subplot(412);
plot(sig_noise); title('Signal plus noise');
subplot(413);
plot(refnoise); title('Reference noise');
subplot(414);
plot(e); title('Reconstructed output');
axis([0 80000 -1 1]);
echo on;
audiowrite('Reconstructed_sig.wav',e,fs_sig); 

