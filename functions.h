#include <iostream>
#include <string>
#include <list>
#include <map>

class Astronauta {
public:
    std::string nome;
    std::string cpf;
    int idade;
};

class Voo {
public:
    int cod;
    std::string status;
    std::list<Astronauta> astronautas_em_voo;
};

std::map<std::string, Astronauta> astronautas_disponiveis;
std::map<std::string, Astronauta> astronautas_mortos_map;
std::list<Voo> voos;
std::list<Voo> voos_em_curso;
std::list<Voo> voos_finalizados;
std::list<Voo> voos_explodidos; 

void Cadastrar_astronauta();
void Cadastrar_voo();
void Adicionar_astronauta();
void Remover_astronauta();
void Subirvoo();
void Explodirvoo();
void Finalizarvoo();
void Listarvoos();
void Listar_astronautas_mortos();

void menu() {
    int opcao;

    do {
        std::cout << "-+-+-+-+MENU+-+-+-+-" << std::endl
            << "[0] Encerrar programa." << std::endl
            << "[1] Cadastrar Astronauta" << std::endl
            << "[2] Cadastrar Voo" << std::endl
            << "[3] Adicionar Astronauta em voo" << std::endl
            << "[4] Remover Astronauta de voo" << std::endl
            << "[5] Lançar Voo" << std::endl
            << "[6] Explodir Voo" << std::endl
            << "[7] Finalizar Voo" << std::endl
            << "[8] Listar Todos os voos" << std::endl
            << "[9] Listar Todos os astronautas mortos" << std::endl;

        std::cin >> opcao;

        switch(opcao) {
            case 1:
                Cadastrar_astronauta();
                break;
            case 2:
                Cadastrar_voo();
                break;
            case 3:
                Adicionar_astronauta();
                break;
            case 4:
                Remover_astronauta();
                break;
            case 5:
                Subirvoo();
                break;
            case 6:
                Explodirvoo();
                break;
            case 7:
                Finalizarvoo();
                break;
            case 8:
                Listarvoos();
                break;
            case 9:
                Listar_astronautas_mortos();
                break;
            case 0:
                std::cout << "Encerrando o programa." << std::endl;
                break;
            default:
                std::cout << "Opção inválida!" << std::endl;
                break;
        }
    } while (opcao != 0);
}

void Cadastrar_astronauta() {
    Astronauta astronauta;

    std::cout << "Digite o nome do astronauta [string]:" << std::endl;
    std::cin >> astronauta.nome;

    std::cout << "Digite o CPF do astronauta [string]:" << std::endl;
    std::cin >> astronauta.cpf;

    std::cout << "Digite a idade do astronauta [int]:" << std::endl;
    std::cin >> astronauta.idade;

    astronautas_disponiveis.insert({astronauta.cpf, astronauta});
}

void Cadastrar_voo() {
    Voo voo;

    std::cout << "Digite o Código do voo [int]:" << std::endl;
    std::cin >> voo.cod;

    voos.push_back(voo);
}

void Adicionar_astronauta() {
    int num_astro; 
    std::string adicionar_cpf; 
    int voocod;

    // Solicita o código do voo ao usuário
    std::cout << "Informe o código de voo [int]:" << std::endl;
    std::cin >> voocod;

    bool encontrado = false; 
    for (auto& voo : voos) {
        if (voocod == voo.cod) {
            std::cout << "Digite o número de astronautas que deseja adicionar ao voo [int]:" << std::endl;
            std::cin >> num_astro;

            for (int i = 0; i < num_astro; i++) {
                std::cout << "Digite o CPF do astronauta a ser adicionado ao voo [string]" << std::endl;
                std::cin >> adicionar_cpf;

                // Verifica se o astronauta com o CPF informado está disponível
                auto it = astronautas_disponiveis.find(adicionar_cpf);
                if (it != astronautas_disponiveis.end()) {
                    // Adiciona o astronauta ao voo e remove-o da lista de disponíveis
                    voo.astronautas_em_voo.push_back(it->second);
                    std::cout << "Astronauta " << it->second.nome << " adicionado ao voo." << std::endl;
                    astronautas_disponiveis.erase(it);
                    encontrado = true; 
                } else {
                    // Informa que o astronauta não foi encontrado
                    std::cout << "Astronauta com CPF " << adicionar_cpf << " não encontrado." << std::endl;
                }
            }
            break; 
        }
    }
    // Se o voo não foi encontrado, emite uma mensagem de aviso
    if (!encontrado) {
        std::cout << "Voo não encontrado." << std::endl;
    }
}

void Remover_astronauta() {
    std::string remover_cpf;
    int voocod;

    std::cout << "Digite o CPF do astronauta que deseja remover: ";
    std::cin >> remover_cpf;

    std::cout << "Digite o código do voo em que deseja remover o astronauta: ";
    std::cin >> voocod;

    for (auto& voo : voos) {
        if (voo.cod == voocod) {
            for (auto it_astronauta = voo.astronautas_em_voo.begin(); it_astronauta != voo.astronautas_em_voo.end(); ++it_astronauta) {
                if (it_astronauta->cpf == remover_cpf) {
                    // Adicionar o astronauta removido de volta à lista de astronautas disponíveis
                    astronautas_disponiveis[it_astronauta->cpf] = *it_astronauta;
                    // Remover o astronauta do voo
                    voo.astronautas_em_voo.erase(it_astronauta);
                    std::cout << "Astronauta removido com sucesso do voo." << std::endl;
                    return;
                }
            }
            // Se o astronauta não for encontrado no voo
            std::cout << "Astronauta com CPF " << remover_cpf << " não encontrado no voo." << std::endl;
            return;
        }
    }

    // Se o voo não for encontrado
    std::cout << "Voo com código " << voocod << " não encontrado." << std::endl;
}

