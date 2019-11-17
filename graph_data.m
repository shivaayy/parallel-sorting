load worst.text;
load average.text;
load best.text;
plot(worst(:,1),worst(:,2),"-or;worst case;");
hold on;
plot(best(:,1),best(:,2),"-og;best case;");
hold on;
plot(average(:,1),average(:,2),"-ob;average case;");
hold on;
set(get(gca, 'Title'), 'String', 'CREW sorting analysis');

set(get(gca, 'XLabel'), 'String', 'No of processor');
set(get(gca, 'YLabel'), 'String', 'Avg exe time in sec for 10^5 element');
