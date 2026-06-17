# Mapa mental do cub3D

Este documento resume a implementacao atual do projeto cub3D, explicando as
pastas, os arquivos, as dependencias entre modulos e a logica principal do
programa.

O objetivo do cub3D e transformar um mapa 2D descrito em um arquivo `.cub` em
uma visao 3D em primeira pessoa, usando raycasting e MiniLibX.

## Visao geral

```text
main
 |
 |-- valida argumentos
 |-- abre arquivo .cub
 |-- le arquivo com get_next_line
 |-- transforma linhas em tokens
 |-- valida configuracoes e mapa
 |-- cria t_game
 |-- inicia MiniLibX
 |-- carrega texturas
 |-- configura player
 |-- entra no loop
       |
       |-- processa input
       |-- limpa imagem
       |-- desenha teto/chao
       |-- executa raycasting
       |-- desenha frame na janela
```

## Estrutura principal

```text
include/
  cub3d.h

src/
  cub3d.c
  create_validate_game.c
  run.c

  validation/
  create/
  constructor/
  configure/
  input/
  render/
  raycast/
  del/
  utils/

libft/
mlx/
resources/
```

## `include/cub3d.h`

Este e o arquivo central do projeto.

Ele concentra:

- constantes da janela
- codigos de tecla
- structs principais
- prototipos das funcoes
- includes da libft, GNL e MiniLibX

Structs mais importantes:

- `t_game`: estado completo do jogo.
- `t_assets`: caminhos, cores e texturas.
- `t_texture`: imagem XPM carregada pela MiniLibX.
- `t_mlx`: contexto, janela e imagem principal.
- `t_img`: buffer de desenho da tela.
- `t_player`: posicao, direcao e plano da camera.
- `t_ray`: dados de cada raio do raycasting.
- `t_wall`: dados da coluna de parede projetada.
- `t_input`: estado das teclas pressionadas.

O `t_game` conecta tudo:

```text
t_game
 |
 |-- board
 |-- assets
 |-- mlx
 |-- player
 |-- input
 |-- debug_view
```

## Entrada do programa

### `src/cub3d.c`

Contem o `main`.

Fluxo:

1. Valida quantidade de argumentos.
2. Cria e valida o jogo com `create_validate_game`.
3. Configura MiniLibX, texturas e player.
4. Chama `run`.
5. Libera tudo se houver erro antes do loop.

Esse arquivo nao conhece os detalhes do parser ou do render. Ele apenas
orquestra o fluxo principal.

### `src/create_validate_game.c`

Responsavel por abrir o arquivo `.cub`, chamar o parser e validar o resultado.

Fluxo:

```text
validate_open_file
validate_game_file
validate_game
```

Se qualquer etapa falhar, retorna `NULL`.

## Pasta `validation/`

Responsavel por verificar se o arquivo recebido faz sentido antes de iniciar o
jogo.

### `argc_validation.c`

Garante que o programa recebeu exatamente um argumento: o caminho do `.cub`.

### `validate_open_file.c`

Valida:

- extensao `.cub`
- se o arquivo pode ser aberto

Usa `open` e aceita qualquer descritor `>= 0`.

### `validate_game_file.c`

Transforma o arquivo em tokens e cria o `t_game`.

Fluxo:

```text
extract_token_list
validate_token_list
create_game
```

### `validate_token_list.c`

Valida a estrutura dos tokens.

Regras principais:

- exatamente um `NO`
- exatamente um `SO`
- exatamente um `WE`
- exatamente um `EA`
- exatamente um `F`
- exatamente um `C`
- mapa precisa existir
- nao pode haver linha estranha
- mapa deve ser o ultimo bloco util
- linha vazia dentro do mapa e erro

### `color_validation.c`

Valida o formato das cores.

Aceita:

```text
F 220,100,0
F 220, 100, 0
F   220 , 100 , 0
```

Rejeita componentes vazios ou lixo no final.

### `board_validator.c`

Valida o mapa.

Regras:

- deve haver exatamente um player
- celulas caminhaveis precisam estar fechadas
- linhas de tamanhos diferentes sao tratadas com seguranca

O mapa e considerado aberto se uma celula `0`, `N`, `S`, `E` ou `W` encostar
em espaco ou fora do array.

## Pasta `create/`

Responsavel por criar estruturas a partir dos tokens.

### `extract_token_list.c`

Le o arquivo linha por linha com `get_next_line`.

Cada linha vira um `t_token`.

### `create_token_by_line.c`

Cria um token.

Tambem remove `\n` e `\r` de forma segura, inclusive quando a ultima linha nao
tem newline.

### `create_game.c`

Aloca `t_game` e `t_assets`.

Depois chama:

