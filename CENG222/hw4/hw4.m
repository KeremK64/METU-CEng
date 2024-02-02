
N = 1502; %from formula

lambda1 = 50;
lambda2 = 40;
lambda3 = 25;

lambda2_1 = 0.1;
lambda2_2 = 0.05;
lambda2_3 = 0.02;

alpha1 = 60;
alpha2 = 100;
alpha3 = 120;

sum1 = 0;
sum2 = 0;
sum3 = 0;

count = 0;
sumAll = 0;
index = 1;
sumArray = zeros(N,1);
for i = 1:N
    sumAll = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
  
    U1 = rand;
    i1 = 0;
    F1 = exp(-lambda1);
    while (U1 >= F1);
    F1 = F1 + exp(-lambda1) * lambda1 ^ i1/gamma(i1+1);
    i1 = i1 + 1;
    end;
    X1=i1;

    U2 = rand;
    i2 = 0;
    F2 = exp(-lambda2);
    while (U2 >= F2);
    F2 = F2 + exp(-lambda2) * lambda2 ^ i2/gamma(i2+1);
    i2 = i2 + 1;
    end;
    X2=i2;

    U3 = rand;
    i3 = 0;
    F3 = exp(-lambda3);
    while (U3 >= F3);
    F3 = F3 + exp(-lambda3) * lambda3 ^ i3/gamma(i3+1);
    i3 = i3 + 1;
    end;
    X3=i3;


    for k = 1:X1
      Y1 = sum( -1/lambda2_1 * log(rand(alpha1,1)) );
      sum1 = sum1 + Y1;
    endfor

    for k = 1:X2
      Y2 = sum( -1/lambda2_2 * log(rand(alpha2,1)) );
      sum2 = sum2 + Y2;
    endfor


    for k = 1:X3
      Y3 = sum( -1/lambda2_3 * log(rand(alpha3,1)) );
      sum3 = sum3 + Y3;
    endfor
    
    if((sum1 + sum2 + sum3) > 300000)
        count = count + 1;
    endif
    
    sumAll = sumAll + sum1 + sum2 + sum3;
    
    sumArray(index,1) = sumAll;
    index = index + 1;
endfor

prob = (count/N);
mean = sum(sumArray) / N;
deviation1 = std(sumArray);

fprintf("Estimated probability : %f\nExpected weight: %f\nStandard deviation : %f\n", prob, mean, deviation1)
