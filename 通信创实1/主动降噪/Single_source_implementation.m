clear all;close all;
[sig,fs]=audioread('sig_noise.wav'); % Reading music file with a noise
sig2=sig(1:73113,1); % Processing only first 73113 samples to reduce the time, Input to the primary channel%最大读73113，否则会报错
ylen=length(sig2);
d=500; % Large delay to make noise uncorrelated as possible
sig_del=zeros(ylen,1);
sig_del(d:ylen)=sig2(1:ylen-d+1); % Delayed signal, Input to the reference channel
e=zeros(ylen,1);w=zeros(ylen,1); w1=zeros(ylen,1); L=151; % Filter order
eta=0.00001; % Learning rate that regulates the speed and stability of adaptation
for i=L+1:ylen
e(i)=sig2(i)-transpose(sig_del(i-L+1:i))*w(i-L+1:i); %Calculation of Error%transpose为转置函数
w(i-L+2:i+1)=w(i-L+1:i)+2*eta*e(i)*sig_del(i-L+1:i); %Calculation of the Weight vector
w1(i)=transpose(sig_del(i-L+1:i))*w(i-L+1:i); % Output signal ofour code
end
subplot(411);
plot(sig2); title('Signal');
subplot(412);
plot(sig_del); title('Delayed signal');
subplot(413);
plot(e); title('Error');
subplot(414);
plot(w1); title('Restored signal');
echo on;
%complete!
echo off;
w1=w1/max(abs(max(w1)),abs(min(w1))); % Normalization of output to prevent data clipping
audiowrite('restored_johnson_w4.wav',w1,fs); % Write the output signal to the music file