Instruções de Compilação:
- Criar um projeto de CLion com a pasta 'src' como raiz
- Carregar o ficheiro 'CMakeLists.txt', clicando neste com o botão direito do rato e clicando em 'Load CMake Project'
- Definir o *working directory* para a pasta 'src', indo a Run > Edit Configurations > Working Directory
- Correr o projeto (Run)

Instruções de utilizaçao:

Seguir as opções apresentadas na interface do programa, que disponibilizam diversas funcionalidades, tais como:
	1. Apresentar o componente fortemente conexo da padaria num determinado mapa.
	2. Calcular o caminho com apenas 1 carrinha, sem ter em conta os tempos de entrega ou capacidades.
	3. Calcular o caminho com apenas 1 carrinha, tendo em conta os tempos de entrega a cada cliente, ignorando a capacidade máxima da mesma.
	4. Calcular o caminho com múltiplas carrinhas, de capacidade limitada e tendo em conta o tempo de entrega a cada cliente.

Notas:
	- Ao carregar a informação proveniente de um ficheiro, o programa requer que o ficheiro de input se localize dentro do diretório 'resources/bakeryInput'. Obviamente, já possuímos exemplos de ficheiros de input para diferentes cidades neste diretório, sendo apenas necessário referi-los quando a interface o pedir, não esquecendo a extensão do ficheiro, caso se aplique. Caso pretenda inserir os dados manualmente, o mapa escolhido deverá localizar-se dentro do diretório 'resources/maps' e conter pelo menos os dois ficheiros: 'nodes.txt' e 'edges.txt'.
