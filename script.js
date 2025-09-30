class Personagem {
  constructor(nome, imagem, descricao) {
    this.nome = nome;
    this.imagem = imagem;
    this.descricao = descricao;
    this.pontuacao = 0;
  }

  adicionarPontos(pontos) {
    this.pontuacao += pontos;
  }
}

class Quiz {
  constructor(personagens, perguntas) {
    this.personagens = personagens;
    this.perguntas = perguntas;
    this.indicePergunta = 0;
  }

  iniciar() {
    document.getElementById('inicio').style.display = 'none';
    document.getElementById('quiz').style.display = 'block';
    this.mostrarPergunta();
  }

  mostrarPergunta() {
    const perguntaAtual = this.perguntas[this.indicePergunta];
    const quizDiv = document.getElementById('quiz');

    quizDiv.innerHTML = `<div class="pergunta"><h2>${perguntaAtual.texto}</h2></div><div class="opcoes"></div>`;
    const opcoesDiv = quizDiv.querySelector('.opcoes');

    perguntaAtual.opcoes.forEach(opcao => {
      const botao = document.createElement('button');
      botao.textContent = opcao.texto;
      botao.onclick = () => this.selecionarOpcao(opcao);
      opcoesDiv.appendChild(botao);
    });
  }

  selecionarOpcao(opcao) {
    for (let personagem in opcao.pontos) {
      this.personagens[personagem].adicionarPontos(opcao.pontos[personagem]);
    }
    this.indicePergunta++;
    if (this.indicePergunta < this.perguntas.length) {
      this.mostrarPergunta();
    } else {
      this.mostrarResultado();
    }
  }

  mostrarResultado() {
    document.getElementById('quiz').style.display = 'none';
    const resultadoDiv = document.getElementById('resultado');
    resultadoDiv.style.display = 'block';

    const vencedor = Object.values(this.personagens).reduce((a, b) => a.pontuacao > b.pontuacao ? a : b);

    resultadoDiv.innerHTML = `
      <h2>Você é ${vencedor.nome}!</h2>
      <img src="imagens/${vencedor.imagem}" alt="${vencedor.nome}">
      <p>${vencedor.descricao}</p>
      <p>Pontuação total: ${vencedor.pontuacao}</p>
      <button onclick="quiz.reiniciar()">Recomeçar</button>
    `;
  }

  reiniciar() {
    this.indicePergunta = 0;
    for (let key in this.personagens) {
      this.personagens[key].pontuacao = 0;
    }
    document.getElementById('resultado').style.display = 'none';
    document.getElementById('inicio').style.display = 'block';
  }
}

const personagens = {
  Ichigo: new Personagem("Ichigo", "Ichigo.webp", "Um deus da morte substituto, um hibrido de todas as raças (deus da morte, fullbringer, quincy, hollow)."),
  Urahara: new Personagem("Urahara", "Urahara.jpg", "Um ex deus da morte que treinou Ichigo, um dos personagens mais brabos do anime."),
  Shunsui: new Personagem("Shunsui", "Shunsui.jpg", "Atual capitão da gotei 13, Um dos deuses da morte mais fortes da geração.")
};

const perguntas = [
  {
    texto: "Qual é o seu passatempo favorito?",
    opcoes: [
      { texto: "Treinar para ser o mais forte", pontos: { Ichigo: 3, Urahara: 2, Shunsui: 1 } },
      { texto: "Realizar pesquisas sobre o mundo", pontos: { Ichigo: 1, Urahara: 3, Shunsui: 2 } },
      { texto: "Descansar, galantear mulheres", pontos: { Urahara: 2, Ichigo: 1, Shunsui: 3 } }
    ]
  },
  {
    texto: "Qual é seu arquiinimigo?",
    opcoes: [
      { texto: "Grimmjow jaegerjaquez", pontos: { Shunsui: 1, Ichigo: 3, Urahara: 1 } },
      { texto: "Aizen", pontos: { Ichigo: 1.5, Urahara: 1.5, Shunsui: 1.5 } },
      { texto: "Staark", pontos: { Shunsui: 3, Ichigo: 1, Urahara: 1 } }
    ]
  },
  {
    texto: "Qual a sua Zanpakuto?",
    opcoes: [
      { texto: "Zangetsu", pontos: { Ichigo: 3, Urahara: 1, Shunsui: 2 } },
      { texto: "Katen e Kyoukotsu", pontos: { Ichigo: 2, Urahara: 1, Shunsui: 3 } },
      { texto: "Benihime", pontos: { Ichigo: 1, Urahara: 3, Shunsui: 2 } }
    ]
  },
  {
    texto: "Qual é a sua bankai?",
    opcoes: [
      { texto: "Tensa Zangetsu", pontos: { Ichigo: 3, Urahara: 2, Shunsui: 1 } },
      { texto: "Katen Kyoukotsu Karamatsu Shinju", pontos: { Ichigo: 2, Urahara: 1, Shunsui: 3 } },
      { texto: "Kannonbiraki Benihime Aratame", pontos: { Ichigo: 1, Urahara: 3, Shunsui: 2 } }
    ]
  }
  
];

const quiz = new Quiz(personagens, perguntas);

function iniciarJogo() {
  quiz.iniciar();
}
