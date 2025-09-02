var frase = document.getElementById("frase");
var jogador = document.getElementById("jogador");
var computador = document.getElementById("computador");

var botao = document.getElementById("botao");

var areaEscolha = document.getElementById("area-escolha");
var areaResultado = document.getElementById("area-resultado");

var imagens_jogador = ["img/Rock.png", "img/Scissors.png", "img/Paper.png"];
var imagens_computador = ["img/Rock-pc.png", "img/Scissors-pc.png", "img/Paper-pc.png"];


var index = 0;

function effect(){
    jogador.src = imagens_jogador[index];
    computador.src = imagens_computador[index];

    index++;
    if(index === 3){
        index = 0;
    }
}
var efeito = setInterval(effect, 100);

function select(escolhaJogador){

    areaEscolha.style.display = 'none';

    areaResultado.style.display = 'block';

    frase.textContent = '3';

    var tempo = setInterval(()=>{
        var cronometro = parseInt(frase.textContent);
        cronometro --;
        frase.textContent = cronometro;

        if(cronometro === 0){
            clearInterval(tempo);
            clearInterval(efeito);
        }
    }, 1000);

    setTimeout(() => {
        var escolhaComputador = Math.floor(Math.random() * 3);
        console.log(escolhaComputador);
        
        computador.src = imagens_computador[escolhaComputador];
         jogador.src = imagens_jogador[escolhaJogador];

        if(escolhaJogador === escolhaComputador){
            frase.textContent = 'Empatou!';
            botao.style.display = 'block';

            return false;
        }

        switch(escolhaJogador){
            case 0://escolheu pedra
            escolhaJogador === 0 ? frase.textContent = "Jogador venceu!" : frase.textContent = "Computador venceu!";
            botao.style.display = 'block';
            break;

            case 1://escolheu papel
            escolhaJogador === 2 ? frase.textContent = "Jogador venceu!" : frase.textContent = "Computador venceu!";
            botao.style.display = 'block';
            break;

            case 2://escolheu tesoura
            escolhaJogador === 1 ? frase.textContent = "Jogador venceu!" : frase.textContent = "Computador venceu!";
            botao.style.display = 'block';
            break;

            default:
                alert("Escolha invalida");
        }
       
    }, 3000);
}

