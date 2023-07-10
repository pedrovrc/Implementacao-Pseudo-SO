# Implementacao-Pseudo-SO
Trabalho de implementação da disciplina de Sistemas Operacionais na UnB no semestre 2023/1

Visão geral do sistema:
  - main:
    
      A função main abre os arquivos recebidos pela linha de comando, instancia a classe PseudoOS e chama seu método Run. Ao término, printa mensagem sobre execução no terminal.

  - PseudoOS:
    
      Classe que contém o código principal para a execução do sistema em seu método Run, bem como as instâncias singleton dos 5 módulos existentes. Essa classe também segue o padrão singleton.

  - Classes Manager:

      Classes que implementam os diversos módulos do sistema implementado.

Mais informações podem ser encontradas no relatório em anexo a este repositório.

# Como executar o código

Para executar este trabalho, faça a descompressão do arquivo em anexo ao envio. Caso não possua o pacote “make” instalado no sistema, instale-o. Num sistema como o Ubuntu, isso é feito entrando as seguintes linhas no terminal:

$ sudo apt update

$ sudo apt install make

Após instalar o make, acessando a pasta descomprimida do Trabalho, execute a seguinte linha de comando em um Painel de Terminal:

$ make

Em seguida, digite o próximo comando:

$ .\pseudoos \<arquivo de processos\> \<arquivo de sistema de arquivos\>

É recomendado que os arquivos tenham extensão “.txt”. Além disso, é possível utilizar os arquivos de teste disponibilizados na pasta da implementação para executar e verificar o funcionamento do software desenvolvido.

