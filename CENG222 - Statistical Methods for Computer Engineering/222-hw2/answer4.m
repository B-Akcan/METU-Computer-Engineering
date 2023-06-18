pkg load statistics


# PART A
data = normrnd(175, 7, 1, 1000);
[counts,bins] = hist(data, [150:1:200]);
figure (1);
bar(bins,counts);
title("Answer 4 Part a");
xlabel("Height");
ylabel("Count");
set(gca,"fontsize", 20)

# PART B
data1 = normrnd(175,6,1,1000);
[counts1,bins1] = hist(data1, [150:1:200]);
figure (2);
counts1 = counts1 ./ sum(counts1);
pdf1 = normpdf(bins1,175,6);
pdf1 = pdf1 ./ sum(pdf1);
plot(bins1,pdf1);
title("Answer 4 Part b (sigma=6)");
xlabel("x");
ylabel("f(x)");
set(gca,"fontsize", 20);
set(gca,"ylim", [0 0.1]);
set(gca, "ytick", 0:0.01:0.1);

data2 = normrnd(175,7,1,1000);
[counts2,bins2] = hist(data2, [150:1:200]);
figure (3);
counts2 = counts2 ./ sum(counts2);
pdf2 = normpdf(bins2,175,7);
pdf2 = pdf2 ./ sum(pdf2);
plot(bins2,pdf2);
title("Answer 4 Part b (sigma=7)");
xlabel("x");
ylabel("f(x)");
set(gca,"fontsize", 20);
set(gca,"ylim", [0 0.1]);
set(gca, "ytick", 0:0.01:0.1);

data3 = normrnd(175,8,1,1000);
[counts3,bins3] = hist(data3, [150:1:200]);
figure (4);
counts3 = counts3 ./ sum(counts3);
pdf3 = normpdf(bins3,175,8);
pdf3 = pdf3 ./ sum(pdf3);
plot(bins3,pdf3);
title("Answer 4 Part b (sigma=8)");
xlabel("x");
ylabel("f(x)");
set(gca,"fontsize", 20);
set(gca,"ylim", [0 0.1]);
set(gca, "ytick", 0:0.01:0.1);

# PART C
perc_array = [];

for j = 1:1000
	data4 = normrnd(175, 7, 1, 1000);
	cnt = 0;
	for i = 1:numel(data4)
		if data4(i) >= 170 && data4(i) <= 180
			cnt++;
		endif
	endfor
	percentage = cnt / numel(data) * 100;
	perc_array = horzcat(perc_array, percentage);
endfor

cnt_45 = 0;
cnt_50 = 0;
cnt_55 = 0;
for i = 1:numel(perc_array)
	if perc_array(i) >= 55
		cnt_45++;
		cnt_50++;
		cnt_55++;
	elseif perc_array(i) >= 50
		cnt_45++;
		cnt_50++;
	elseif perc_array(i) >= 45
		cnt_45++;
	endif
endfor

prob_45 = cnt_45 / numel(perc_array);     # answer of 45%
prob_50 = cnt_50 / numel(perc_array);	  # answer of 50%
prob_55 = cnt_55 / numel(perc_array);     # answer of 55%


