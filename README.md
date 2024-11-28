~~~c
Desenvolvido por Gabriel Silva, Lucas Vieira, Marcelo Belotto e Vinicius Silva.
~~~

# Guia do Usuário - ReuniON
Bem-vindo ao ReuniON, um sistema de gerenciamento de reservas de salas de reunião. Este guia fornece instruções detalhadas sobre a instalação, navegação e uso do sistema para otimizar o uso de espaços corporativos.

Para acessar este guia no formato interativo, clique [aqui](https://reuniondocs.gitbook.io/guia-do-usuario).

Se preferir, faça download da versão PDF, clicando [aqui](https://1drv.ms/b/s!AncniuGrXQf6i4AE3eJr6_5fRdRX3g?e=FG6UUd).

## Conteúdo

1. [ReuniON](#reunion)
2. [Requisitos do Sistema](#requisitos-do-sistema)
3. [Instalação e Execução do Sistema](#instalação-e-execução-do-sistema)
4. [Navegando no Sistema](#navegando-no-sistema)
5. [Funcionalidades Detalhadas](#funcionalidades-detalhadas)
6. [Telas e Mensagens de Sistema](#telas-e-mensagens-de-sistema)
7. [Backup e Manutenção](#backup-e-manutenção)
8. [Recursos Planejados](#recursos-planejados)

<br>

---

<br>

# ReuniON
O ReuniON é uma ferramenta projetada para atender às necessidades de agendamento e gerenciamento de salas de reunião em organizações. Sua interface de linha de comando (CLI) é simples e eficiente, permitindo que usuários e administradores realizem operações como reservas, consultas e gerenciamento de salas e usuários.

### **Principais Recursos:**

*   **Usuários Gerais:**

    * Reservar salas.
    * Alterar ou cancelar reservas.
    * Verificar disponibilidade.


* **Administradores:**
  * Cadastrar e gerenciar usuários e salas.
  * Visualizar todas as reservas.
  * Alterar configurações de usuários e salas.

[Topo](#conteúdo)

<br>

***

<br>

# Requisitos do Sistema

#### **Hardware:**

* Processador: x64 ou superior.
* Memória RAM: 2 GB (mínimo).
* Espaço em disco: 100 MB.

#### **Software:**

* **Sistema Operacional:** Compatível com Windows, Linux ou MacOS.
* **Compilador:** GCC (GNU Compiler Collection).
* **Ferramentas Necessárias:**
  * Visual Studio Code (opcional, como IDE).
  * Git (para controle de versão e clonagem do repositório).

[Topo](#conteúdo)

<br>

***

<br>

# Instalação e Execução do Sistema

## &#x20;**Clonando o Repositório**

#### Execute os comandos abaixo no terminal:

```bash
git clone https://github.com/marcelo-belotto/projeto-ESI.git
cd projeto-ESI
```
## **Compilando o Sistema**

Use o GCC para compilar:

```bash
gcc -o ReuniON.exe ./src/*.c main.c
```

####

## **Executando o Sistema**

Após compilar, execute o sistema com:

```bash
./ReuniON
```

Se ocorrerem erros, certifique-se de que o GCC está instalado e o diretório atual contém os arquivos do projeto.

[Topo](#conteúdo)

<br>

***

<br>

# Navegando no Sistema

## **Estrutura de Menus**

Ao acessar o ReuniON, o sistema exibirá o **Menu Inicial**, com as seguintes opções:

1. **Fazer login:** Insira seu ID e senha para acessar o sistema.
2. **Sair:** Encerre o sistema.

Após o login, você será direcionado para um menu específico de acordo com o seu perfil:



## Menu Geral (Usuários Comuns):

1. [Listar Salas](#listar-salas)
2. [Reservar Sala](#reservar-sala)
3. [Listar Reservas](#listar-reservas)
4. [Alterar Reserva](#alterar-reserva)
5. [Cancelar Reserva](#cancelar-reserva)
6. [Alterar Senha](#alterar-senha)
7. Sair

## Menu Administrador:
#### Funcionalidades exclusivas, além daquelas já contidas no menu geral

1. [Cadastrar Usuário](#cadastrar-usuário)
2. [Alterar Usuário](#alterar-usuário)
3. [Cadastrar Sala](#cadastrar-sala)
5. [Alterar Sala](#alterar-sala)
6. [Listar Reservas](#listar-reservas---administrador)

Para navegar, digite o número correspondente à opção desejada.

[Topo](#conteúdo)

<br>

***

<br>

# Funcionalidades Detalhadas

### Listar Salas:
   * Veja a relação de salas disponíveis, com detalhes sobre o tipo e a capacidade.
  
[Menu](#menu-geral-usuários-comuns)

### Reservar Sala:

* Escolha o tipo de sala;
* O sistema exibirá todas as salas cadastradas;
* Escolha o número da sala e digite as datas de início e fim da reserva, assim como horas de início e fim.
* O sistema confirmará a disponibilidade e registrará a reserva.

[Menu](#menu-geral-usuários-comuns)

### Listar Reservas - Usuário Geral:

* Visualize suas reservas atuais, com detalhes de data, horário e sala.

[Menu](#menu-geral-usuários-comuns)


## Alterar Reserva:

* Escolha uma de suas reservas e modifique os dados (data, horário ou sala).

[Menu](#menu-geral-usuários-comuns)


## Cancelar Reserva

* Selecione uma reserva para cancelar. Confirme a operação para concluí-la.

[Menu](#menu-geral-usuários-comuns)

## Alterar Senha:

* Atualize sua senha de acesso ao sistema.

[Menu](#menu-geral-usuários-comuns)


## Cadastrar Usuário:
   * Insira os dados do novo usuário (nome, CPF, perfil, senha, status).

[Menu](#menu-administrador)

## Alterar Usuário:

* Modifique os dados de um usuário existente (ex.: perfil ou status).

[Menu](#menu-administrador)

## Cadastrar Sala:

* Registre uma nova sala informando número e tipo.

[Menu](#menu-administrador)

## Listar Salas:

* Veja todas as salas registradas no sistema, ativas ou inativas.

[Menu](#menu-administrador)

## Alterar Sala:

* Atualize informações de uma sala (ex.: status ou tipo).


[Menu](#menu-administrador)

## Listar Reservas - Administrador:

* Veja todas as reservas realizadas, independente do usuário.

[Menu](#menu-administrador)

[Topo](#conteúdo)

<br>

***

<br>

# Telas e Mensagens de Sistema

## Tela - Reservar Sala

~~~c
=== ReuniON ===
1. Listar salas
2. Reservar sala
3. Listar reservas
4. Alterar reserva
5. Cancelar reserva
6. Alterar senha
7. Sair

Escolha uma opção: 2

Escolha o tipo de sala: GA

Salas cadastradas:
Número da sala: 02
Tipo da sala: GA
Status atual da sala: Ativa

Número da sala: 06
Tipo da sala: GA
Status atual da sala: Ativa

Escolha o número da sala: 02

Digite a data de inicio da reserva (dd/mm/yyyy): 30/11/2024
Digite a hora de inicio da reserva (HH:MM): 14:00
Digite a data de fim da reserva (dd/mm/yyyy): 30/11/2024
Digite a hora de fim da reserva (HH:MM): 15:00

Sala GA - 02 reservada com sucesso.
~~~

***


## Fluxos

### Fluxo Normal

* **Reserva confirmada:**
  * "Sua reserva foi registrada com sucesso!"
* **Usuário cadastrado:**
  * "Novo usuário adicionado: \[ID]."

### Mensagens de Erro

* **Login inválido:**
  * "Credenciais incorretas. Tente novamente."
* **Sala indisponível:**
  * "Erro: Sala já reservada neste horário."
* **Dados inválidos:**
  * "Os campos obrigatórios devem ser preenchidos corretamente."

### Fluxos de Exceção

* **Erro na autenticação:**\
  O sistema bloqueia o acesso após 3 tentativas falhas.
* **Conflito de agendamento:**\
  O sistema solicita ajustes na data ou sala para evitar conflitos.

[Topo](#conteúdo)

<br>

***

<br>

# Backup e Manutenção

## Backup Manual

* Acesse o diretório `databases/`.
* Faça cópias dos arquivos `salas.csv` e `usuarios.csv` para um local seguro.


## Atualizações e Suporte

*   Atualize o sistema com:

    ```bash
    git pull origin main
    ```

* Relate problemas no repositório GitHub do projeto na aba _Issues_.

[Topo](#conteúdo)

<br>

***

<br>

# Recursos Planejados

* **Interface Gráfica:** Para melhorar a acessibilidade do sistema.
* **Banco de dados:** Construir a persistência dos dados com banco de dados estruturado (SQL).
* **Notificações por E-mail:** Alertas de reservas futuras e cancelamentos.

[Topo](#conteúdo)

<br>

***

<br>

**Observação:** Para mais informações, contribua ou acesse os arquivos no repositório oficial do projeto. Este guia está em constante evolução.

[Topo](#conteúdo)