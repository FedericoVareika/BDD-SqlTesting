LOAD DATA
INFILE 'Configuracion.csv'
INTO TABLE Configuracion
FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY "'"
(
    idConfiguracion INTEGER EXTERNAL,
    ropa CHAR,
    interes CHAR,
    rasgo CHAR,
    voz CHAR,
    costoGemas INTEGER EXTERNAL,
    costoMonenas INTEGER EXTERNAL,
    idAsistente INTEGER EXTERNAL,
    vigente CHAR
)

