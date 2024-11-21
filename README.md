# **Guia do Usuário - ReuniON**  
Bem-vindo ao ReuniON, um sistema de gerenciamento de reservas de salas de reunião. Este guia fornece instruções detalhadas sobre a instalação, navegação e uso do sistema para otimizar o uso de espaços corporativos.  

---

## **1. Introdução ao ReuniON**  
O ReuniON é uma ferramenta projetada para atender às necessidades de agendamento e gerenciamento de salas de reunião em organizações. Sua interface de linha de comando (CLI) é simples e eficiente, permitindo que usuários e administradores realizem operações como reservas, consultas e gerenciamento de salas e usuários.  

### **Principais Recursos:**  
- **Usuários Gerais:**  
  - Reservar salas.  
  - Alterar ou cancelar reservas.  
  - Verificar disponibilidade.  

- **Administradores:**  
  - Cadastrar e gerenciar usuários e salas.  
  - Visualizar todas as reservas.  
  - Alterar configurações de usuários e salas.  

---

## **2. Requisitos do Sistema**  

### **Hardware:**  
- Processador: x64 ou superior.  
- Memória RAM: 2 GB (mínimo).  
- Espaço em disco: 100 MB.  

### **Software:**  
- **Sistema Operacional:** Compatível com Windows, Linux ou MacOS.  
- **Compilador:** GCC (GNU Compiler Collection).  
- **Ferramentas Necessárias:**  
  - Visual Studio Code (opcional, como IDE).  
  - Git (para controle de versão e clonagem do repositório).  

---

## **3. Instalação do Sistema**  

### **3.1 Clonando o Repositório**  
Execute os comandos abaixo no terminal:  
```bash
git clone https://github.com/marcelo-belotto/projeto-ESI.git
cd projeto-ESI
```

### **3.2 Compilando o Sistema**  
Use o GCC para compilar:  
```bash
gcc -o ReuniON.exe ./src/*.c main.c
```

### **3.3 Executando o Sistema**  
Após compilar, execute o sistema com:  
```bash
./ReuniON
```

Se ocorrerem erros, certifique-se de que o GCC está instalado e o diretório atual contém os arquivos do projeto.  

---

## **4. Navegando no Sistema**  

### **4.1 Estrutura de Menus**  
Ao acessar o ReuniON, o sistema exibirá o **Menu Inicial**, com as seguintes opções:  
1. **Fazer login:** Insira seu ID e senha para acessar o sistema.  
2. **Sair:** Encerre o sistema.  

Após o login, você será direcionado para um menu específico de acordo com o seu perfil:  

