--CRIAÇÃO DAS TABELAS
CREATE TABLE DEPTO (
    coddepto INT PRIMARY KEY,
    nomedepto VARCHAR(100)
);
CREATE TABLE TITULACAO (
    codtit INT PRIMARY KEY,
    nometit VARCHAR(100)
);
CREATE TABLE PROFESSOR (
    codprof INT PRIMARY KEY,
    coddepto INT,
    codtit INT,
    nomeprof VARCHAR(100),

    FOREIGN KEY (coddepto) REFERENCES DEPTO(coddepto),
    FOREIGN KEY (codtit) REFERENCES TITULACAO(codtit)
);
CREATE TABLE DISCIPLINA (
    coddepto INT,
    numdisc INT,
    nomedisc VARCHAR(100),
    creditosdisc INT,

    PRIMARY KEY (coddepto, numdisc),
    FOREIGN KEY (coddepto) REFERENCES DEPTO(coddepto)
);
CREATE TABLE PREREQ (
    coddepto INT,
    numdisc INT,
    coddeptopreq INT,
    numdiscpreq INT,

    PRIMARY KEY (coddepto, numdisc, coddeptopreq, numdiscpreq),

    FOREIGN KEY (coddepto, numdisc)
        REFERENCES DISCIPLINA(coddepto, numdisc),

    FOREIGN KEY (coddeptopreq, numdiscpreq)
        REFERENCES DISCIPLINA(coddepto, numdisc)
);
CREATE TABLE TURMA (
    coddepto INT,
    numdisc INT,
    anosem INT,
    siglatur VARCHAR(10),
    capacidade INT,

    PRIMARY KEY (coddepto, numdisc, anosem, siglatur),

    FOREIGN KEY (coddepto, numdisc)
        REFERENCES DISCIPLINA(coddepto, numdisc)
);
CREATE TABLE PROFTURMA (
    coddepto INT,
    numdisc INT,
    anosem INT,
    siglatur VARCHAR(10),
    codprof INT,

    PRIMARY KEY (coddepto, numdisc, anosem, siglatur, codprof),

    FOREIGN KEY (coddepto, numdisc, anosem, siglatur)
        REFERENCES TURMA(coddepto, numdisc, anosem, siglatur),

    FOREIGN KEY (codprof)
        REFERENCES PROFESSOR(codprof)
);
CREATE TABLE PREDIO (
    codpredio INT PRIMARY KEY,
    descricaopredio VARCHAR(100)
);
CREATE TABLE SALA (
    codpredio INT,
    numsala INT,
    descricaosala VARCHAR(100),
    capacidade INT,

    PRIMARY KEY (codpredio, numsala),

    FOREIGN KEY (codpredio) REFERENCES PREDIO(codpredio)
);
CREATE TABLE HORARIO (
    coddepto INT,
    numdisc INT,
    anosem INT,
    siglatur VARCHAR(10),
    diasem INT,
    horainicio INT,
    codpredio INT,
    numsala INT,
    numhoras INT,

    PRIMARY KEY (
        coddepto, numdisc, anosem, siglatur,
        diasem, horainicio
    ),

    FOREIGN KEY (coddepto, numdisc, anosem, siglatur)
        REFERENCES TURMA(coddepto, numdisc, anosem, siglatur),

    FOREIGN KEY (codpredio, numsala)
        REFERENCES SALA(codpredio, numsala)
);
--INSERINDO DADOS NAS TABELAS
--DEPARTAMENTOS
INSERT INTO DEPTO VALUES
(1, 'Tecnologia'),
(2, 'Humanas'),
(3, 'Administracao');
--TITULAÇÃO
INSERT INTO TITULACAO VALUES
(1, 'Graduado'),
(2, 'Mestre'),
(3, 'Doutor');
--PROFESSORES
INSERT INTO PROFESSOR VALUES
(1, 1, 2, 'Seu Madruga'),
(2, 2, 3, 'Dona Florinda'),
(3, 3, 2, 'Seu Barriga'),
(4, 2, 1, 'Dona Clotilde'),
(5, 1, 1, 'Jaiminho'),
(6, 3, 3, 'Seu Furtado');
--DISCIPLINAS
INSERT INTO DISCIPLINA VALUES
(1, 101, 'Algoritmos', 60),
(1, 102, 'Banco de Dados', 60),
(2, 201, 'Filosofia', 40),
(2, 202, 'Sociologia', 40),
(3, 301, 'Administracao Financeira', 60),
(3, 302, 'Gestao de Pessoas', 60);
--PRÉREQUISITOS
INSERT INTO PREREQ VALUES
(1, 102, 1, 101), -- Banco de Dados precisa de Algoritmos
(3, 302, 3, 301); -- Gestão precisa de Financeira
--TURMAS
INSERT INTO TURMA VALUES
(1, 101, 20241, 'A', 30),
(1, 102, 20241, 'A', 30),
(2, 201, 20241, 'A', 25),
(2, 202, 20241, 'B', 25),
(3, 301, 20241, 'A', 40),
(3, 302, 20241, 'A', 40);
--PROFESSOR - TURMA
INSERT INTO PROFTURMA VALUES
(1, 101, 20241, 'A', 1), -- Madruga
(1, 102, 20241, 'A', 5), -- Jaiminho
(2, 201, 20241, 'A', 2), -- Florinda
(2, 202, 20241, 'B', 4), -- Clotilde
(3, 301, 20241, 'A', 3), -- Barriga
(3, 302, 20241, 'A', 6); -- Furtado
--PRÉDIOS
INSERT INTO PREDIO VALUES
(1, 'Predio Central'),
(2, 'Predio Administrativo');
--SALAS
INSERT INTO SALA VALUES
(1, 101, 'Sala 101', 30),
(1, 102, 'Sala 102', 30),
(2, 201, 'Sala 201', 40),
(2, 202, 'Sala 202', 40);
--HORÁRIOS
INSERT INTO HORARIO VALUES
(1, 101, 20241, 'A', 1, 800, 1, 101, 2), -- Madruga segunda
(1, 102, 20241, 'A', 3, 1000, 1, 102, 2), -- Jaiminho quarta
(2, 201, 20241, 'A', 2, 900, 2, 201, 2), -- Florinda terça
(2, 202, 20241, 'B', 4, 1100, 2, 202, 2), -- Clotilde quinta
(3, 301, 20241, 'A', 1, 1400, 1, 101, 2), -- Barriga tarde
(3, 302, 20241, 'A', 5, 1600, 2, 201, 2); -- Furtado sexta