```text
assign_assets
map_constructor
```

### `assign_assets.c`

Percorre tokens antes do mapa e chama o construtor adequado:

```text
NO -> no_texture_constructor
SO -> so_texture_constructor
WE -> we_texture_constructor
EA -> ea_texture_constructor
F  -> floor_color_constructor
C  -> ceiling_color_constructor
```

Tambem conta quantas linhas de mapa existem.

### `extract_colors.c`

Depois da validacao de formato, separa os tres componentes RGB.

Tambem verifica se cada valor esta entre `0` e `255`.

## Pasta `constructor/`

Transforma tokens especificos em dados do jogo.

### `texture_constructor.c`

Extrai os caminhos das texturas.

Exemplo:

```text
NO ./resources/north-texture.xpm
```

O caminho e salvo em `game->assets->no_texture`.

### `color_constructor.c`

Extrai `F` e `C`.

As cores ficam como vetores:

```text
floor_color[3]
ceiling_color[3]
```

Depois o render converte esses vetores para inteiro com `rgb_to_int`.

### `map_constructor.c`

Copia as linhas do mapa para `game->board`.

O mapa nao e retangularizado. Cada linha mantem seu tamanho original.

Por isso, as leituras de mapa precisam sempre verificar limites.

## Pasta `configure/`

Prepara o jogo para executar.

### `configure_game.c`

Inicializa:

1. MiniLibX
2. texturas
3. player

Tambem define se o jogo inicia em modo normal ou debug.

### `configure_textures.c`

Carrega os arquivos `.xpm` com:

```c
mlx_xpm_file_to_image
```

Depois pega o buffer com:

```c
mlx_get_data_addr
```

Cada textura guarda:

- imagem
- endereco
- largura
- altura
- bpp
- line length
- endian

### `configure_player.c`

Procura `N`, `S`, `E` ou `W` no mapa.

Define:

- posicao inicial
- direcao
- plano da camera

Depois troca o caractere do player por `0`, para o mapa representar apenas
paredes e chao.

## Pasta `input/`

Controla teclado e movimento.

### `input_hooks.c`

Registra eventos:

- fechar janela
- tecla pressionada
- tecla liberada

`ESC` fecha o jogo.

`M` alterna modo debug.

As teclas de movimento alteram o estado em `t_input`.

### `player_move.c`

Transforma o estado das teclas em movimento.

Controles:

- `W`: frente
- `S`: tras
- `A`: strafe esquerda
- `D`: strafe direita

O movimento usa:

```text
direcao do player
vetor perpendicular para strafe
MOVE_SPEED
```

A colisao permite andar apenas sobre `0`.

Tambem existe uma margem ao redor do player para evitar atravessar cantos.

### `player_rotate.c`

Rotaciona:

- vetor de direcao
- plano da camera

Usa matriz de rotacao 2D:

```text
x' = x * cos - y * sin
y' = old_x * sin + y * cos
```

As setas esquerda/direita alteram o angulo.

### `window_handlers.c`

Fecha o jogo.

Fluxo:

```text
del_game
exit
```

## Pasta `render/`

Desenha o frame final.

### `render_utils.c`

Funcoes basicas de desenho:

- `put_pixel`
- `clear_screen`
- `draw_rect`
- `draw_vertical_line`
- `draw_wireframe`

Todas desenham no buffer da imagem, nao direto na janela.

### `color_utils.c`

Converte RGB para inteiro:

```text
R,G,B -> 0xRRGGBB
```

### `render_background.c`

Desenha teto e chao.

Usa:

- cor `C` para teto
- cor `F` para chao

Tambem define a altura da viewport:

- tela inteira no modo normal
- metade superior no modo debug

### `render_frame.c`

Monta um frame completo:

```text
clear_screen
render_background
render_raycast
debug: wireframe + minimap
mlx_put_image_to_window
```

Esse arquivo e o ponto central do desenho.

### `render_minimap.c`

Desenha o mapa em 2D no modo debug.

O player e desenhado usando a posicao atual, nao mais o caractere original do
mapa.

## Pasta `raycast/`

Implementa o raycasting baseado no tutorial do Lode.

### `init_ray.c`

Para cada coluna `x`, calcula:

- `camera_x`
- direcao do raio
- celula inicial do mapa
- `delta_dist_x`
- `delta_dist_y`
- `step_x`
- `step_y`
- `side_dist_x`
- `side_dist_y`

Essa e a preparacao do DDA.

### `dda.c`

Executa o DDA.

O raio anda celula por celula ate bater em parede.

Depois calcula:

```text
perp_wall_dist
```

Essa distancia perpendicular evita o efeito olho de peixe.

`is_wall` trata com seguranca:

