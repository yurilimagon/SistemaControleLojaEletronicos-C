#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PRODUTOS "produtos.dat"
#define CLIENTES "clientes.dat"
#define VENDAS "vendas.dat"

struct reg_produto
{
    int cod_prod;
    char desc_prod[100];
    int quant_prod;
    int qmin_prod;
    float preco_prod;
};

struct cad_clientes
{
    int cod_cli;
    char nome_cli[50];
    char end_cli[50];
    char tel_cli[20];
    char email_cli[50];
    char dnas_cli[11];
};

struct cad_vendas
{
    int cod_vend;
    int cod_prod_vend;
    int cod_cli_vend;
    int qtd_prod_vend;
    char data_vend[11];
    float desc_vend;
};

void cadastroProduto() //Cadastrar Produtos
{
    FILE *fpprodutos;
    struct reg_produto produtos;
    char opc;

    printf("Digite o codigo do Produto: ");
    fflush(stdin);
    scanf("%d", &produtos.cod_prod);

    printf("Digite a descricao do Produto: ");
    fflush(stdin);
    gets(produtos.desc_prod);

    printf("Digite a quantidade do Produto: ");
    fflush(stdin);
    scanf("%d", &produtos.quant_prod);

    printf("Digite a quantidade minima do Produto: ");
    fflush(stdin);
    scanf("%d", &produtos.qmin_prod);

    printf("Digite o preco do Produto: ");
    fflush(stdin);
    scanf("%f", &produtos.preco_prod);

    printf("\nGravar?(S/N): ");
    fflush(stdin);
    scanf("%c",&opc);

  if ((opc=='S')||(opc=='s')){
    //Abrir o Arquivo
    fpprodutos = fopen(PRODUTOS,"ab");
    //Gravar
    fwrite(&produtos,sizeof(produtos),1,fpprodutos);
    //Fechar o Arquivo
    fclose(fpprodutos);
    printf("\nProduto Cadastrado com Sucesso. \n\n");
    system("pause");
  }
  else
  {
      printf("\nOperacao Cancelada! \n\n");
      system("pause");
  }
}//Fim cadastroProduto()

void cadastroCliente() //Cadastrar Clientes
{
    FILE *fpclientes;
    struct cad_clientes cliente;
    char opc;

    //Solicita os dados
    printf("\nDigite o Codigo do Cliente: ");
    fflush(stdin);
    scanf("%i",&cliente.cod_cli);
    printf("Digite o Nome do Cliente: ");
    fflush(stdin);
    gets(cliente.nome_cli);
    printf("Digite o Endereco do Cliente: ");
    fflush(stdin);
    gets(cliente.end_cli);
    printf("Digite o Telefone: ");
    fflush(stdin);
    gets(cliente.tel_cli);
    printf("Digite o Email: ");
    fflush(stdin);
    gets(cliente.email_cli);
    printf("Digite a data de nascimento do cliente: ");
    fflush(stdin);
    gets(cliente.dnas_cli);

    printf("\nGravar?(S/N) ");
    fflush(stdin);
    scanf("%c",&opc);

    if ((opc=='S')||(opc=='s')){
    //Abrir o Arquivo
    fpclientes = fopen(CLIENTES,"ab");
    //Gravar
    fwrite(&cliente,sizeof(cliente),1,fpclientes);
    //Fechar o Arquivo
    fclose(fpclientes);
    printf("\ncliente Cadastrado com Sucesso. \n\n");
    system("pause");
    }
    else
    {
        printf("\nOperacao Cancelada! \n\n");
        system("pause");
    }
}//Fim cadastroCliente()

void consultaProdutos() //Consulta Produtos Descricao
{
    FILE *fpcprodutos;
    struct reg_produto produtos;
    char palavra[30];
    int achou=0;

    printf("\nDigite a Palavra Chave: ");
    fflush(stdin);
    gets(palavra);

    //Abrir o Arquivo
    fpcprodutos = fopen(PRODUTOS,"rb");

    //Ler cada registro e mostrar na tela
    while (fread(&produtos,sizeof(produtos),1,fpcprodutos) ==1)
    {
        if(strstr(produtos.desc_prod,palavra)!=NULL)
        {
          printf("\nID: %3d \nDesc: %-30s \nQuantidade: %d \nQuant. Min.:%d \nPreco: %.2f \n\n", produtos.cod_prod, produtos.desc_prod, produtos.quant_prod, produtos.qmin_prod, produtos.preco_prod);
          achou = 1;
        }
    }

    if (!achou)
    {
        printf("\nNenhum Produto encontrado com esta palavra chave.\n\n");
    }
    system("pause");

    //Fechar o aquivo
    fclose(fpcprodutos);
}//Fim consultaProdutos()