void Subirvoo() {
    int voocod;
    std::cout << "Digite o código do voo que deseja lançar: ";
    std::cin >> voocod;

    for (auto it_voo = voos.begin(); it_voo != voos.end(); ++it_voo) {
        if (it_voo->cod == voocod) {
            it_voo->status = "Em curso";
            voos_em_curso.push_back(*it_voo);
            voos.erase(it_voo);
            std::cout << "Voo lançado com sucesso." << std::endl;
            return;
        }
    }

    // Se o voo não for encontrado
    std::cout << "Voo com código " << voocod << " não encontrado." << std::endl;
}

void Explodirvoo() {
    int voocod;
    std::cout << "Digite o código do voo que deseja explodir: ";
    std::cin >> voocod;

    for (auto it_voo = voos_em_curso.begin(); it_voo != voos_em_curso.end(); ++it_voo) {
        if (it_voo->cod == voocod) {
            // Marcar astronautas do voo como mortos e removê-los da lista de astronautas disponíveis
            for (auto& astronauta : it_voo->astronautas_em_voo) {
                astronautas_mortos_map[astronauta.cpf] = astronauta;
                astronautas_disponiveis.erase(astronauta.cpf);
            }
            // Mover o voo para a lista de voos explodidos e removê-lo da lista de voos em curso
            voos_explodidos.push_back(*it_voo);
            voos_em_curso.erase(it_voo);
            std::cout << "Voo explodido com sucesso." << std::endl;
            
            return;
        }
    }

    // Se o voo não for encontrado ou não estiver em curso
    std::cout << "Voo com código " << voocod << " não encontrado ou não está em curso." << std::endl;
}

void Finalizarvoo() {
    int voocod;
    std::cout << "Digite o código do voo que deseja finalizar: ";
    std::cin >> voocod;

    for (auto it_voo = voos_em_curso.begin(); it_voo != voos_em_curso.end(); ++it_voo) {
        if (it_voo->cod == voocod) {
            // Adicionar astronautas de volta à lista de astronautas disponíveis
            for (auto& astronauta : it_voo->astronautas_em_voo) {
                astronautas_disponiveis[astronauta.cpf] = astronauta;
            }
            it_voo->status = "Finalizado";
            voos_finalizados.push_back(*it_voo);
            voos_em_curso.erase(it_voo);
            std::cout << "Voo finalizado com sucesso." << std::endl;
            return;
        }
    }

    // Se o voo não for encontrado
    std::cout << "Voo com código " << voocod << " não encontrado ou não está em curso." << std::endl;
}

void ListarVoos() {
    std::cout << std::endl;
    std::cout << "Voos Planejados:" << std::endl;
    std::cout << std::endl;

    for (auto& voo : voos) {
        // Mostra o código do voo.
        std::cout << "Código do voo: " << voo.cod << std::endl;
        std::cout << "Astronautas no voo:" << std::endl;
        
        for (auto& astronauta : voo.astronautas_em_voo) {
            // Mostra o nome e CPF do astronauta.
            std::cout << "- Nome: " << astronauta.nome << ", CPF: " << astronauta.cpf << std::endl;
        }
    }

    // Repete o mesmo processo para voos em curso, finalizados e explodidos.

    std::cout << std::endl;
    std::cout << "Voos em Curso:" << std::endl;
    std::cout << std::endl;

    for (auto& voo : voos_em_curso) {
        // Mostra o código do voo.
        std::cout << "Código do voo: " << voo.cod << std::endl;
        std::cout << "Astronautas no voo:" << std::endl;

        for (auto& astronauta : voo.astronautas_em_voo) {
            // Mostra o nome e CPF do astronauta.
            std::cout << "- Nome: " << astronauta.nome << ", CPF: " << astronauta.cpf << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Voos Finalizados:" << std::endl;
    std::cout << std::endl;

    for (auto& voo : voos_finalizados) {
        // Mostra o código do voo.
        std::cout << "Código do voo: " << voo.cod << std::endl;
        std::cout << "Astronautas no voo:" << std::endl;

        for (auto& astronauta : voo.astronautas_em_voo) {
            // Mostra o nome e CPF do astronauta.
            std::cout << "- Nome: " << astronauta.nome << ", CPF: " << astronauta.cpf << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Voos Explodidos:" << std::endl;
    std::cout << std::endl;

    for (auto& voo : voos_explodidos) {
        // Mostra o código do voo.
        std::cout << "Código do voo: " << voo.cod << std::endl;
    }
}

void ListarAstronautasMortos() {
    
    for (auto& pair : astronautas_mortos_map) {
        // Mostra o nome e CPF do astronauta morto.
        std::cout << "Astronauta: " << pair.second.nome << " - CPF: " << pair.second.cpf << std::endl;
        std::cout << "Voos em que participou:" << std::endl;

        for (auto& voo : voos_finalizados) {
            // Verifica se o astronauta participou deste voo.
            for (auto& astronauta_voo : voo.astronautas_em_voo) {
                if (astronauta_voo.cpf == pair.second.cpf) {
                    // Mostra o código do voo em que o astronauta participou.
                    std::cout << "- Código do voo: " << voo.cod << std::endl;
                }
            }
        }
        
        for (auto& voo : voos_explodidos) {
            // Verifica se o astronauta participou deste voo.
            for (auto& astronauta_voo : voo.astronautas_em_voo) {
                if (astronauta_voo.cpf == pair.second.cpf) {
                    // Mostra o código do voo em que o astronauta participou.
                    std::cout << "- Código do voo: " << voo.cod << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}