--CONSULTA
SELECT 
    p.nomeprof,
    SUM(h.numhoras) AS total_horas
FROM PROFESSOR p
JOIN PROFTURMA pt 
    ON p.codprof = pt.codprof
JOIN HORARIO h 
    ON pt.coddepto = h.coddepto
    AND pt.numdisc = h.numdisc
    AND pt.anosem = h.anosem
    AND pt.siglatur = h.siglatur
GROUP BY p.nomeprof
ORDER BY total_horas DESC;

--SALAS OCUPADAS
SELECT 
    s.codpredio,
    s.numsala,
    s.descricaosala,
    h.diasem,
    h.horainicio,
    h.numhoras
FROM SALA s
JOIN HORARIO h
    ON s.codpredio = h.codpredio
    AND s.numsala = h.numsala
ORDER BY s.codpredio, s.numsala;

--SALAS LIVRE
SELECT 
    s.codpredio,
    s.numsala,
    d.diasem,
    h.horainicio
FROM SALA s
CROSS JOIN (
    SELECT 1 AS diasem UNION SELECT 2 UNION SELECT 3 UNION SELECT 4 UNION SELECT 5
) d
CROSS JOIN (
    SELECT 800 AS horainicio UNION SELECT 1000 UNION SELECT 1400 UNION SELECT 1600
) h
WHERE NOT EXISTS (
    SELECT 1
    FROM HORARIO ho
    WHERE ho.codpredio = s.codpredio
    AND ho.numsala = s.numsala
    AND ho.diasem = d.diasem
    AND ho.horainicio = h.horainicio

);