void consultaCliente() //Consulta Clientes Inicio Nome
{
    FILE *fpccliente;
    struct cad_clientes cliente;
    char palavra[30];
    int achou=0;

    printf("\nDigite a Palavra Chave: ");
    fflush(stdin);
    gets(palavra);

    //Abrir o Arquivo
    fpccliente = fopen(CLIENTES,"rb");

    //Ler cada registro e mostrar na tela
    while (fread(&cliente,sizeof(cliente),1,fpccliente) ==1)
    {
        if (strncmp(strupr(cliente.nome_cli),strupr(palavra),strlen(palavra))==0)
        {
          printf("\nID: %3d \nCliente: %-30s \nEndereco: %s \nTel: %s \nEmail: %s \nNascimento: %s \n\n", cliente.cod_cli, cliente.nome_cli, cliente.end_cli, cliente.tel_cli, cliente.email_cli, cliente.dnas_cli);
          achou = 1;
        }
    }
    if (!achou)
    {
        printf("\nNenhum Cliente encontrado com esta palavra chave. \n\n");
    }
    system("pause");

    //Fechar o aquivo
    fclose(fpccliente);
}//Fim consultaCliente()

void venda() //Venda
{
    FILE *fpprodutos, *fpclientes, *fpvendas;
    struct reg_produto produto;
    struct cad_clientes cliente;
    struct cad_vendas venda;
    int codProd, codcliente, codvenda, achou, continuar;
    char opc;
    float total,subtotal;

    //Localizar o Cliente
    printf("\nDigite o Codigo do Cliente: ");
    fflush(stdin);
    scanf("%i",&codcliente);

    fpclientes = fopen(CLIENTES,"rb");
    achou = 0;
    while ((!achou)&&(fread(&cliente,sizeof(cliente),1,fpclientes)==1))
    {
        if (cliente.cod_cli == codcliente)
        {
            printf("\nNome: %s \n",cliente.nome_cli);
            achou = 1;
        }
    }
    fclose(fpclientes);
    if (!achou)
    {
      printf("\nCliente NAO Localizado!!");
      return;
    }
    printf("\nConfirma Cliente(S/N)? ");
    fflush(stdin);
    scanf("%c",&opc);

    if ((opc!='s')&&(opc!='S'))
    {
      printf("\nOperacao Cancelada!");
      return;
    }
    //Codigo da Venda - Isso pode ser gerado automaticamente
    printf("\nDigite o Codigo para a Venda: ");
    fflush(stdin);
    scanf("%i",&codvenda);
    //Data da Venda
    printf("\nDigite a Data da Venda[DD/MM/AAAA]: ");
    fflush(stdin);
    gets(venda.data_vend);

    //Entrar e Localizar os Produtos da Venda
    do{
        printf("\nDigite o codigo do Produto: ");
        fflush(stdin);
        scanf("%i",&codProd);
        fpprodutos = fopen(PRODUTOS,"rb");
        achou = 0;
        while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos) == 1))
        {
            if (produto.cod_prod == codProd){
              printf("\nProduto: %s", produto.desc_prod);
              printf("\nPreco.: %.2f", produto.preco_prod);
              achou = 1;
            }
        }
        fclose(fpprodutos);
        if (!achou)
        {
            printf("\nProduto NAO Localizado!");
        }
        else //Produto foi encontrado, então pedir demais dados e gravar
        {
            printf("\nDigite a Quantidade: ");
            fflush(stdin);
            scanf("%i",&venda.qtd_prod_vend);

            printf("Digite o Desconto: ");
            fflush(stdin);
            scanf("%f",&venda.desc_vend);
            venda.cod_vend = codvenda;
            venda.cod_cli_vend = cliente.cod_cli;
            venda.cod_prod_vend = produto.cod_prod;

            //Gravar Venda
            printf("\nConfirma venda deste item(S/N)? ");
            fflush(stdin);
            scanf("%c",&opc);

            if ((opc=='s')||(opc=='S'))
            {
                fpvendas = fopen(VENDAS,"ab");
                fwrite(&venda,sizeof(venda),1,fpvendas);
                fclose(fpvendas);

                printf("\nItem de venda gravado com sucesso.");
            }
            else
            {
                printf("\nItem NAO Confirmado!");
            }
        }
        //Incluir mais Produtos?
        printf("\nDeseja incluir mais Produtos nesta venda(S/N)? ");
        fflush(stdin);
        scanf("%c",&opc);
        if ((opc=='s')||(opc=='S'))
        {
            continuar = 1;
            system("cls");
        }
        else
        {
            continuar = 0;
            system("cls");
        }
    }while (continuar);

    //Finalizar/Totalizar Venda
    printf("\n++++++ Venda +++++++");
    printf("\nPedido nro: %i",codvenda);
    printf("\nData da Venda: %s ", venda.data_vend);
    printf("\nCliente %i - %s \n\n",cliente.cod_cli, cliente.nome_cli);

    fpvendas = fopen(VENDAS,"rb");
    total = 0;
    while (fread(&venda,sizeof(venda),1,fpvendas)==1)
    {
        if (venda.cod_vend == codvenda)
        {
            fpprodutos = fopen(PRODUTOS,"rb+");
            achou = 0;
            while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos)==1))
            {
              if (produto.cod_prod == venda.cod_prod_vend)
              {
                  achou = 1;
              }
            }
            //Decrementa a quantidade comprada do Produto
            produto.quant_prod -= venda.qtd_prod_vend;
            //Posiciona o ponteiro no Código do Produto em questão
            fseek(fpprodutos, -sizeof(produto),1);
            //Altera o valor total do Produto no estoque
            fwrite(&produto,sizeof(produto),1,fpprodutos);
            //Fecha o arquivo
            fclose(fpprodutos);

            subtotal = (produto.preco_prod * venda.qtd_prod_vend) - venda.desc_vend;
            total = total + subtotal;
            printf("\nCod. Produto: %6i \nDescricao: %-25s \nPreco: %5.2f \nQuantidade: %4i \nDesconto: %8.2f SubTotal: %.2f \n", venda.cod_prod_vend, produto.desc_prod, produto.preco_prod, venda.qtd_prod_vend, venda.desc_vend, subtotal);
        }
    }
    fclose(fpvendas);
    printf("\nT O T A L .......: %.2f \n\n",total);
    system("pause");
}//Fim venda()

