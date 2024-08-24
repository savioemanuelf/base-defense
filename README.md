# Base Defense - LP1
## Sobre o jogo
Você é um herói que precisa defender sua base dos inimigos, para isso é necessário administrar com cuidado sua mana e sua vida, jogo proposto pela matéria de Linguagem de Programação UFRN.

## Autores do Projeto
- Elon Arkell Freire Bezerra
- Sávio Emanuel Mariano Fonseca
- Vinicius Alexandre Melo
  
## Orientador
- Isaac Franco Fernandes

## Funcionalidades

- Menu inicial (Jogar, Opções e Sair).
- Movimentação baseada no cursor do mouse (Press Right Buttom).
- Disparo de projétil com a tecla "Q" do teclado.
- Sistema de vida e mana do herói.
- Ao abater inimigos há um percentual de drop de poções de vida e mana.
- Base com vida regenerativa ao longo do tempo.
- Inimigos são gerados aleatoriamente fora da tela e vão se aproximando em direção ao herói. 
- Sistema de pause durante o jogo (Press Esc to Pause).


## Configuração e execução no Linux

- **Instale as ferramentas essenciais para C++**

Primeiramente, atualize os repositórios de pacotes:
```bash
  sudo apt update
```

Em seguida, instale o pacote `build-essential` que inclui o compilador `g++` e outras ferramentas:
```bash
  sudo apt install build-essential
```

- **Clone o projeto**
```bash
  git clone https://github.com/savioemanuelf/base-defense
```

- **Navegue até diretório do projeto**
```bash
  cd base-defense
```

**Compile e execute o código**:
Usando o `Makefile`
```bash
  make
```
