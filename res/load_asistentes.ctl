LOAD DATA
INFILE 'Asistente.csv'
INTO TABLE Asistente
FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY "'"
(
    idAsistente INTEGER EXTERNAL,
    nombre CHAR,
    genero CHAR
)
