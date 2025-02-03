Esse projeto é uma atividade feita para o curso de sistemas embarcados do Embarcatech - Cepedi. Trata-se de um experimento utilizando funções de temporização.

A tarefa envolve o disparo único através de um botão para realizar um desligamento periódico de LEDs através das funções _add_alarm_in_ms_ e _turn_off_callback_.
Ao apertar o botão, uma rotina de interrupção é acionada (havendo um debounce via software), acionando 3 LEDs e emitindo a cor branca.
Em seguida, é disparada a função do temporizador, desligando cada LED de forma sequêncial (primeiro o vermelho, depois o azul, por último o verde) a cada 3 segundos.

A função _turn_off_callback_ age de forma recursiva, chamando a si mesmo até que nenhum LED esteja aceso.
É um requisito da tarefa que o botão não interrompa a rotina do temporizador, logo, após pressiona-lo ele fica desabilitado até que _turn_off_callback_ o habilite novamente.

O código foi projetado para ser executado numa Rasberry Pi Pico W e foi simulado no Wokwi, cujo diagrama pode ser visto no arquivo _diagram.json_.

A atividade pede para que, se possível, o experimento seja testado na placa de desenvolvimento BitDogLab. Utiliza-se o botão A e o LED RGB presentes nela para executar o experimento.
Dada a natureza do LED e interação com as cores, ao pressionar o botão, a cor branca é exibida, seguida da cor ciana e, por último, a cor verde.

Para observar a execução do código na BitDogLab, pode-se acessar o link a seguir: [https://drive.google.com/file/d/1t45mNMaU2kOzVfU4vSujOJAi492WcBDW/view?usp=drivesdk]
