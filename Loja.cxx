#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>

using namespace std;

struct NotaFiscal {
    string produto;
    double valor;
    string data;
    string cnpj;

    void exibirNota() {
        cout << "\n--- Nota Fiscal ---" << endl;
        cout << "Produto: " << produto << endl;
        cout << "Valor: R$ " << fixed << setprecision(2) << valor << endl;
        cout << "Data: " << data << endl;
        cout << "CNPJ: " << cnpj << endl;
        cout << "-------------------" << endl;
    }
};

class Loja {
private:
    vector<string> produtos{"MAÇA", "BANANA", "UVA", "PESSEGO", "LIMÃO", "MORANGO"};
    vector<double> valores{5.0, 10.50, 6.40, 2.40, 9.0, 10.0};
    double lucroTotal = 0.0; // Para armazenar o lucro total

public:
    // CONSTRUTOR    
    Loja() = default;

    void listarProdutos() {
        cout << "\n----------------------------" << endl;
        cout << "| Produto    | Valor (R$)  |" << endl;
        cout << "----------------------------" << endl;

        for (size_t i = 0; i < produtos.size(); ++i) {
            cout << "| " << left << setw(10) << produtos[i]
                 << "| " << right << setw(10) << fixed << setprecision(2) << valores[i] << " |" << endl;
        }
        cout << "----------------------------" << endl;
    }

    const string& getProduto(size_t index) const {
        if (index < produtos.size()) {
            return produtos[index];
        } else {
            throw out_of_range("\nÍndice de produto inválido.");
        }
    }

    double getValor(size_t index) const {
        if (index < valores.size()) {
            return valores[index];
        } else {
            throw out_of_range("\nÍndice de valor inválido.");
        }
    }

    size_t getQuantidadeProdutos() const {
        return produtos.size();
    }

    void registrarLucro(double valor) {
        lucroTotal += valor;
    }

    double getLucroTotal() const {
        return lucroTotal;
    }
};

// pular linha
void pularLinha() {
    cout << "\n";
}

void pressione() {
    cout << "APERTE QUALQUER TECLA PARA CONTINUAR: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o resto da linha
    cin.get(); // Aguarda a entrada do usuário
}

int main() {
    setlocale(LC_ALL, "portuguese");

    int opt;
    bool menu = true;

    string inicio = "\nBEM VINDO AO MENU!";
    Loja loja;

    do {
        cout << inicio << endl;
        cout << "AUTOR: Ronny Rocke" << endl;
        cout << "DATA: 18/10/24" << endl;
        pularLinha();
        cout << "1: Ver Produtos" << endl;
        cout << "2: Comprar Produto" << endl;
        cout << "3: Solicitar Nota Fiscal" << endl;
        cout << "4: Ver Lucro Total" << endl; // Nova opção
        cout << "5: Sair" << endl;

        pularLinha();

        cout << "DIGITE UMA OPÇÃO: ";
        cin >> opt;

        // Verifica se a entrada é válida
        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a linha atual
            cout << "Entrada inválida! Por favor, insira um número." << endl;
            pressione();
            continue; // Volta para o início do loop
        }

        pularLinha();

        try {
            switch (opt) {
                case 1:
                    loja.listarProdutos();
                    pressione();
                    break;

                case 2: {
                    loja.listarProdutos();  // Exibe produtos antes de comprar
                    size_t indice;  
                    cout << "Digite o número do produto que deseja comprar (0 a " << loja.getQuantidadeProdutos() - 1 << "): ";
                    cin >> indice;

                    // Verifica se a entrada é válida
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada inválida! Por favor, insira um número." << endl;
                        pressione();
                        continue; // Volta para o início do loop
                    }

                    if (indice < loja.getQuantidadeProdutos()) {
                        cout << "Produto comprado: " << loja.getProduto(indice) 
                             << " - R$ " << loja.getValor(indice) << endl;
                        loja.registrarLucro(loja.getValor(indice)); // Registra o lucro
                        pularLinha();
                        pressione();
                    } else {
                        cout << "\nProduto inválido!" << endl;
                    }
                    break;
                }

                case 3: {
                    // Solicitar nota fiscal
                    string cnpj = "00.000.000/0000-00";  // CNPJ simulado
                    string data;
                    cout << "\nDigite a data da compra: ";
                    cin >> data;

                    string produto;
                    double valor;
                    cout << "\nDigite o produto comprado: ";
                    cin >> produto;

                    // Verifica se o produto existe
                    bool produtoValido = false;
                    for (size_t i = 0; i < loja.getQuantidadeProdutos(); ++i) {
                        if (produto == loja.getProduto(i)) {
                            produtoValido = true;
                            valor = loja.getValor(i);
                            break;
                        }
                    }

                    if (!produtoValido) {
                        cout << "Produto não encontrado na lista!" << endl;
                        pressione();
                        break;
                    }

                    cout << "\nDigite o valor: ";
                    cin >> valor;

                    NotaFiscal nota;
                    nota.produto = produto;
                    nota.valor = valor;
                    nota.data = data;
                    nota.cnpj = cnpj;

                    pularLinha();
                    nota.exibirNota();  // Exibe a nota fiscal
                    
                    pressione();
                    break;
                }

                case 4: {
                    cout << "\nLucro Total: R$ " << fixed << setprecision(2) << loja.getLucroTotal() << endl;
                    pressione();
                    break;
                }

                case 5:
                    cout << "\nObrigado por utilizar o programa!" << endl;
                    menu = false;
                    break;

                default:
                    cout << "\nOPÇÃO INVÁLIDA!" << endl;
                    pressione();
                    break;
            }
        } catch (const exception& e) {
            cout << "Erro: " << e.what() << endl;
        }

    } while (menu);

    return 0;
}
