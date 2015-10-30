%http://au.mathworks.com/help/images/ref/bwdist.html
clear all
clc
close all
im = imread('templ.png');
 bw = im2bw(im);
 subimage(mat2gray(bw))
 D1 = bwdist(bw,'euclidean');
 subimage(mat2gray(bw))
 figure
 subimage(mat2gray(D1))