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
cd reunion
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

### **4.1 Estrutura do Menu**  
Ao iniciar, o sistema solicitará credenciais de login:  

**Menu Principal:**  
  1. Reservar Sala.  
  2. Alterar Reserva.  
  3. Cancelar Reserva.  
  4. Consultar Disponibilidade.  
  5. Exibir Minhas Reservas.  

**Opções Administrativas:** *(apenas para administradores)*  
   1. Gerenciar Usuários.  
   2. Gerenciar Salas.  
   3. Visualizar Todas as Reservas.  

Digite o número da opção desejada e siga as instruções na tela.  

---

## **5. Funcionalidades Detalhadas**  

### **5.1 Para Usuários**  
1. **Reservar Sala:**  
   - Escolha o tipo de sala e o horário desejado.  
   - O sistema exibirá as salas disponíveis.  
   - Confirme a reserva para registrá-la.  

   **Exemplo de fluxo:**  
   ```text
   Menu -> Opção 1: Reservar Sala  
   Selecione o tipo de sala: GA  
   Informe a data: 20/11/2024  
   Horário de início: 14:00  
   Horário de término: 15:00  
   Sala confirmada: GA-02  
   ```

2. **Alterar Reserva:**  
   - Liste suas reservas e escolha a que deseja modificar.  
   - Insira os novos detalhes (sala, horário ou data).  

3. **Cancelar Reserva:**  
   - Liste suas reservas.  
   - Escolha qual reserva cancelar e confirme a operação.  

4. **Verificar Disponibilidade:**  
   - Insira o tipo de sala e a data.  
   - O sistema exibirá os horários indisponíveis.  

5. **Exibir Minhas Reservas:**  
   - Visualize todas as reservas associadas ao seu ID.  

### **5.2 Para Administradores**  
1. **Cadastrar Usuários:**  
   - Insira os dados do usuário (CPF, nome, perfil, senha e status).  
   - O sistema valida as informações antes de registrar.  

2. **Cadastrar Salas:**  
   - Defina o número, tipo (PA, MA, GA, etc.) e status (ativo/inativo).  
   - O sistema verifica se o número da sala é único.  

3. **Listar Usuários e Reservas:**  
   - Liste usuários ou reservas filtrando por período ou tipo de sala.  

4. **Alterar Usuários ou Salas:**  
   - Modifique dados de usuários ou salas existentes, como status ou permissões.  

---

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