- coordenada negativa
- linha inexistente
- linha curta
- parede `1`
- espaco

### `texture_utils.c`

Escolhe a textura correta de acordo com o lado atingido pelo raio.

Tambem possui `texture_pixel`, que busca uma cor dentro do buffer da textura.

### `render_raycast.c`

Para cada coluna da viewport:

1. inicializa o raio
2. roda DDA
3. escolhe a textura
4. calcula altura da parede
5. calcula `wall_x`
6. calcula `tex_x`
7. calcula `tex_y`
8. desenha a coluna pixel por pixel

Esse e o nucleo visual do cub3D.

## Pasta `del/`

Libera memoria e recursos.

### `del_game.c`

Libera o jogo completo.

Ordem importante:

1. texturas
2. assets
3. mapa
4. MiniLibX
5. player
6. game

### `del_textures.c`

Destroi as imagens XPM carregadas.

Precisa rodar antes de destruir o contexto MLX.

### `del_mlx.c`

Destroi:

- imagem principal
- janela
- display
- contexto MLX

Tambem lida com inicializacao parcial.

### `del_split.c`

Libera arrays de strings.

### `del_token.c`

Libera tokens criados durante o parser.

## Pasta `utils/`

Funcoes pequenas auxiliares.

### `compare_token.c`

Classifica uma linha como:

- textura
- cor
- mapa
- linha vazia
- desconhecida

### `check_file.c`

Verifica se um caminho pode ser aberto.

### `dup_str.c`

Duplica strings com mensagem de erro padronizada.

## `resources/`

Contem:

- `map.cub`
- quatro texturas XPM

O `.cub` aponta para:

```text
NO ./resources/north-texture.xpm
SO ./resources/south-texture.xpm
WE ./resources/west-texture.xpm
EA ./resources/east-texture.xpm
```

## `Makefile`

Compila o projeto com:

```text
cc -Wall -Wextra -Werror
```

Targets principais:

- `all`
- `clean`
- `fclean`
- `re`

Tambem existem targets auxiliares de debug/validacao, mas eles nao fazem parte
da logica obrigatoria do jogo.

## Fluxo de dependencias

```text
cub3d.c
 |
 |-- validation/
 |-- create/
 |-- constructor/
 |
configure_game.c
 |
 |-- MiniLibX
 |-- configure_textures.c
 |-- configure_player.c
 |
run.c
 |
 |-- input/
 |-- render/
       |
       |-- render_background.c
       |-- raycast/
       |-- render_minimap.c
```

## Conceitos principais aprendidos

### Parser

O programa precisa transformar texto em dados confiaveis antes de iniciar a
janela.

Se o parser aceitar um mapa errado, o erro aparece depois como crash no render.

Por isso, validacao vem antes de MiniLibX.

### Mapa 2D

O mapa e uma matriz de caracteres.

Caracteres principais:

- `1`: parede
- `0`: chao
- espaco: fora do mapa
- `N/S/E/W`: posicao inicial do player

Depois da inicializacao, o player vira `0`.

### Camera

O player possui:

- posicao
- direcao
- plano da camera

A direcao diz para onde ele olha.

O plano da camera define a largura do campo de visao.

### Raycasting

Cada coluna da tela recebe um raio.

O raio anda no mapa usando DDA ate encontrar uma parede.

A distancia ate a parede define a altura da coluna desenhada.

### Textura

Depois de encontrar a parede, o programa calcula onde o raio bateu dentro da
parede.

Esse ponto vira uma coordenada `tex_x`.

Cada pixel vertical da parede calcula um `tex_y`.

`tex_x` e `tex_y` escolhem a cor dentro da textura.

### Loop de jogo

O jogo precisa repetir:

```text
ler input
atualizar player
desenhar frame
mostrar frame
```

Isso acontece dentro do `mlx_loop_hook`.

### Memoria

Tudo que e alocado precisa ter dono claro.

O `t_game` e o dono principal.

Por isso, `del_game` centraliza a liberacao.

## Resumo para defesa

Uma explicacao curta:

```text
O projeto le um arquivo .cub, valida texturas, cores e mapa, cria uma estrutura
central t_game, inicializa a MiniLibX, carrega quatro texturas XPM e posiciona
o player. A cada frame, o input atualiza a posicao e a rotacao do player. Em
seguida, a imagem e limpa, teto e chao sao desenhados e o raycasting dispara um
raio para cada coluna da tela. O DDA encontra a parede, calcula a distancia
perpendicular, projeta a altura da parede e usa as coordenadas de impacto para
buscar pixels da textura correta. O frame final e enviado para a janela com
mlx_put_image_to_window. Ao fechar, del_game libera texturas, mapa, assets,
MiniLibX e player.
```

