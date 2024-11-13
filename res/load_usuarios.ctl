LOAD DATA
INFILE 'Usuario.csv'
INTO TABLE Usuario
FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY "'"
(
    email CHAR,
    nombre CHAR,
    rangoEdad CHAR,
    fechaRegistro DATE "DD/MM/YYYY",
    saldoGemas INTEGER EXTERNAL,
    saldoMonedas INTEGER EXTERNAL,
    idAsistente INTEGER EXTERNAL
)

