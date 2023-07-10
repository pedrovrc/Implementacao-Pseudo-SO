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