void relatorioEstoqueMin() //Relatorio de Produtos com Estoque Minimo
{
    FILE *fpprodutos;
    struct reg_produto produtos;
    int achou=0;

    //Abrir o Arquivo
    fpprodutos = fopen(PRODUTOS,"rb");

    //Ler cada registro e mostrar na tela
    while (fread(&produtos,sizeof(produtos),1,fpprodutos) ==1)
    {
        if (produtos.quant_prod <= produtos.qmin_prod)
        {
            printf("\nCod. Prod: %d \nDescricao: %s \nPreco: %.2f \nQuant.: %d \nQuant. Min: %d \n\n",produtos.cod_prod, produtos.desc_prod, produtos.preco_prod, produtos.quant_prod, produtos.qmin_prod);
            achou = 1;
        }
    }
    fclose(fpprodutos);
    if (!achou)
    {
      printf("\nNao existem produtos com estoque minimo atingido.\n\n");
    }
    system("pause");

}//Fim relatorioEstoqueMin()

void relatorioProdutosCliente() //Relatorio de Produtos Comprados por um Cliente
{
    FILE *fpvendas, *fpprodutos;
    struct cad_vendas venda;
    struct reg_produto produtos;
    int codcliente;
    float totalComprado = 0, subTotal;
    int achouVend=0, achouProd = 0;

    //Localizar o Cliente
    printf("\nDigite o Codigo do Cliente: ");
    fflush(stdin);
    scanf("%i",&codcliente);

    //Abrir o Arquivo
    fpvendas = fopen(VENDAS,"rb");

    //Ler cada registro e mostrar na tela
    while (fread(&venda,sizeof(venda),1,fpvendas) ==1)
    {
        if (venda.cod_cli_vend == codcliente)
        {
            fpprodutos = fopen(PRODUTOS,"rb");
            achouProd = 0;
            while (!achouProd && (fread(&produtos,sizeof(produtos),1,fpprodutos)==1))
            {
              if (venda.cod_prod_vend == produtos.cod_prod)
              {
                  achouProd = 1;
              }
            }
            fclose(fpprodutos);

            subTotal = (produtos.preco_prod * venda.qtd_prod_vend) - venda.desc_vend;
            totalComprado += subTotal;

            printf("\nCod. Prod: %d \nDescricao: %s \nQuant.: %d \nPreco: %.2f \n\n", venda.cod_prod_vend, produtos.desc_prod, venda.qtd_prod_vend, subTotal);
            achouVend = 1;
        }
    }
    fclose(fpvendas);
    if (!achouVend)
    {
      printf("\nNao existem produtos comprados por este cliente.\n\n");
      system("pause");
      return;
    }
    printf("TOTAL COMPRADO...............: %.2f \n\n", totalComprado);
    system("pause");

}//Fim relatorioProdutosCliente()

