% PROGRAMMA: Semplice sistema di comunicazione
% 097460 - Prova finale (Sistemi di Comunicazione)
% Autore: Leticia Bochko
%(il file include funzioni prese dal materiale didattico del corso)
% Politecnico di Milano, a.a. 2021-2022

clc, clear, close all

%% TRASMETTITORE
%trasmissione in banda base sul binario antipodale (2-PAM).

%ingresso dati binari
%generazione di numeri interi pseudo-casuali tra 0 e 1
num_bit_ingresso = single(16000);  
bit_ingresso = single(randi([0, 1], [1, num_bit_ingresso]));%il segnale in ingresso

N_sample_per_symbol=64;
Rs=10e9;   % symbol rate [Baud - symbols/s]
Ts=1/Rs;   % symbol time [s]

window_length=num_bit_ingresso*Ts;
df=1/window_length;   % passo (risoluzione) spettrale [Hz]
dt=Ts/N_sample_per_symbol;  %time step, passo/risoluzione temporale (tempo per ogni campione) [s]
N_sample=num_bit_ingresso*N_sample_per_symbol; %numero totale dei campioni
f_sample=1/dt; %frequenza di campionamento [Hz]

t=[0:N_sample-1]*dt; %vettore degli istanti di tempo [s]

y=zeros(size(t));

%generatore sequenza impulsiva
%ampiezza +1 se bit trasmesso==1; -1 se bit trasmesso==0
for c = 1:(num_bit_ingresso) 
    if bit_ingresso(c)==1
        y(32+64*(c-1))=1;   
    else
        y(32+64*(c-1))=-1;
    end
end


figure('Name',' Segnale in ingresso rappresentato come sequenza impulsiva')
plot(t,y), xlabel('tempo [s]'), ylabel('sequenza impulsiva'), grid on

%per teorema di Nyquist, possiamo rappresentare correttamente segnali
%campionati a f_sample solo se la banda del segnale è compresa tra 
% -f_sample/2 e +f_sample/2

% vettore dei campioni di frequenza (rappr. bilatera - condizioni al bordo periodiche)
f=[-f_sample/2:df:+f_sample/2-1];

%trasformata di Fourier di sequenza impulsiva
Y=fftshift(fft(fftshift(y)));

%trasformata di Fourier del filtro formatore ht (di Nyquist)
Ht=rect_mod(f,2*Rs,0);

%trasformata di Fourier del segnale trasmesso
%dato dalla convoluzione della sequenza impulsiva e del filtro formatore
%oppure dal prodotto delle loro trasformate
Y_nyquist=Y.*Ht;

y_nyquist=ifftshift(ifft(ifftshift(Y_nyquist))); 
%il segnale aleatorio in forma adatta ad essere trasmesso sul canale

figure('Name',' Segnale filtrato con filtro Tx di Nyquist e pronto ad essere trasmesso sul canale')
plot(t,y_nyquist), xlabel('tempo [s]'), ylabel('segnale in ingresso al canale'), grid on

%% CANALE DI TRASMISSIONE
%risposta del canale è pura attenuazione hc(t)=(1/alfa)*delta(t)
alfa = 0.2; % attenuazione [dB/km]
%Potenza_uscita=(1/alfa)*Potenza_ingresso

L=[0:1:100]; %lunghezza collegamento [km] 

%alfa=(10/L)*log(P_in/P_out)=0.2 dB/km
%P_out=P_in/[10^(alfa*L/10)]
%s_out=s_in/[10^(alfa*L/20)]

P_in=y_nyquist.^2; %potenza del segnale in ingresso 
figure('Name',' Potenza del segnale in ingresso al canale')
plot(t,P_in), xlabel('tempo [s]'), ylabel('potenza segnale in ingresso [W]'), grid on

%P_out=P_in./(10^(alfa*L/10)); %potenza del segnale in uscita
%figure('Name','potenza del segnale in uscita al canale')    
%plot(t,P_out), xlabel('tempo [s]'), ylabel('potenza segnale in uscita'), grid on

%potenza del segnale in uscita e potenza media del segnale in uscita
P_out=zeros([length(L) length(t)]);
P_out_avg=zeros(size(L));
lunghezza=length(L);

for c = 1:(lunghezza)
    P_out(c,:)=P_in./(10^(alfa*L(c)/10));  
    P_out_avg(c)=mean(P_out(c,:));
end

figure('Name',' Potenza del segnale in uscita dal canale')
plot(t,P_out), xlabel('tempo [s]'), ylabel('potenza segnale in uscita [W]'), grid on

