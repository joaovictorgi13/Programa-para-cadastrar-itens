#include <stdio.h>
#include <string.h>

 //Estrutura para representar um produto, com suas respectivas caracteristicas(nome, preço, quantidade).
typedef struct {
    char Name[50];
    float Price;
    int Quantity;
}Product;

//Estrutura para representar um pedido(ID do pedido, Array de até 99 produtos, Soma do valor total do pedido).
typedef struct {
    int Id;
    Product Products[99];
    float Total;
}Order;

int main() {
    Order orders[99]; // Vetor de 99 pedidos.
    int id = 0, status = 1, c;

    // loop que controla todo o programa.
    while (status) {
        printf("\e[1;1H\e[2J"); // Limpa o terminal.
        printf("1 - New order");
        printf("\n2 - List order(s)");
        printf("\n3 - Exit");
        printf("\nChoose an option: ");
        int option;
        scanf("%d", &option);

        switch (option){
            case 1:
                printf("\e[1;1H\e[2J");

                printf("ORDER ID: %d", id + 1);
                printf("\n======================================");
                orders[id].Id = id;
                float total = 0;

                // loop para adicionar produtos
                for (int i = 0; i < 99; i++) {
                    while ((c = getchar()) != '\n' && c != EOF);

                    printf("\n#Product %d", i + 1);
                
                    printf("\nEnter the name of the product: ");    
                    char name[50];
                    fgets(name, sizeof(name), stdin); // atribui o nome do produto a variavel

                    printf("\nEnter the price of the product: ");
                    float price;
                    scanf("%f", &price);

                    printf("\nEnter the quantity of the product: ");
                    int quantity;
                    scanf("%d", &quantity);
                    
                    // cria produto com os dados informados
                    Product product = {.Price = price, .Quantity = quantity};
                    strcpy(product.Name, name); //copia o nome para a struct
                
                    orders[id].Products[i] = product; //Salva no pedido.


                    total += price * quantity; // soma o produto adicionado ao total.

                    printf("\nDo you want to add another product? [y/n] ");
                    char newProduct;
                    scanf(" %c", &newProduct);
                    
                    if (newProduct != 'y') {
                        break;
                    }

                    printf("-------------------------------------------");

                }
                orders[id].Total = total;
                id++;
                break;

            case 2: //listar pedidos
                printf("\e[1;1H\e[2J");
                float overallTotal = 0;

                // percorre todos os pedidos que ja foram criados.
                for (int i = 0; i < id; i++) {
                    if (i > 0) {
                        printf("\n");
                    }
                    printf("ORDER ID: %d", i + 1);
                    for (int j = 0; j < 99; j++) {
                        printf("\n----------------------------------");
                        printf("\n#Product %d", j + 1);
                        printf("\nProduct's name: %s", orders[i].Products[j].Name);
                        printf("Product's price: %f", orders[i].Products[j].Price);
                        printf("\nProduct's quantity: %d", orders[i].Products[j].Quantity);
                        
                        // se o próximo produto tem quantidade 0, significa que não existe
                        if (orders[i].Products[j + 1].Quantity == 0) {
                            break;
                        }
                    }
                    printf("\n==================================");
                    printf("\nTotal: %f", orders[i].Total);
                    overallTotal += orders[i].Total;
                    printf("\n==================================\n");
                }
                printf("\n- Overall total: %f\n", overallTotal);
                printf("\nPress any key to continue...");
                // aguarda botão para continuar
                while ((c = getchar()) != '\n' && c != EOF);
                getchar();
                break;
            case 3: // fechar o programa
                status = 0;
                break;
        }
    }
  
    return 0;
}