void relatorioClientesProduto() //Relatorio de Clientes que Compraram um Produto
{
    FILE *fpvendas, *fpclientes;
    struct cad_vendas venda;
    struct cad_clientes cliente;
    int codProduto;
    int achouVend = 0, achouCliente = 0;

    //Localizar o Produto
    printf("\nDigite o Codigo do Produto: ");
    fflush(stdin);
    scanf("%i",&codProduto);

    //Abrir o Arquivo
    fpvendas = fopen(VENDAS,"rb");

    //Ler cada registro e mostrar na tela
    while (fread(&venda,sizeof(venda),1,fpvendas) ==1)
    {
        if (venda.cod_prod_vend == codProduto)
        {
            fpclientes = fopen(CLIENTES,"rb");
            achouCliente = 0;
            while (!achouCliente && (fread(&cliente,sizeof(cliente),1,fpclientes)==1))
            {
              if (venda.cod_cli_vend == cliente.cod_cli)
              {
                  achouCliente = 1;
              }
            }
            fclose(fpclientes);

            printf("\nCliente: %s", cliente.nome_cli);

            achouVend = 1;
        }
    }
    printf("\n\n");
    fclose(fpvendas);
    if (!achouVend)
    {
      printf("Nao existem clientes que compraram este produto.\n\n");
    }
    system("pause");
}//Fim relatorioClientesProduto()

void relatorioProdutosMes() //Relatorio de Produtos Vendidos em um Determinado Mes
{
    FILE *fpvendas, *fpprodutos;
    struct cad_vendas venda;
    struct reg_produto produto;
    char data[11];
    int achouData = 0, achouProduto;
    int totalItens = 0;
    float totalVendido = 0, subTotal = 0;

    printf("\nDigite uma data para consulta [MM/AAAA]: ");
    fflush(stdin);
    gets(data);
    //Abre o arquivo VENDAS
    fpvendas = fopen(VENDAS,"rb");

    //Ler cada registro e mostrar na tela
    while(fread(&venda, sizeof(venda),1,fpvendas) == 1)
    {
        if(strstr(venda.data_vend, data) != NULL)
        {
            fpprodutos = fopen(PRODUTOS,"rb");
            achouProduto = 0;
            while(!achouProduto && (fread(&produto,sizeof(produto),1,fpprodutos)==1))
            {
                if(venda.cod_prod_vend == produto.cod_prod)
                {
                    achouProduto = 1;
                }
            }
            fclose(fpprodutos);
            subTotal = (produto.preco_prod * venda.qtd_prod_vend) - venda.desc_vend;
            totalVendido += subTotal;
            totalItens += venda.qtd_prod_vend;
            printf("\nData Compra: %s \nCod. Produto: %6i \nDescricao: %-25s \nPreco: %5.2f \nQuantidade: %4i \nDesconto: %8.2f \nSubTotal: %.2f \n", venda.data_vend, venda.cod_prod_vend, produto.desc_prod, produto.preco_prod, venda.qtd_prod_vend, venda.desc_vend, subTotal);
            achouData = 1;
        }
    }
    fclose(fpvendas);
    if (!achouData)
    {
      printf("\nNao existem produtos comprados neste MES.\n\n");
      system("pause");
      return;
    }
    printf("\nQUANTIDADE DE PRODUTOS VENDIDOS NO MES...............: %d \nTOTAL VENDIDO NO MES.................................: %.2f \n\n", totalItens, totalVendido);
    system("pause");

}//Fim relatorioProdutosMes()

