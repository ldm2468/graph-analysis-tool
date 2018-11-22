function []=graph_plot(gn)

% label
file=fopen('./matlab_plot/label-vertex.txt', 'r');
if ( file > 0)
data = textscan(file,'%s %f');
figure(1);
label = categorical(data{1}');
vertex = data{2}';
h=histogram('Categories', label, 'BinCounts', vertex);
h.DisplayOrder = 'descend';

title('label-vertex', 'fontsize', 14);
xlabel('label', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
path=['./matlab_plot/', gn,'_label-vertex'];
print('-f1',path, '-dpng');    
 
figure(2);
vertex_log = log10(abs(vertex));
h=histogram('Categories', label, 'BinCounts', vertex_log);
h.DisplayOrder = 'descend';
title('label-log(vertex)', 'fontsize', 14);
xlabel('label', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
path=['./matlab_plot/', gn '_label-vertex_log'];
print('-f2',path, '-dpng');    

end

% degree
file=fopen('./matlab_plot/degree.txt', 'r');
if (file>0)
d = fscanf(file, "%f");
figure(3);
h=histogram(d);
title('degree-vertex', 'fontsize', 14);
xlabel('degree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
path=['./matlab_plot/', gn, '_degree'];
print('-f3', path, '-dpng');

figure(4);
h=histogram(log10(abs(d)));
title('degree-log(vertex)', 'fontsize', 14);
xlabel('degree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
path=['./matlab_plot/', gn, '_degree_log'];
print('-f4', path, '-dpng');

end

% indegree
file=fopen('./matlab_plot/indegree.txt', 'r');
if(file>0)
d = fscanf(file, "%f");
figure(5);
histogram(d);
title('indegree-vertex', 'fontsize', 14);
xlabel('indegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
path=['./matlab_plot/', gn, '_indegree'];
print('-f5', path, '-dpng');
figure(6);
histogram(log10(d));
title('indegree-log(vertex)', 'fontsize', 14);
xlabel('indegree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
path=['./matlab_plot/', gn, '_indegree_log'];
print('-f6', path, '-dpng');

end

% outdegree
file=fopen('./matlab_plot/outdegree.txt', 'r');
if(file>0)
d = fscanf(file, "%f");
figure(7);
histogram(d);
title('outdegree-vertex', 'fontsize', 14);
xlabel('outdegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
path=['./matlab_plot/', gn, '_outdegree'];
print('-f7', path, '-dpng');

figure(8);
histogram(log10(abs(d)));
title('outdegree-log(vertex)', 'fontsize', 14);
xlabel('outdegree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
path=['./matlab_plot/', gn, '_outdegree_log'];
print('-f8', path, '-dpng');
end

clc; close all;