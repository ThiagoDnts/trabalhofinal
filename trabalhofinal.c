#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do veículo
typedef struct Veiculo {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
    struct Veiculo *proximo;
} Veiculo;

// Função para adicionar um novo veículo à lista
void adicionarVeiculo(Veiculo **inicio) {
    Veiculo *novoVeiculo = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        printf("Erro ao alocar memória para o novo veículo.\n");
        return;
    }

    printf("Digite o nome do proprietario: ");
    scanf(" %[^\n]", novoVeiculo->proprietario);
    printf("Digite o tipo de combustivel (alcool/diesel/gasolina): ");
    scanf(" %[^\n]", novoVeiculo->combustivel);
    printf("Digite o modelo do veiculo: ");
    scanf(" %[^\n]", novoVeiculo->modelo);
    printf("Digite a cor do veiculo: ");
    scanf(" %[^\n]", novoVeiculo->cor);
    printf("Digite o numero do chassi: ");
    scanf(" %[^\n]", novoVeiculo->chassi);
    printf("Digite o ano do veiculo: ");
    scanf("%d", &novoVeiculo->ano);
    printf("Digite a placa do veiculo (3 letras seguidas de 4 numeros): ");
    scanf(" %[^\n]", novoVeiculo->placa);

    novoVeiculo->proximo = *inicio;
    *inicio = novoVeiculo;

    printf("Veiculo adicionado com sucesso!\n");
}

// Função para listar proprietários de carros do ano 2010 ou posterior movidos a diesel
void listarDieselAno2010OuPosterior(Veiculo *inicio) {
      Veiculo *atual = inicio;
      int encontrados = 0;
      while (atual != NULL) {
          if (strcmp(atual->combustivel, "diesel") == 0 && atual->ano >= 2010) {
              printf("Proprietario: %s\n", atual->proprietario);
              encontrados = 1;
          }
          atual = atual->proximo;
      }
      if (!encontrados) {
          printf("Nenhum veiculo encontrado com os critérios especificados.\n");
      }
  }
// Função para listar placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 e seus respectivos proprietários
void listarPlacasComJ(Veiculo *inicio) {
      Veiculo *atual = inicio;
      int encontrados = 0;
      while (atual != NULL) {
          if (atual->placa[0] == 'J' && (atual->placa[6] == '0' || atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7')) {
              printf("Placa: %s, Proprietario: %s\n", atual->placa, atual->proprietario);
              encontrados = 1;
          }
          atual = atual->proximo;
      }
      if (!encontrados) {
          printf("Nenhum veiculo encontrado com os critérios especificados.\n");
      }
  }

// Função para verificar se um número é par
int ehPar(int numero) {
    return numero % 2 == 0;
}

// Função para listar modelo e cor dos veículos com placas tendo como segunda letra uma vogal e soma dos valores numéricos par
void listarModeloCorPlacasEspecificas(Veiculo *inicio) {
      Veiculo *atual = inicio;
      int encontrados = 0;
      while (atual != NULL) {
          if (strchr("aeiouAEIOU", atual->placa[1]) != NULL) {
              int somaNumerosPlaca = 0;
              for (int i = 3; i < 7; i++) {
                  somaNumerosPlaca += atual->placa[i] - '0';
              }
              if (ehPar(somaNumerosPlaca)) {
                  printf("Modelo: %s, Cor: %s\n", atual->modelo, atual->cor);
                  encontrados = 1;
              }
          }
          atual = atual->proximo;
      }
      if (!encontrados) {
          printf("Nenhum veiculo encontrado com os critérios especificados.\n");
      }
}

// Função para realizar a troca de proprietário com base no número do chassi
void trocarProprietarioPorChassi(Veiculo *inicio, char chassiBuscado[], char novoProprietario[]) {
   Veiculo *atual = inicio;
      while (atual != NULL) {
          int temZeroNaPlaca = 0;
          for (int i = 0; i < 7; i++) {
              if (atual->placa[i] == '0') {
                  temZeroNaPlaca = 1;
                  break;
              }
          }
          if (!temZeroNaPlaca && strcmp(atual->chassi, chassiBuscado) == 0) {
              strcpy(atual->proprietario, novoProprietario);
              printf("Proprietario do veiculo com chassi %s foi alterado para %s\n", chassiBuscado, novoProprietario);
              return;
          }
          atual = atual->proximo;
      }
      printf("Nenhum veiculo com chassi %s encontrado ou veiculo possui digito zero na placa\n", chassiBuscado);
  }


void liberarLista(Veiculo *inicio) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        Veiculo *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

// Função principal para testar as funcionalidades
int main() {
    Veiculo *listaVeiculos = NULL;
    int opcao;
    char chassiTroca[20], novoProprietario[50];

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar veículo\n");
        printf("2. Listar proprietários de carros do ano 2010 ou posterior movidos a diesel\n");
        printf("3. Listar placas que começam com J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários\n");
        printf("4. Listar modelo e cor dos veículos com placas específicas\n");
        printf("5. Trocar proprietário por número de chassi\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarVeiculo(&listaVeiculos);
                break;
            case 2:
                listarDieselAno2010OuPosterior(listaVeiculos);
                break;
            case 3:
                listarPlacasComJ(listaVeiculos);
                break;
            case 4:
                listarModeloCorPlacasEspecificas(listaVeiculos);
                break;
            case 5:
                printf("Digite o número do chassi: ");
                scanf(" %[^\n]", chassiTroca);
                printf("Digite o novo proprietário: ");
                scanf(" %[^\n]", novoProprietario);
                trocarProprietarioPorChassi(listaVeiculos, chassiTroca, novoProprietario);
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    liberarLista(listaVeiculos);

    return 0;
}
