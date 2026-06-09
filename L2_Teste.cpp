
#include <stdio.h>
#include <stdlib.h>

	int main(){
		//DECLARAÇÃO DAS VARIÁVIES
		//Caixas (Tipos)
		printf("A seguir os 3 tamanhos de caixas para empacotamento \n\n");
		printf("Caixa 1: Altura 30 Comprimento 40 Largura 80 \n");
		printf("Caixa 2: Altura 80 Comprimento 50 Largura 40 \n");
		printf("Caixa 3: Altura 50 Comprimento 80 Largura 60 \n\n");
		int box_1[3]= {30, 40, 80};
		int box_2[3]= {80, 50, 40};
		int box_3[3]= {50, 80, 60};
		
		//Caixas (Volume)
		int box_1_volume = 30 * 40 * 80;
		int box_2_volume = 80 * 50 * 40;
		int box_3_volume = 50 * 80 * 60;
		//Print informativo para demonstrar o espaco em centimetros cúbicos
		printf("O volume correspondente das caixas em centrimetros cubicos de menor a maior: \n\n");
		printf("Caixa 1 comporta %icm³ \n",box_1_volume);
		printf("Caixa 2 comporta %icm³ \n",box_2_volume);
		printf("Caixa 3 comporta %icm³ \n\n",box_3_volume);
		
		/*Comparação dos Lados da Caixa
		  int box_larger_side = 80;
		  int box_medium_side = 40;
		  int box_smaller_side = 30;
		*/
		/*Comparação dos Lados do Produto
		  int prod_side = 0;
		  int prod_smaller_side = 0;
		  int prod_medium_side = 0;
		  int prod_larger_side = 0;
		*/
		//Soma das Dimensões Individuais dos Produtos
		int prod_sum_height = 0;
		int prod_sum_width = 0;
		int prod_sum_length = 0;
		
		//DADOS DO PRODUTO (ITEM)
		char prod_name[100][50];
		int prod_height[100];
		int prod_width[100];
		int prod_length[100];
	
		//Volume
		int prod_volume[100];
		//Quantidade individual 
		int prod_qty[100];
		//Quantidade que será multiplicado pelo volume
		int prod_qty_volume = 0;
		//Total das quantidades multiplicadas pelos volumes
		int total_volume = 0;
		//Total das dimensões individuais de cada item
		int total_dim_h = 0;
		int total_dim_w = 0;
		int total_dim_l = 0;
		
		//ESTRUTURA DE REPETIÇÃO
		//Looping da inserção de itens
		int option = 0;
		//Looping do novo pedido adicionado
		int option_pedido = 0;
		int i = 0;
		
		do{
			
			do{
			//ENTRADA DE DADOS
		printf("Informe o produto que deseja adicionar ao pacote: \n");
		scanf(" %s", prod_name[i]);
		
		printf("Informe as dimensoes do produto: Altura, Comprimento, Largura \n");
		scanf("%i %i %i", &prod_height[i], &prod_width[i], &prod_length[i]);
		
		//XxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxX
		//Verifica se Alguma das Dimensões do Produto é Maior que alguma das Dimensão da Caixa
		//Poderia verificar também as dimensões médias e minímas, verifica apenas a maior
		while(prod_height[i] > 80 || prod_width[i] > 80 || prod_length[i] > 80){
			printf("Item muito grande para caber nas caixas \n\n ");
			printf("Informe o produto que deseja adicionar ao pacote: \n");
			scanf(" %s", prod_name[i]);
			printf("Informe as dimensoes do produto: Altura, Largura, Comprimento \n");
			scanf("%i %i %i", &prod_height[i], &prod_width[i], &prod_length[i]);
		}
		//XxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxXxX
		
		printf("Informe a quantidade desejada do produto: \n");
		scanf("%i", &prod_qty[i]);
		
		//Soma das Dimensões Individuais do Produto
		prod_sum_height += prod_height[i];
		prod_sum_width += prod_width[i];
		prod_sum_length += prod_length[i];
		
		//Multiplica a soma da dimensão pela quantidade de itens
		total_dim_h = prod_sum_height * prod_qty[i];
		total_dim_w = prod_sum_width * prod_qty[i];
		total_dim_l = prod_sum_length * prod_qty[i];
		
		//Armazena o Resultado da Multiplicação entre as Dimensões dos Produtos
		prod_volume[i] = prod_height[i] * prod_width[i] * prod_length[i];
		
		//Multiplica as quantidades pelo volume do item
		prod_qty_volume = prod_qty[i] * prod_volume[i];
		
		//Soma o Total 
		total_volume += prod_qty_volume;
		
		printf("Deseja adicionar mais algum produto? \n");
		i++;
		printf("1 = sim / 0 = nao \n");
		scanf("%i", &option);
		
		}while(option != 0);
		
			// Produtos Adicionados ao Pacote
    	printf("\n--- Produtos Adicionados ---\n");
    	for(int j = 0; j < i; j++) {
        printf("Produto %d: %s | Dimensoes: %ix%ix%i |Quantidade: %i\n", j+1, prod_name[j], prod_height[j], prod_width[j], prod_length[j], prod_qty[j]);
        
    	}
		
		//Comparando o Volume dos Produtos com o Volume das Caixas
		if((prod_height[i] <= 30 
		|| prod_width[i] <= 40 
		|| prod_length[i] <= 80)
		&& total_volume <= box_1_volume){
			printf("Produto empacotado na caixa tipo 1 \n");
		}
		
		else if((prod_height[i] <= 80 
		|| prod_width[i] <= 50 
		|| prod_length[i] <= 40)
		&& total_volume > box_1_volume 
		&& total_volume <= box_2_volume){
			printf("Produto empacotado na caixa tipo 2 \n");
		
		}
		else if((prod_height[i] <= 50 
		|| prod_width[i] <= 80 
		|| prod_length[i] <= 60)
		&& total_volume > box_2_volume 
		&& total_volume <= box_3_volume){
			printf("Produto empacotado na caixa tipo 3 \n");
			
		}
		else{
			printf("O pedido ocupa mais de uma caixa. \n");
			if(total_volume > box_3_volume){
				int package = total_volume / box_3_volume;
				int leftover = total_volume % box_3_volume;
				printf("Pacote ocupa: %i caixas tipo 3 \n",package);
				if(leftover <= box_1_volume){
					printf("O restante ocupa uma caixa tipo 1 \n");
				}
				else if(leftover > box_1_volume && leftover <= box_2_volume){
					printf("O restante ocupa uma caixa tipo 2 \n");
				}
				else{
					printf("O restante ocupa uma caixa tipo 3 \n");
				}
			}
		}
		
		printf("Deseja empacotar um novo pedido? \n");
			printf("1 = Sim / 0 = Nao \n");
			scanf("%i", &option_pedido);
			if(option_pedido == 1){
    		prod_volume[i] = 0;
    		i = 0;
    		option = 0;
		}	
		
		}while(option_pedido != 0);
		
    	return(0);
	}
