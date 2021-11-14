% PROGRAMMA Equalizzatore (per il progetto da 1 credito)
% Autore: Leticia Bochko
% Politecnico di Milano, 21 Luglio 2020
clear 
close all
clc
%----------------------------------------------------------------------------
% Esegue la registrazione e il campionamento (f di campionamento = Fs)
% di un segnale audio in ingresso dal microfono del PC. 
% Visualizza sia il segnale campionato sia la sua trasformata di Fourier.
% Ricostruisce il segnale tempo continuo a partire dal segnale campionato e lo
% riproduce tramite altoparlanti del PC.
% Passa il segnale attraverso un banco di 5 filtri (passa basso, 3 passa
% banda e passa alto).
% Moltiplica i segnali in uscita da ciascun filtro per
% un coefficiente 0<a<1.
% Somma i segnali così modificati per ottenere un segnale discreto
% modificato in uscita.
% Ricostruisce il segnale tempo continuo a partire dal segnale discreto
% modificato e lo riproduce tramite gli altopralanti del PC.
% Visualizza il segnale modificato e la sua trasformata di Fourier per
% confrontare questi con i grafici del segnale originale


% Ho fatto diverse prove e c'era un parziale miglioramento alle fs tra
% 15000 e 40000, che prontamente svaniva dopo che testavo di nuovo, per sicurezza, la fs
% scelta. Ho notato che questo accadeva perché il mio pc
% tendeva a scegliere i valori "casuali" di 'a' molto vicini a 1, quindi il
% segnale modificato era molto vicino all'originale. Ho quindi con altre
% prove visto che i valori di 'a' che ora ho impostato manualmente fanno
% meglio vedere e sentire l'effetto dell'equalizzatore, anche a fs elevate


Fs=40000;   %frequenza di campionamento 
Nbit=16;    %numero bit con cui rappresento ogni campione 
Ch=1;       %numero di canali (mono/stereo)
T=10;       %tempo di registrazione
N=Fs*T;     %numero dei campioni
t=(0:1/Fs:T-1/Fs);
myVoice = audiorecorder(Fs,Nbit,Ch);


%registrazione
disp('Return to start ...');
pause
disp('Start speaking to record the input signal.');
recordblocking(myVoice, T);
disp('End of recording.');


%rappresentazione del brano registrato
disp('Return to display the input signal ...');
pause

G=3*10000/Fs;
figure(1)

x = getaudiodata(myVoice);
plot(t,x)
xlabel('Time seconds')
title('Recorded Signal')

disp('Return to display FFT of the input signal...');
pause
X=fft(x);
f=(-Fs/2:Fs/N:Fs/2-Fs/N);
figure(2)
plot(f,fftshift(abs(X)))
xlabel('Frequency Hz')
title('Fourier T. Abs Value')


%riascolto il brano
disp('Return to playback the original input signal ...');
pause

myVoice=audioplayer(x*G,Fs);
play(myVoice);
pause(T)



%banco dei filtri
N=256; %lunghezza risposta in impulso


h1=fir1(N, .2); %passa basso
h2=fir1(N, [.2 .4]); %passa banda
h3=fir1(N, [.4 .6]);
h4=fir1(N, [.6 .8]);
h5=fir1(N, .8, 'high'); %passa alto


H1=fft(h1);
H2=fft(h2);
H3=fft(h3);
H4=fft(h4);
H5=fft(h5);


disp('Return to display the filters ...');
pause
figure(3)
    plot((0:N), abs(H1))
    hold on
    plot((0:N), abs(H2), 'r')
    plot((0:N), abs(H3), 'g')
    plot((0:N), abs(H4), 'y')
    plot((0:N), abs(H5), 'c')
    plot((0:N), abs(H1)+abs(H2)+abs(H3)+abs(H4)+abs(H5), 'm')
    axis([0 N -.5 1.5])
    hold off
    
    
    
%sommare i componenti modificati del segnale
a1=0.4; % oppure rand per generare un numero casuale tra 0 e 1
a2=0.38;
a3=0.76; 
a4=0.77;
a5=0.19;

x1=conv(x,a1*h1);
x2=conv(x,a2*h2);
x3=conv(x,a3*h3);
x4=conv(x,a4*h4);
x5=conv(x,a5*h5);


xMod=(x1+x2+x3+x4+x5); %segnale discreto modificato


disp('Return to playback modified signal ...');
pause

xContMod=audioplayer(xMod*G*3,Fs); %segnale continuo modificato
play(xContMod)
pause(T)


%rappresentazione segnale modificato
disp('Return to display modified signal...');
pause

figure(1)
hold on
plot(t,xMod(1:length(t)),'r')
xlabel('Time seconds')
title('Modified Signal')
hold off

figure(2)
hold on
disp('Return to display FFT of modified signal...');
pause
XMOD=fft(xMod(1:length(t)));
plot(f,fftshift(abs(XMOD)),'r')
xlabel('Frequency Hz')
title('Fourier T. Abs Value')
hold off