void campeaoVendasAno() //BÔNUS! - Campeao de Vendas do Ano
{
    FILE *fpvendas, *fpprodutos;
    struct cad_vendas venda;
    struct reg_produto produto;
    char ano[10];

    int achouAno = 0, achouProduto = 0, codProdRecord;
    int totalItens = 0, totalItensRecord = 0;
    float totalVendido = 0, precoProdRecord = 0, totalDescRecord = 0;

    printf("\nDigite um ano para consulta [AAAA]: ");
    fflush(stdin);
    gets(ano);

	fpprodutos = fopen(PRODUTOS, "rb");
	//Corre todos os produtos no arquivo PRODUTOS
	while(fread(&produto,sizeof(produto),1,fpprodutos)==1)
	{
		fpvendas = fopen(VENDAS, "rb");

		totalItens = 0;
		//Procura todos os produtos individualmente no arquivo VENDAS
		while(fread(&venda, sizeof(venda),1,fpvendas) == 1)
		{
			//Busca pelo ano e pelo produto por código
			if((produto.cod_prod == venda.cod_prod_vend) && (strstr(venda.data_vend, ano) != NULL))
			{
				totalItens += venda.qtd_prod_vend;
				totalDescRecord += venda.desc_vend;
				achouAno = 1;
			}
		}
		//Guarda a maior quantidade, o código do produto e o preço do produto
		if(totalItens > totalItensRecord)
		{
			totalItensRecord = totalItens;
			codProdRecord = produto.cod_prod;
			precoProdRecord = produto.preco_prod;
		}
		fclose(fpvendas);
	}
	fclose(fpprodutos);

	if (!achouAno)
	{
		printf("\nNao existem produtos comprados neste ANO.\n\n");
		system("pause");
		return;
	}

    fpprodutos = fopen(PRODUTOS,"rb");
    //Ler cada registro e mostrar na tela
    while((!achouProduto)&&(fread(&produto,sizeof(produto),1,fpprodutos) ==1))
    {
        if(produto.cod_prod == codProdRecord)
        {
           achouProduto = 1;
        }
    }
    //Fechar o aquivo
    fclose(fpprodutos);

	totalVendido = ((precoProdRecord * totalItensRecord) - totalDescRecord);
	printf("\nR E C O R D I S T A: \n\nCod. Produto: %6i \nDescricao: %-25s \nQuantidade: %4i \nPreco: %5.2f \nDesconto Total: %.2f \nTotal Faturado: %.2f \n\n", codProdRecord, produto.desc_prod, totalItensRecord, precoProdRecord, totalDescRecord, totalVendido);
	system("pause");

}//Fim campeaoVendasAno()

int main() //PRINCIPAL
{
    int op;
    char data[11];
    do{
        system("cls");
        printf("\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n:: Sistema de Controle de Loja de Eletroeletronicos   ::");
        printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n:: 1) Cadastrar Produtos                              ::");
        printf("\n:: 2) Cadastrar Clientes                              ::");
        printf("\n:: 3) Consulta Produtos Descricao                     ::");
        printf("\n:: 4) Consulta Clientes Inicio Nome                   ::");
        printf("\n:: 5) Venda                                           ::");
        printf("\n:: 6) Relatorio de Produtos com Estoque Minimo        ::");
        printf("\n:: 7) Relatorio de Produtos Comprados por um Cliente  ::");
        printf("\n:: 8) Relatorio de Clientes que Compraram um Produto  ::");
        printf("\n:: 9) Relatorio de Produtos Vendidos em um Det. Mes   ::");
        printf("\n:: 10)Campeao de Vendas do Ano                        ::");
        printf("\n::                                                    ::");
        printf("\n:: 0) Sair                                            ::");
        printf("\n::                                                    ::");
        printf("\n   Opcao-> ");
        fflush(stdin);
        scanf("%d",&op);

        switch(op)
        {
            case 1: system("cls");
                    cadastroProduto();
                    break;

            case 2: system("cls");
                    cadastroCliente();
                    break;

            case 3: system("cls");
                    consultaProdutos();
                    break;
            case 4: system("cls");
                    consultaCliente();
                    break;
            case 5: system("cls");
                    venda();
                    break;
            case 6: system("cls");
                    relatorioEstoqueMin();
                    break;
            case 7: system("cls");
                    relatorioProdutosCliente();
                    break;
            case 8: system("cls");
                    relatorioClientesProduto();
                    break;
            case 9: system("cls");
                    relatorioProdutosMes();
                    break;
            case 10: system("cls");
                     campeaoVendasAno();
                     break;
        }

    }while (op!=0);
}//Fim main()
