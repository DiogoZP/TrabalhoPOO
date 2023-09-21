/* Crie um jogo de RPG em C++ de acordo com as seguintes instruções:
O RPG simulará um combate em uma arena entre personagens. Terá (no mínimo) as classes JogoRPG,
Personagem, e mais 6 classes distintas representando diferentes arquétipos. Por exemplo, Guerreiro(a),
Bruxo(a), Ladrão, Arqueiro(a), etc.
A classe Personagem deve ter no mínimo os seguintes atributos:
Nome do personagem.
Pontos de vida (VID).
Pontos de ataque (ATQ).
Pontos de defesa (DEF).
Lista de personagens derrotados.
Cada classe que identifica um arquétipo será derivada da classe Personagem.
Cada arquétipo terá um ataque especial, exclusivo de sua classe. Este ataque poderá ocorrer,
aleatoriamente, durante um round de combate. Ou seja, em vez do ataque normal, ocorrerá o ataque
especial. Este ataque terá um nome específico e causará mais dano do que um ataque normal.
O ataque especial também poderá causar sangramento, onde o outro personagem sangrará por um número
de rounds calculado aleatoriamente (mínimo de 2 rounds, máximo de 6 rounds). O sangramento causará
uma perda (baixa) de vida a cada round, independente do dano atual recebido no round.
O sangramento deve ser calculado no início de cada round, portanto, um personagem pode ser derrotado
sem receber dano de ataque no round.
Caso ambos os personagens fiquem sem vida devido a sangrarem no início do round, um dos dois
personagens será sorteado para avançar e o outro será considerado derrotado.
Implemente construtores para inicializar o nome, VID, ATQ e DEF do personagem. Implemente um
método para exibir as estatísticas do personagem.
Cada personagem irá armazenar a lista de personagens que derrotou. Use alguma estrutura de dados para
armazenar cada personagem que foi derrotado.
Cada combate poderá durar no máximo 10 rounds. Se nenhum dos dois personagens forem derrotados ao
fim de 10 rounds, o personagem que causou mais dano será considerado o vencedor.
Ao fim de cada combate seu jogo deve exibir uma tabela com as estatísticas do combate, considerando
dano efetuado por cada personagem, vida restante de cada personagem, número de rounds ocorridos, e
quantos ataques especiais ocorreram. */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

class Personagem {
    protected: 
        string _nome;
        int _hp;
        int _hpAtual;
        int _atk;
        int _atkAtual;
        int _def;
        int _defAtual;
        int _danoCausado;
        int _numAtaquesEspeciais;
        int _sangramento;
        vector<Personagem*> _derrotados;

    public:
        Personagem(string nome, int hp, int atk, int def) : _nome(nome), _hp(hp), _hpAtual(hp), _atk(atk), _atkAtual(atk), _def(def), _defAtual(def),    _danoCausado(0), _numAtaquesEspeciais(0), _sangramento(0){}
        void exibir() {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hp << endl;
            cout << "ATK: " << _atk << endl;
            cout << "DEF: " << _def << endl;
        }
        void exibirAtual()
        {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hpAtual << endl;
            cout << "ATK: " << _atkAtual << endl;
            cout << "DEF: " << _defAtual << endl;
            cout << "Derrotados: " << endl;
            int num = _derrotados.size();
            for(int i = 0; i < num; i++) {
                cout << _derrotados[i]->_nome << endl;
            }
        }
        void atacar(Personagem *p) {
            if((rand() % 20 + 1) == 20){
                _numAtaquesEspeciais++;
                AtaqueEspecial(p);
            }
            else {
            p->_hp -= _atk - p->_def;
            _danoCausado += _atk - p->_def;
            }
        }
        int receberDano(int dano) {
            _hpAtual -= dano - _def;
            return dano - _def;
        }
        void receberSangramento()
        {
            _sangramento = rand() % 6 + 2;
        }
        void sangrar() {
            receberDano(_sangramento);
            _sangramento--;
        }
        void reduzirDefesa(int valor) {
            _defAtual -= valor;
        }
        void resetarDefesa() {
            _defAtual = _def;
        }
        void reduzirAtaque(int valor) {
            _atkAtual -= valor;
        }
        void resetarAtaque() {
            _atkAtual = _atk;
        }
        void AtaqueEspecial(Personagem *p) {
            _danoCausado += p->receberDano(_atk);
        }
        void derrotar(Personagem *p) {
            _derrotados.push_back(p);
        }
        bool estaVivo() {
            return _hpAtual > 0;
        }
};

class Guerreiro : public Personagem {
    public:
        Guerreiro(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Furia" << endl;
        }

        void AtaqueEspecial(Personagem *p) {
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            _atkAtual += 5;
            _danoCausado += p->receberDano(_atk);
        }
};

class Ladino : public Personagem {
    public:
        Ladino(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Golpe Critico" << endl;
        }

        void AtaqueEspecial(Personagem *p) {
            p->receberSangramento();
            _danoCausado += p->receberDano(_atk);
        }
};

class Clerigo : public Personagem {
    public:
        Clerigo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Cura" << endl;
        }

        void AtaqueEspecial() {
            _hpAtual += _atk;
        }
};

class Bruxo : public Personagem {
    public:
        Bruxo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Escudo Magico" << endl;
        }

        void AtaqueEspecial(Personagem *p) {
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            _defAtual += 5;
            _danoCausado += p->receberDano(_atk);
        }
};

class Bardo : public Personagem {
    public:
        Bardo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Encantar" << endl;
        }

        void AtaqueEspecial(Personagem *p) {
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            p->reduzirAtaque(5);
            _danoCausado += p->receberDano(_atk);
        }
};

class Arqueiro : public Personagem {
    public:
        Arqueiro(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Flecha Perfurante" << endl;
        }

        void AtaqueEspecial(Personagem *p) {
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            p->reduzirDefesa(5);
            _danoCausado += p->receberDano(_atk);
        }
};

class JogoRPG {
};

int main(){
    srand(time(NULL));
    Guerreiro g1("Guerreiro 1", 100, 10, 5);
    Guerreiro g2("Guerreiro 2", 100, 10, 5);
    Bruxo b1("Bruxo 1", 100, 10, 5);
    b1.derrotar(&g1);
    b1.derrotar(&g2);
    b1.exibirAtual();
    return 0;
}
