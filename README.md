# EDB II -  Implementação de árvore B para controle de estoque

Este projeto implementa uma Árvore B para armazenar e organizar informações de um sistema de controle de estoque. A árvore B permite a inserção, exclusão e busca de itens no estoque com base em um ID único.

## 1.1. Fluxograma da Função de Exclusão em uma Árvore B

![Fluxograma da Função de Exclusão em uma Árvore B]()

---

### 2. Implementação Computacional 

A árvore B foi implementada para armazenar os itens de estoque, com as seguintes informações em cada nó:
- **ID do item**: chave única (inteiro).
- **Nome do item**: descrição (string).
- **Quantidade em estoque**: quantidade disponível (inteiro).

A árvore B possui as operações básicas:
- **Inserção**: Adiciona um novo item no sistema de controle de estoque.
- **Busca**: Permite buscar um item pelo ID (por exemplo, `buscar pelo ID 109` deve retornar `{109, "SSD", 30}`).
- **Exclusão**: Remove um item da árvore com base no ID (por exemplo, `excluir o ID 140`).
- **Geração de Arquivo `.dot` para Visualização com Graphviz**: A árvore pode ser visualizada utilizando o Graphviz, gerando um arquivo `.dot` que pode ser renderizado para exibição gráfica da estrutura da árvore.

### 3. Arquivo de Dados

Os dados dos itens de estoque a serem inseridos na árvore B estão disponíveis no arquivo [`./assets/dadosB.txt`](./assets/dadosB.txt). Este arquivo contém uma lista de itens no seguinte formato:

```text
{ID, "Nome", Quantidade}
```

### 3.2. Estrutura dos Projeto

### 4. Compilação e Execução

Para compilar e executar o programa, siga os passos abaixo:

1. **Compilação**:
   ```bash

   ```

2. **Execução**:
   ```bash

   ```

