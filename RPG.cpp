#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <conio.h>
using namespace std;

class Item {
    protected:
        string _nome;
        string _raridade;
        int _hp, _atk, _def, _vel;
    public:
        Item(string nome, string raridade, int hp, int atk, int def, int vel) : _nome(nome), _raridade(raridade), _hp(hp), _atk(atk), _def(def), _vel(vel){}
        string getNome() {
            return _nome;
        }
        int getHp() {
            return _hp;
        }
        int getAtk() {
            return _atk;
        }
        int getDef() {
            return _def;
        }
        int getVel() {
            return _vel;
        }

};
class Personagem {
    protected: 
        string _nome;
        int _hp, _hpAtual, _atk, _atkAtual, _def, _defAtual, _vel, _velAtual, _sangramento;
        vector<Item> _inventario;
        int _posX = 1;
        int _posY = 8;

    public:
        Personagem(string nome, int hp, int atk, int def, int vel) : _nome(nome), _hp(hp), _hpAtual(hp), _atk(atk), _atkAtual(atk), _def(def), _defAtual(def), _vel(vel), _velAtual(vel), _sangramento(0){}
        
        void setHpAtual(int hp) {
            _hpAtual = hp;
        }
        void resetar() {
            _hpAtual = _hp;
            _atkAtual = _atk;
            _defAtual = _def;
            _velAtual = _vel;
            _sangramento = 0;
        }
        string getNome() {
            return _nome;
        }
        int getSangramento() {
            return _sangramento;
        }
        int getHp() {
            return _hp;
        }
        int getHpAtual() {
            return _hpAtual;
        }
        int getVelAtual() {
            return _velAtual;
        }

        void atacar(Personagem *p) {
            srand(time(NULL));
            if((rand() % 20 + 1) > 10){
                AtaqueEspecial(p);
            }
            else {
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " golpeou causando " << dano << " de dano." << endl;
            }
        }
        int receberDano(int atk) {
            srand(time(NULL));
            int d = atk - _def + (rand() % 6);
            if (d < 0) d = 0;
            _hpAtual -= d;
            return d;
        }
        void receberSangramento()
        {
            srand(time(NULL));
            _sangramento = rand() % 6 + 2;
        }
        void sangrar() {
            _hpAtual -= _sangramento;
            cout << _nome << " sangrou perdendo " << _sangramento << " de vida." << endl;
            _sangramento--;
        }
        void reduzirDefesa(int valor) {
            _defAtual -= valor;
        }
        void reduzirAtaque(int valor) {
            _atkAtual -= valor;
        }
        void reduzirVelocidade(int valor) {
            _velAtual -= valor;
        }
        void adicionarItem(Item i) {
            _inventario.push_back(i);
            _hp += i.getHp();
            _atk += i.getAtk();
            _def += i.getDef();
            _vel += i.getVel();
        }
        void virtual AtaqueEspecial(){}
        void virtual AtaqueEspecial(Personagem *p) {}
        bool estaVivo() {
            return _hpAtual > 0;
        }
        void mover(int x, int y) {
            _posX = x;
            _posY = y;
        }
        int getPosX() {
            return _posX;
        }
        int getPosY() {
            return _posY;
        }
        void exibirInventario() {
            system("cls");
            for(int i=0; i<_inventario.size(); i++) {
                cout << "=====" << _inventario[i].getNome() << "=====" << endl;
                if(_inventario[i].getHp() > 0) {
                    cout << "HP: +" << _inventario[i].getHp() << endl;
                }
                if(_inventario[i].getAtk() > 0) {
                    cout << "Ataque: +" << _inventario[i].getAtk() << endl;
                }
                if(_inventario[i].getDef() > 0) {
                    cout << "Defesa: +" << _inventario[i].getDef() << endl;
                }
                if(_inventario[i].getVel() > 0) {
                    cout << "Velocidade: +" << _inventario[i].getVel() << endl;
                }
            }
            system("pause");
        }
};

class Guerreiro : public Personagem {
    public:
        Guerreiro(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            srand(time(NULL));
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            _atkAtual += 3;
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " usou Furia recebendo 3 de ataque e causou " << dano << " de dano." << endl;
        }
};

class Ladino : public Personagem {
    public:
        Ladino(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            p->receberSangramento();
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " usou Golpe Critico causando sangramento e " << dano << " de dano." << endl;
        }
};

class Clerigo : public Personagem {
    public:
        Clerigo(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            _hpAtual += _atkAtual;
            cout << _nome << " usou Cura e recuperou " << _atkAtual << " de vida." << endl;
        }
};

class Bruxo : public Personagem {
    public:
        Bruxo(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            srand(time(NULL));
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            _defAtual += 3;
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " usou Escudo Magico recebendo 3 de defesa e causou " << dano << " de dano." << endl;
        }
};

class Bardo : public Personagem {
    public:
        Bardo(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            srand(time(NULL));
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            p->reduzirAtaque(3);
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " usou Encantar reduzindo o ataque do inimigo em 3 e causou " << dano << " de dano." << endl;
        }
};

