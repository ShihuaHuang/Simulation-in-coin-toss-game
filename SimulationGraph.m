plot(Simulationresult(:,1,1),Simulationresult(:,2,1),Simulationresult(:,1,1),Simulationresult(:,3,1))%column1,all rows,column2, all rows, column1,all rows, column3, all rows
xlabel('Number of Coin Tosses in Each Game');
ylabel('Alice''s Probability of Winning');
legend('Experiment','Theory')