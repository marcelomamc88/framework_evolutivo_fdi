epochs = 300 ;
m = [-1, 1];

values = zeros(1,epochs);

for i=1:epochs
    choices = [.01:.04:.5];     
    values(i) =   randi([10 50],1,1);
end

max(values)

