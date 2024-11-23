LOAD DATA
INFILE 'Compra.csv'
INTO TABLE Compra
FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY "'"
(
    idConfiguracion INTEGER EXTERNAL,
    email CHAR,
    fechaCompra DATE "DD/MM/YYYY",
    totalGemas INTEGER EXTERNAL,
    totalMonedas INTEGER EXTERNAL
)
