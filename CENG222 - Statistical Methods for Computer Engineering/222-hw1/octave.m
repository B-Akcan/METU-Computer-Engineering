blue = [1,2,3,4,5,6];
yellow = [1,1,1,3,3,3,4,8];
red = [2,2,2,2,2,3,3,4,4,6];

idx_b = randi (numel (blue), 1000, 1);
idx_y = randi (numel (yellow), 1000, 1);
idx_r = randi (numel (red), 1000, 1);

values_b = blue (idx_b);
values_y = yellow (idx_y);
values_r = red (idx_r);

values1 = [];

i = 1;
while (i <= 1000)
	values1(i) = values_b(i) + values_y(i) + values_r(i);
	i += 1;
endwhile

mean1 = mean (values1);   # answer of the 1st question

idx_b_1 = randi (numel (blue), 1000, 1);
idx_b_2 = randi (numel (blue), 1000, 1);
idx_b_3 = randi (numel (blue), 1000, 1);

values_b_1 = blue (idx_b_1);
values_b_2 = blue (idx_b_2);
values_b_3 = blue (idx_b_3);

values2 = [];

i = 1;
while (i <= 1000)
	values2(i) = values_b_1(i) + values_b_2(i) + values_b_3(i);
	i += 1;
endwhile

mean2 = mean (values2);   # answer of the 2nd question

i = 1;
total = 0;
while (i <= 1000)
	if (values2(i) > values1(i))
		total += 1;
	endif
	i += 1;
endwhile

percentage = total / 10;   # answer of the 3rd question









