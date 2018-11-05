/*

Transicao::{
    Pre
    Pos
    funcao{
        anda, para, liga sensor
    }
}

funcao(estado atual){
    transicoes = transicoes_sensibilizadas(estado atual)
    transicao = escolhe(transicoes)
    estado atual -= transicao.Pre
    faz transicao.funcao()
    estado atual += transicao.Pos
    return estado atual
}
*/
