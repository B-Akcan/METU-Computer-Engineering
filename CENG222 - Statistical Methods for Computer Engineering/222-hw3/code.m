pkg load statistics

input = [34,32,15,19; 56,58,75,71];

i = 1;
n_j = [];
while (i<=columns(input))
	j = 1;
	summ = 0;
	while (j<=rows(input))
		summ += input(j,i);
		j++;
	endwhile
	n_j = horzcat(n_j, summ);
	i++;
endwhile

i = 1;
n_i = [];
while (i<=rows(input))
	j = 1;
	summ = 0;
	while (j<=columns(input))
		summ += input(i,j);
		j++;
	endwhile
	n_i = horzcat(n_i, summ);
	i++;
endwhile

exp_cont_table = [];
i = 1;
while (i<=rows(input))
	j = 1;
	tmp = [];
	while (j<=columns(input))
		res = n_i(i) * n_j(j) / sum(n_i);
		tmp = horzcat(tmp, res);
		j++;
	endwhile
	exp_cont_table = vertcat(exp_cont_table, tmp);
	i++;
endwhile

chi2 = 0;    	% chi-square value
i = 1;
while (i<=rows(input))
	j = 1;
	while (j<=columns(input))
		chi2 += power(input(i,j)-exp_cont_table(i,j), 2) / exp_cont_table(i,j);
		j++;
	endwhile
	i++;
endwhile

df = (rows(input)-1)*(columns(input)-1);
p_value = 1 - chi2cdf(chi2, df);  % p-value
