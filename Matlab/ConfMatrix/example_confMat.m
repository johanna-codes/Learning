clc
clear all
close all

%Example 1
desired=[1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 5 5];
computed=[1 5 5 1 1 1 1 1 5 5 1 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 2 5 5 5 5 5 5 5 5 3 5 5 5];
confMat = confMatGet(desired, computed);
confMatPlot(confMat);

%Example 2
figure
confMat = confMatGet(desired, computed);
opt=confMatPlot('defaultOpt');
opt.className={'run', 'jog', 'walk', 'box', 'hand-c'};
opt.mode='percentage';
opt.format='8.1f';
confMatPlot(confMat,opt);