class Arqueiro : public Personagem {
    public:
        Arqueiro(string nome, int hp, int atk, int def, int vel) : Personagem(nome, hp, atk, def, vel){}

        void AtaqueEspecial(Personagem *p) override {
            srand(time(NULL));
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            p->reduzirDefesa(5);
            int dano = p->receberDano(_atkAtual);
            cout << _nome << " usou Flecha Perfurante reduzindo a defesa do inimigo em 5 e causou " << dano << " de dano." << endl;
        }
};

class Dungeon {
    public:
    vector<Item> comuns{
        Item("Armadura de Couro", "Comum", 2, 0, 0, 0),
        Item("Espada de Madeira", "Comum", 0, 2, 0, 0),
        Item("Escudo de Madeira", "Comum", 0, 0, 2, 0),
        Item("Botas de Couro", "Comum", 0, 0, 0, 2),
    };

    vector<Item> raros{
        Item("Armadura de Ferro", "Raro", 4, 0, 0, 0),
        Item("Espada de Ferro", "Raro", 0, 4, 0, 0),
        Item("Escudo de Ferro", "Raro", 0, 0, 4, 0),
        Item("Botas Velozes", "Raro", 0, 0, 0, 4),
    };

    vector<Item> epicos{
        Item("Armadura de Ouro", "Epico", 6, 0, 0, 0),
        Item("Espada de Ouro", "Epico", 0, 6, 0, 0),
        Item("Escudo de Ouro", "Epico", 0, 0, 6, 0),
        Item("Botas de Hermes", "Epico", 0, 0, 0, 6),
    };

