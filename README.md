# FEUP-Dissertation
for PDIS and  Master Degree Dissertation


[Work Plan](https://docs.google.com/document/d/1EaRwrBXzREETSml68tNRoZJT4m01oLyG0Dr0M8CWDNk/edit)
[Proposal](https://docs.google.com/document/d/10GmOw57nbpL4KeOVmFNBExa8AKJa6nUK6WsU4PIATa0/edit)
[Abstract](
)
[Presentaton]()



# Dissertation description

**Enquadramento do trabalho:**	As plataformas computacionais são hoje em dia heterogéneas, contendo um processador central e um ou mais elementos aceleradores. Estes elementos de processamento têm características diferentes, sendo cada um deles adequado, ou seja obtêm melhor desempenho, para um determinado tipo de operação. Por outro lado as aplicações são compostas por diversos tipos de operações que poderão ser melhor executadas considerando os vários elementos de processamento disponíveis. 
Neste trabalho pretende-se desenvolver estratégias de execução de aplicações em sistemas heterogéneos e desenvolver mecanismos que possibilitem a configuração automática em função da plataforma disponível.

Este trabalho enquadra-se no projeto ANTAREX (www-antarex-project.eu). 
Objetivos e resultados esperados:	Desenvolver estratégias de configuração automática para aplicações de modo a otimizar a sua execução em plataformas heterogéneas, restritas a uma deadline e custo energético.


**Aspetos inovadores:**	Adaptação da execução de aplicações minimizando os custos energéticos e garantindo as restrições para o tempo de processamento.


**Plano de trabalho provisório:**	
1. Estudar as plataformas heterogéneas disponíveis. 
2. Monitorização dos elementos de processamento em termos de energia e capacidade de processamento. 
3. Estudar e desenvolver estratégias de autotuning para as aplicações alvo. 
4. Implementar e validar as estratégias propostas. 
5. Escrita da dissertação. 


**Referências bibiográficas:**	

*Kaushik Datta. Stencil computation optimization and auto-tuning on state-of-the-art multicore architectures. Proceeding SC '08 Proceedings of the 2008 ACM/IEEE conference on Supercomputing 

*Davide Gadioli, Gianluca Palermo, Cristina Silvano, "Application Autotuning to Support Runtime Adaptivity in Multicore Architectures", Proceeding of XV International Conference on Systems, Architectures, Modeling, and Simulation, IC-SAMOS 2015 

betweenness
g++ *.cpp -fopenmp -std=gnu++11 -o test.out
./teste.out