%grafico della potenza media in Watt in relazione alla lunghezza 
figure('Name',' Potenza media del segnale in uscita dal canale, in Watt')
plot(L,P_out_avg), xlabel('lunghezza del collegamento [km]'), ylabel('potenza media del segnale in uscita [W]'), grid on

%grafico della potenza media in dB in relazione alla lunghezza 
P_out_avg_dB=pow2db(P_out_avg);
figure('Name',' Potenza media del segnale in uscita dal canale, in dB')
plot(L,P_out_avg_dB), xlabel('lunghezza del collegamento [km]'), ylabel('potenza media del segnale in uscita [dB]'), grid on


%segnale in uscita dal canale di trasmissione (prima dell'aggiunta del
%rumore)
s_out=zeros([length(L) length(t)]);
for c = 1:(lunghezza)
    s_out(c,:)=y_nyquist./(10^(alfa*L(c)/20));  
end
figure('Name',' Segnale in uscita dal canale, prima di sommare la componente "rumore"')    
plot(t,s_out), xlabel('tempo [s]'), ylabel('segnale in uscita'), grid on

%generazione del rumore e la sua somma al segnale

SNR_0=10; % SNR per back-to-back [dB]

% vettore di SNR in relazione alla lunghezza
SNR=zeros(size(L));
SNR=L.*alfa;
SNR=SNR_0-SNR;


%somma del segnale e del rumore considerando SNR data lunghezza del
%collegamento
for c=1:(lunghezza)
    s_out_n(c,:)=awgn(s_out(c,:),SNR(c),'measured');
end


figure('Name',' Somma del segnale e del rumore')
plot(t,s_out_n), xlabel('tempo [s]'), ylabel('segnale in uscita dal canale'), grid on
%% RICEVITORE
%è coerente (no dispersione cromatica) ed equalizzato
%hr(t)=ht(t0-t)
%risposta in frequenza al filtro di ricezione - filtro adattato

%hr=ht(t0-t) = ht(-t-(-t0)) -> Ht(-f)*e^(-j*2*Pi_greco*(-t0)) = traslazione
%t0 = metà base del rect_mod = Rs
%Hr=rect_mod(f,2*Rs,Rs); %trasformata di Fourier del filtro di ricezione hr (adattato)
Hr=1; %per spegnere il filtro di ricezione
%figure('Name','filtro del ricevitore')
%plot(f,Hr), xlabel('frequenza'), ylabel('rettangolo'), grid on
s_out_filtrato=zeros([length(L) length(t)]);
for c = 1:(lunghezza)
    S_out_N(c,:)=fftshift(fft(fftshift(s_out_n(c,:))));
    S_out_filtrato(c,:)=S_out_N(c,:).*Hr;

    s_out_filtrato(c,:)=ifftshift(ifft(ifftshift(S_out_filtrato(c,:)))); 
end

figure('Name',' Segnale filtrato dal filtro di ricezione adattato')
plot(t,s_out_filtrato), xlabel('tempo [s]'), ylabel('segnale in uscita dal filtro di ricezione'), grid on
%% campionamento e decisore 
%valore > 0 -> bit 1 
%valore < 0 -> bit 0
s_out_filtrato=s_out_filtrato>0;
s_out_finale=zeros([length(L) length(t)]);


for r = 1:(lunghezza) 
    for c = 1:(num_bit_ingresso)
        if s_out_filtrato(r,32+64*(c-1))==1
            s_out_finale(r,32+64*(c-1))=1;  
        else
            s_out_finale(r,32+64*(c-1))=-1;
        end
    end
end

figure('Name',' Segnale in uscita dal decisore rappresentato come sequenza impulsiva')
plot(t,s_out_finale), xlabel('tempo [s]'), ylabel('segnale in uscita dal decisore'), grid on

%% BER

%BER=sum(trasmessi~=ricevuti)/length(trasmessi)
%BER=sum(y~=s_out_finale)/length(y)
for c = 1:(lunghezza)
    errori=sum(y~=s_out_finale(c,:));
    if errori>=10
        BER(1,c)=errori/length(y);
    else
        BER=NaN;
    end
end

figure('Name',' BER in funzione della lunghezza')
semilogy(L,BER), xlabel('lunghezza collegamento [km]'), ylabel('BER'), grid on

%% FUNZIONI:

function y=rect_mod(t,D,t0)

% funzione rettangolo di durata D e centrata in t0
% INPUT:    t       vettore (ad es. degli istanti di tempo)
y=zeros(size(t));
y=(abs(t-t0)<=D/2);
return
end