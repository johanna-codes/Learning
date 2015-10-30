close all
clear all
clc
rx = randi([11 29],100,1);
ry = randi([21 45],100,1);
plot (rx,ry, 'r.');
hold on

sx = randi([21 39],100,1);
sy = randi([65 85],100,1);
plot (sx,sy, 'b.');


wx = randi([30 49],100,1);
wy = randi([49 65],100,1);
plot (wx,wy, 'g.');

training_data = [ rx ry];
labels = [ones(100,1)];
training_data = [training_data; sx sy];
labels = [labels; 2*ones(100,1)];
training_data = [training_data; wx wy];
training_data = training_data';
labels = [labels; 3*ones(100,1)];

[dim,n_samples] = size(training_data)  ;

figure
hold on
for i=1:n_samples
    x = training_data(1,i);
    y = training_data(2,i);
    if labels(i) ==1
        plot (x,y, 'k.');
    elseif labels(i) ==2
        plot (x,y, 'm.');
    else
        plot (x,y, 'r.');
    end
end
save('training_data.dat','training_data', '-ascii')  
save('labels.dat','labels', '-ascii')  