#### **Menu Geral (Usuários Comuns):**  
1. [Listar Salas](#listar-salas)  
2. [Reservar Sala](#reservar-sala)  
3. [Listar Reservas](#listar-reservas)  
4. [Alterar Reserva](#alterar-reserva)  
5. [Cancelar Reserva](#cancelar-reserva)  
6. [Alterar Senha](#alterar-senha)  
7. Sair  

#### **Menu Administrador:**  
1. [Cadastrar Usuário](#cadastrar-usuario)  
2. [Alterar Usuário](#alterar-usuario)  
3. [Cadastrar Sala](#cadastrar-sala)  
4. [Listar Salas](#listar-salas)  
5. [Alterar Sala](#alterar-sala)  
6. [Reservar Sala](#reservar-sala)  
7. [Listar Reservas](#listar-reservas)  
8. [Alterar Reserva](#alterar-reserva)  
9. [Cancelar Reserva](#cancelar-reserva)  
10. [Alterar Senha](#alterar-senha)  
11. Sair  

Para navegar, digite o número correspondente à opção desejada.  

---

## **5. Funcionalidades Detalhadas**  

### **5.1 Menu Geral (Usuários Comuns)**  
<a id="listar-salas"></a>  
1. **Listar Salas:**  
   - Veja a relação de salas disponíveis, com detalhes sobre o tipo e a capacidade.  
   [Topo](#4-navegando-no-sistema)  

<a id="reservar-sala"></a>  
2. **Reservar Sala:**  
   - Escolha a sala e o horário desejados.  
   - O sistema confirmará a disponibilidade e registrará a reserva.  
   **Exemplo de fluxo:**  
   ```text  
   Menu -> Opção 2: Reservar Sala  
   Escolha o tipo de sala: GA  
   Informe a data: 20/11/2024  
   Horário de início: 14:00  
   Horário de término: 15:00  
   Reserva confirmada: GA-02  
   ```  
   [Topo](#4-navegando-no-sistema)  

<a id="listar-reservas"></a>  
3. **Listar Reservas:**  
   - Visualize suas reservas atuais, com detalhes de data, horário e sala.  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-reserva"></a>  
4. **Alterar Reserva:**  
   - Escolha uma de suas reservas e modifique os dados (data, horário ou sala).  
   [Topo](#4-navegando-no-sistema)  

<a id="cancelar-reserva"></a>  
5. **Cancelar Reserva:**  
   - Selecione uma reserva para excluir. Confirme a operação para concluí-la.  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-senha"></a>  
6. **Alterar Senha:**  
   - Atualize sua senha de acesso ao sistema.  
   [Topo](#4-navegando-no-sistema)  

---

### **5.2 Menu Administrador**  
<a id="cadastrar-usuario"></a>  
1. **Cadastrar Usuário:**  
   - Insira os dados do novo usuário (nome, CPF, perfil, senha, status).  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-usuario"></a>  
2. **Alterar Usuário:**  
   - Modifique os dados de um usuário existente (ex.: perfil ou status).  
   [Topo](#4-navegando-no-sistema)  

<a id="cadastrar-sala"></a>  
3. **Cadastrar Sala:**  
   - Registre uma nova sala informando número, tipo e capacidade.  
   [Topo](#4-navegando-no-sistema)  

<a id="listar-salas"></a>  
4. **Listar Salas:**  
   - Veja todas as salas registradas no sistema, ativas ou inativas.  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-sala"></a>  
5. **Alterar Sala:**  
   - Atualize informações de uma sala (ex.: status ou capacidade).  
   [Topo](#4-navegando-no-sistema)  

<a id="reservar-sala"></a>  
6. **Reservar Sala:**  
   - Realize uma reserva em nome de qualquer usuário.  
   [Topo](#4-navegando-no-sistema)  

<a id="listar-reservas"></a>  
7. **Listar Reservas:**  
   - Veja todas as reservas, com filtros por usuário, data ou sala.  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-reserva"></a>  
8. **Alterar Reserva:**  
   - Modifique os detalhes de qualquer reserva registrada no sistema.  
   [Topo](#4-navegando-no-sistema)  

<a id="cancelar-reserva"></a>  
9. **Cancelar Reserva:**  
   - Exclua reservas feitas por qualquer usuário.  
   [Topo](#4-navegando-no-sistema)  

<a id="alterar-senha"></a>  
10. **Alterar Senha:**  
    - Atualize a senha de qualquer usuário do sistema.  
    [Topo](#4-navegando-no-sistema)  

11. **Sair:**  
    - Retorne ao menu inicial.  

## **6. Cenários e Mensagens do Sistema**  

### **6.1 Fluxo Normal**  
- **Reserva confirmada:**  
  - "Sua reserva foi registrada com sucesso!"  
- **Usuário cadastrado:**  
  - "Novo usuário adicionado: [ID]."  

### **6.2 Mensagens de Erro**  
- **Login inválido:**  
  - "Credenciais incorretas. Tente novamente."  
- **Sala indisponível:**  
  - "Erro: Sala já reservada neste horário."  
- **Dados inválidos:**  
  - "Os campos obrigatórios devem ser preenchidos corretamente."  

### **6.3 Fluxos de Exceção**  
- **Erro na autenticação:**  
  O sistema bloqueia o acesso após 3 tentativas falhas.  
- **Conflito de agendamento:**  
  O sistema solicita ajustes na data ou sala para evitar conflitos.  

---

## **7. Backup e Manutenção**  

### **7.1 Backup Manual**  
- Acesse o diretório `databases/`.  
- Faça cópias dos arquivos `salas.csv` e `usuarios.csv` para um local seguro.  

### **7.2 Atualizações e Suporte**  
- Atualize o sistema com:  
  ```bash
  git pull origin main
  ```
- Relate problemas no repositório GitHub do projeto na aba *Issues*.  

---

## **8. Recursos Planejados**  
- **Interface Gráfica:** Para melhorar a acessibilidade do sistema.  
- **Integração com Google Calendar:** Sincronize suas reservas.  
- **Notificações por E-mail:** Alertas de reservas futuras e cancelamentos.  

---

**Observação:** Para mais informações, contribua ou acesse os arquivos no repositório oficial do projeto. Este guia está em constante evolução.