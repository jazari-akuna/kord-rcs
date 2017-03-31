%% Tool for loading measurement files from the optical sensor experiment and plotting them correctly.
close all;
clear;

tare=66;
%figure('Name','Sensor output for different motor speeds','NumberTitle','off');

%% Get the measurements file
    %[FileA,PathA]=uigetfile('*.txt');
    figure(1);
    FullFileA = '/home/raphael/Documents/P6/kord-rcs/SRB_test/LOG00414.TXT'; %fullfile(PathA,FileA);
    FullFileB = '/home/raphael/Documents/P6/kord-rcs/SRB_test/LOG00415.TXT';
    file=dlmread(FullFileA,' ');
    traw=file(:,2);
    fraw=file(:,3);
    %f=zeros(length(fraw));
    %t=zeros(length(fraw));
    j=1;
    
    for i=2723:3101
        if abs(fraw(i)-mean(fraw)) < 10^10
            f(j)=fraw(i);
            t(j)=traw(i);
            j=j+1;
        end
    end
    f=f+1338244;
    f=f.*(287/(1.475*10^5));
    f=f+tare;
    %xlim([0 25000])

    %figure(2)
    file=dlmread(FullFileB,' ');
    t2raw=file(:,2);
    f2raw=file(:,3);
    %f=zeros(length(fraw));
    %t=zeros(length(fraw));
    j=1;
    
    for i=4695:5060
        if abs(f2raw(i)-mean(f2raw)) < 10^10
            f2(j)=f2raw(i);
            t2(j)=t2raw(i);
            j=j+1;
        end
    end
    
    f2=f2+1338244;
    f2=f2.*(287/(1.475*10^5));
    f2=f2+tare;
    %xlim([0 8*10^4])
    
    for i=1:length(f2)
        f3(i)=(f(i)+f2(i))/2;
        x(i)=(i-1)*15;
    end;
    for i=1:length(f)
        x1(i)=(i-1)*15;
    end;
    
    hold on;
    plot(x1,f,'.')
    plot(x,f2,'.')
    plot(x,f3);