    int mapa[10][15] = 
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,5,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,0,4,0,4,0,1},
        {1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
        {1,1,1,0,1,0,1,0,1,1,1,1,0,1,1},
        {1,2,0,0,1,0,0,0,0,0,0,0,0,3,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    void sortearItem(Personagem *p) {
        srand(time(NULL));
        int r = rand() % 20 + 1;
        if(r <= 10) {
            int i = rand() % comuns.size();
            system("cls");
            cout << "Voce encontrou: " << comuns[i].getNome() << endl;
            if (comuns[i].getHp() > 0) {
                cout << "HP: +" << comuns[i].getHp() << endl;
            }
            if (comuns[i].getAtk() > 0) {
                cout << "Ataque: +" << comuns[i].getAtk() << endl;
            }
            if (comuns[i].getDef() > 0) {
                cout << "Defesa: +" << comuns[i].getDef() << endl;
            }
            if (comuns[i].getVel() > 0) {
                cout << "Velocidade: +" << comuns[i].getVel() << endl;
            }
            p->adicionarItem(comuns[i]);
            system("pause");
        }
        else if(r <= 17) {
            int i = rand() % raros.size();
            system("cls");
            cout << "Voce encontrou: " << raros[i].getNome() << endl;
            if (raros[i].getHp() > 0) {
                cout << "HP: +" << raros[i].getHp() << endl;
            }
            if (raros[i].getAtk() > 0) {
                cout << "Ataque: +" << raros[i].getAtk() << endl;
            }
            if (raros[i].getDef() > 0) {
                cout << "Defesa: +" << raros[i].getDef() << endl;
            }
            if (raros[i].getVel() > 0) {
                cout << "Velocidade: +" << raros[i].getVel() << endl;
            }
            p->adicionarItem(raros[i]);
            system("pause");
        }
        else {
            int i = rand() % epicos.size();
            system("cls");
            cout << "Voce encontrou: " << epicos[i].getNome() << endl;
            if (epicos[i].getHp() > 0) {
                cout << "HP: +" << epicos[i].getHp() << endl;
            }
            if (epicos[i].getAtk() > 0) {
                cout << "Ataque: +" << epicos[i].getAtk() << endl;
            }
            if (epicos[i].getDef() > 0) {
                cout << "Defesa: +" << epicos[i].getDef() << endl;
            }
            if (epicos[i].getVel() > 0) {
                cout << "Velocidade: +" << epicos[i].getVel() << endl;
            }
            p->adicionarItem(epicos[i]);
            system("pause");
        }
    }

    void exibirMapa() {
        system("cls");
        for(int i=0; i<10; i++) {
            for(int j=0; j<15; j++) {
                if(mapa[i][j] == 0) {
                    cout << " ";
                }
                else if(mapa[i][j] == 1) {
                    cout << char(219);
                }
                else if(mapa[i][j] == 2) {
                    cout << "O";
                }
                else if(mapa[i][j] == 3) {
                    cout << "B";
                }
                else if(mapa[i][j] == 4) {
                    cout << "\033[1;31mX\033[0m";
                }
                else if(mapa[i][j] == 5) {
                    cout << "X";
                }
            }
            cout << endl;
        }
    }
    void comando(Personagem *p, char dir)
    {
        int x = p->getPosX();
        int y = p->getPosY();
        dir = tolower(dir);
        if(dir == 'w') {
            if(mapa[y-1][x] == 0) {
                mapa[y][x] = 0;
                mapa[y-1][x] = 2;
                p->mover(x, y-1);
            }
            else if(mapa[y-1][x] == 3) {
                mapa[y][x] = 0;
                mapa[y-1][x] = 2;
                p->mover(x, y-1);
                sortearItem(p);
            }
            else if(mapa[y-1][x] == 4) {
                mapa[y][x] = 0;
                mapa[y-1][x] = 2;
                p->mover(x, y-1);
                combate(p, new Guerreiro("Goblin", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
            else if(mapa[y-1][x] == 5) {
                mapa[y][x] = 0;
                mapa[y-1][x] = 2;
                p->mover(x, y-1);
                combate(p, new Guerreiro("Orc", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
        }
        else if(dir == 's') {
            if(mapa[y+1][x] == 0) {
                mapa[y][x] = 0;
                mapa[y+1][x] = 2;
                p->mover(x, y+1);
            }
            else if(mapa[y+1][x] == 3) {
                mapa[y][x] = 0;
                mapa[y+1][x] = 2;
                p->mover(x, y+1);
                sortearItem(p);
            }
            else if(mapa[y+1][x] == 4) {
                mapa[y][x] = 0;
                mapa[y+1][x] = 2;
                p->mover(x, y+1);
                combate(p, new Guerreiro("Goblin", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
            else if(mapa[y+1][x] == 5) {
                mapa[y][x] = 0;
                mapa[y+1][x] = 2;
                p->mover(x, y+1);
                combate(p, new Guerreiro("Orc", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
        }
        else if(dir == 'a') {
            if(mapa[y][x-1] == 0) {
                mapa[y][x] = 0;
                mapa[y][x-1] = 2;
                p->mover(x-1, y);
            }
            else if(mapa[y][x-1] == 3) {
                mapa[y][x] = 0;
                mapa[y][x-1] = 2;
                p->mover(x-1, y);
                sortearItem(p);
            }
            else if(mapa[y][x-1] == 4) {
                mapa[y][x] = 0;
                mapa[y][x-1] = 2;
                p->mover(x-1, y);
                combate(p, new Guerreiro("Goblin", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
            else if(mapa[y][x-1] == 5) {
                mapa[y][x] = 0;
                mapa[y][x-1] = 2;
                p->mover(x-1, y);
                combate(p, new Guerreiro("Orc", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
        }
        else if(dir == 'd') {
            if(mapa[y][x+1] == 0) {
                mapa[y][x] = 0;
                mapa[y][x+1] = 2;
                p->mover(x+1, y);
            }
            else if(mapa[y][x+1] == 3) {
                mapa[y][x] = 0;
                mapa[y][x+1] = 2;
                p->mover(x+1, y);
                sortearItem(p);
            }
            else if(mapa[y][x+1] == 4) {
                mapa[y][x] = 0;
                mapa[y][x+1] = 2;
                p->mover(x+1, y);
                combate(p, new Guerreiro("Goblin", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
            else if(mapa[y][x+1] == 5) {
                mapa[y][x] = 0;
                mapa[y][x+1] = 2;
                p->mover(x+1, y);
                combate(p, new Guerreiro("Orc", 30, 10, 10, 10));
                sortearItem(p);
                p->resetar();
            }
        }
        else if(dir == 'i') {
            p->exibirInventario();
        }
    }
    void exibirRodadas(Personagem *p1, Personagem *p2)
    {
        system("cls");
        cout << p1->getNome() << " vs " << p2->getNome() << endl;
        cout << p1->getNome() << " - HP: " << p1->getHpAtual() << "/" << p1->getHp() << endl;
        cout << p2->getNome() << " - HP: " << p2->getHpAtual() << "/" << p2->getHp() << endl;
    }

    void combate(Personagem *p1, Personagem *p2)
    {
        srand(time(NULL));
        int iniciativa = rand() % 2;
        while(p1->estaVivo() && p2->estaVivo()) {
            exibirRodadas(p1, p2);
            if(p1->getVelAtual()>p2->getVelAtual()) {
                p1->atacar(p2);
                p2->atacar(p1);
            }
            else if (p1->getVelAtual()<p2->getVelAtual()) {
                p2->atacar(p1);
                p1->atacar(p2);
            }
            else if (p1->getVelAtual()==p2->getVelAtual()) {
                if(iniciativa == 0) {
                    p1->atacar(p2);
                    p2->atacar(p1);
                }
                else {
                    p2->atacar(p1);
                    p1->atacar(p2);
                }
            }
            else {
                if(iniciativa == 0) {
                    p1->atacar(p2);
                    p2->atacar(p1);
                }
                else {
                    p2->atacar(p1);
                    p1->atacar(p2);
                }
            }
            if(p1->getSangramento() > 0) {
                p1->sangrar();
            }
            if(p2->getSangramento() > 0) {
                p2->sangrar();
            }
            system("pause");
        }
    }
};

int main(){
    Dungeon d;
    Guerreiro g("Guerreiro", 30, 15, 15, 15);
    char dir;
    while(1){
        d.exibirMapa();
        dir = getch();
        d.comando(&g, dir);
    }
    return 0;
}
